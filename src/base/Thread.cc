/*
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <node.h>
#include <v8.h>
#include <uv.h>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#include <objbase.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "ole32.lib")
#else
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#endif
#ifndef _WIN32
#if defined(__APPLE__) && defined(__MACH__)
#include <sys/resource.h>
#else
#include <limits.h>
#include <sys/syscall.h>
#endif
#endif

#include <string>
#include <memory>
#include <list>
#include <queue>
#include <map>
#include "macros.h"
#include "ref_counted.h"
#include "WrapperObj.h"
#include "WeakPtr.h"
#include "FastDelegateImpl.h"
#include "time/time.h"
#include "MessagePump.h"
#include "util_tools.h"
#include "Event/WaitableEvent.h"
#include "PendingTask.h"
#include "observer_list.h"
#include "MessagePumpDefault.h"
#include "MessageLoop.h"
#include "roler.h"
#include "Thread.h"

namespace base {

  void* Thread::ArrayBufferAllocator::Allocate(size_t length) {
    void* data = AllocateUninitialized(length);
    return data == nullptr ? data : memset(data, 0, length);
  }

  void* Thread::ArrayBufferAllocator::AllocateUninitialized(size_t length) { return malloc(length); }

  void Thread::ArrayBufferAllocator::Free(void* data, size_t) { free(data); }

  Thread::ArrayBufferAllocator array_buffer_allocator_;

#ifdef _WIN32
  Thread::ScopedCOMInitializer::~ScopedCOMInitializer() {
    assert(GetCurrentThreadId() == thread_id_);
    CoUninitialize();
  }

  void Thread::ScopedCOMInitializer::Initialize(COINIT init) {
    thread_id_ = GetCurrentThreadId();
    CoInitializeEx(NULL, init);
  }

  DWORD __stdcall ThreadFunc(void* params);
#else
  void * ThreadFunc(void* params);
#endif

  Thread::Options::Options()
    :message_loop_type_(MessageLoop::TYPE_DEFAULT), stack_size_(0) {
  }

  Thread::Options::Options(MessageLoop::Type type, size_t size)
    :message_loop_type_(type), stack_size_(size) {
  }

  Thread::Codes::Codes() {
    utf8 = NULL;
    len = 0;
  }

  Thread::Codes::Codes(char *utf8, int len) {
    this->utf8 = utf8;
    this->len = len;
  }

  Thread::Thread():
#ifdef _WIN32
  com_status_(NONE),
#endif
    started_(false),
    stopping_(false),
    running_(false),
    thread_(NULL),
    message_loop_(NULL),
    thread_id_(kInvalidThreadId),
    startup_data_(NULL){
    Init();
  }

  Thread::Thread(const char* name):
#ifdef _WIN32
  com_status_(NONE),
#endif
    started_(false),
    stopping_(false),
    running_(false),
    thread_(NULL),
    message_loop_(NULL),
    name_(name),
    thread_id_(kInvalidThreadId),
    startup_data_(NULL) {
    Init();
  }

  void Thread::Init() {
    computational_ = 0;

    uv_loop_init(&loop_);
    v8params_.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate* isolate = v8::Isolate::Allocate();
    node::MultiIsolatePlatform * pt = node::GetMainThreadMultiIsolatePlatform();
    
    pt->RegisterIsolate(isolate, &loop_);
    v8::Isolate::Initialize(isolate, v8params_);
    isolate_ = isolate;
  }

  Thread::~Thread() {
    Stop();
    node::MultiIsolatePlatform* pt = node::GetMainThreadMultiIsolatePlatform();
    pt->UnregisterIsolate(isolate_);
    if (isolate_) {
      isolate_->Dispose();
    }
    uv_loop_close(&loop_);
    delete v8params_.array_buffer_allocator;
  }

  bool Thread::StartWithOptions(const Options& options) {
    assert(!message_loop_);
    StartupData startup_data(options);
    startup_data_ = &startup_data;
    if (!CreateThreadInternal(options.stack_size_, this, &thread_)) {
      startup_data_ = NULL;
      return false;
    }
    startup_data.event_.Wait();
    startup_data_ = NULL;
    started_ = true;
    assert(message_loop_);
    return true;
  }

  //static
  bool Thread::CreateThreadInternal(size_t stack_size, Thread *thread,
    PlatformThreadHandle *out_thread_handle) {
#ifdef _WIN32
    unsigned int flags = 0;
    if (stack_size > 0)
      flags = STACK_SIZE_PARAM_IS_A_RESERVATION;

    Thread::ThreadParams * params = new Thread::ThreadParams;
    params->thread_ = thread;

    PlatformThreadHandle thread_handle = ::CreateThread(NULL, stack_size, ThreadFunc, params, flags, NULL);
    if (NULL == thread_handle) {
      delete params;
      return false;
    }
    if (out_thread_handle) {
      *out_thread_handle = thread_handle;
    } else {
      CloseHandle(thread_handle);
    }
    return true;
#else
    bool success = false;
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    if (stack_size > 0)
      pthread_attr_setstacksize(&attributes, stack_size);

    ThreadParams* params = new ThreadParams;
    params->thread_ = thread;

    int err = pthread_create(out_thread_handle, &attributes, ThreadFunc, params);
    success = !err;
    if (!success) {
      errno = err;
    }
    pthread_attr_destroy(&attributes);
    if (!success)
      delete params;
    return success;
#endif
  }

  void Thread::ThreadMain() {
    std::auto_ptr<MessageLoop> message_loop;
    message_loop.reset(new MessageLoop(startup_data_->options_.message_loop_type_));
    assert(message_loop.get());
#ifdef _WIN32
    thread_id_ = GetCurrentThreadId();
#elif defined(__APPLE__) && defined(__MACH__)
    thread_id_ = pthread_mach_thread_np(pthread_self());
#else
    thread_id_ = syscall(__NR_gettid);
#endif
    message_loop->set_thread_name(name_);
    message_loop_ = message_loop.get();
#ifdef _WIN32
    std::auto_ptr<ScopedCOMInitializer> com_initializer;
    if (com_status_ != NONE) {
      com_initializer.reset((com_status_ == STA) ?
        new ScopedCOMInitializer() :
      new ScopedCOMInitializer(MTA));
    }
#endif
    v8::Isolate* isolate = Isolate();
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);
    // Create a new context.
    v8::Local<v8::Context> context = v8::Context::New(isolate);
    v8::Context::Scope context_scope(context);

// Create a string containing the JavaScript source code.
    v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate,
      cods_.utf8,
      v8::NewStringType::kNormal,
      cods_.len).ToLocalChecked();
    // todo
    //v8::Local<v8::String> source =
    //  v8::String::NewFromUtf8Literal(isolate, "'Hello' + ', World!'");

    v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();

    v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();
    v8::String::Utf8Value utf8(isolate, result);

    SetCodsNull();
      
    running_ = true;
    startup_data_->event_.Signal();
    Run(message_loop_);

    running_ = false;
    // Let the thread do extra cleanup.
    CleanUp();
#ifdef _WIN32
    com_initializer.reset();
#endif
    message_loop_ = NULL;
  }

  void Thread::Run(MessageLoop *message_loop) {
    message_loop->Run();
  }

  bool Thread::IsRunning() const {
    return running_;
  }

  void Thread::SetPriority(ThreadPriority priority) {
#ifdef _WIN32
    switch (priority) {
    case kThreadPriority_Normal:
      ::SetThreadPriority(thread_, THREAD_PRIORITY_NORMAL);
      break;
    case kThreadPriority_RealtimeAudio:
      ::SetThreadPriority(thread_, THREAD_PRIORITY_TIME_CRITICAL);
      break;
    default:
      break;
    }
#endif
  }

  void Thread::Stop() {
    if (!started_)
      return;

    if (stopping_ || !message_loop_)
      return;

    stopping_ = true;

    message_loop_->Quit();

    PlatformThreadHandle thread_handle = thread_;
#ifdef _WIN32
    DWORD result = WaitForSingleObject(thread_handle, INFINITE);
    if (result != WAIT_OBJECT_0) {
      assert(0);
    }
    CloseHandle(thread_handle);
#else
    pthread_join(thread_handle, NULL);
#endif
    started_ = false;
    stopping_ = false;
  }

  bool Thread::set_thread_name(std::string name) {
    if (name_.empty()) {
      name_ = name;
      return true;
    }
    return false;
  }

  bool Thread::SetRoler(std::string name, FurRoler &ft) {
    FileIter iter = rolers_.find(name);
    if (iter == rolers_.end()) {
      rolers_.insert(std::make_pair(name, ft));
      return true;
    } else {
      // cannot set twice;
      ;
    }
    return false;
  }

  FurRoler Thread::GetRoler(std::string name) {
    FileIter iter = rolers_.find(name);
    if (iter == rolers_.end()) {
      return FurRoler(NULL);
    }
    return iter->second;
  }

  void Thread::RemoveRoler(std::string name) {
    FileIter iter = rolers_.find(name);
    if (iter == rolers_.end()) {
      return;
    }
    rolers_.erase(iter);
  }

  void Thread::IncComputational() {
    ++computational_;
  }

  void Thread::DecComputational() {
    --computational_;
  }

  size_t Thread::Computational() {
    return computational_;
  }

  void Thread::SetCods(Codes & cods) {
    cods_.utf8 = cods.utf8;
    cods_.len = cods.len;
  }

  void Thread::SetCodsNull() {
    cods_.utf8 = NULL;
    cods_.len = 0;
  }

}//end base

namespace base {

#ifdef _WIN32
  DWORD __stdcall ThreadFunc(void* params) {
    Thread::ThreadParams *thread_params = static_cast<Thread::ThreadParams*>(params);
    base::Thread *thread = thread_params->thread_;
    delete thread_params;

    thread->ThreadMain();

    return 0;
  }
#else
  void* ThreadFunc(void* params) {
    Thread::ThreadParams *thread_params = static_cast<Thread::ThreadParams*>(params);
    base::Thread *thread = thread_params->thread_;
    delete thread_params;

    thread->ThreadMain();

    return NULL;
  }
#endif

} //end base
