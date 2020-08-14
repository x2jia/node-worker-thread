#ifndef RCIB_OBJECT_
#define RCIB_OBJECT_

#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>
#include <uv.h>
#if defined _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <node_buffer.h>
#include <stdlib.h>
#include <string>
#include <memory>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include "../base/macros.h"
#include "../base/aligned_memory.h"
#include "../base/lazy_instance.h"
#include "../base/ref_counted.h"
#include "../base/WrapperObj.h"
#include "../base/WeakPtr.h"
#include "../base/FastDelegateImpl.h"
#include "../base/time/time.h"
#include "../base/MessagePump.h"
#include "../base/util_tools.h"
#include "../base/Event/WaitableEvent.h"
#include "../base/PendingTask.h"
#include "../base/observer_list.h"
#include "../base/MessagePumpDefault.h"
#include "../base/MessageLoop.h"
#include "../base/roler.h"
#include "../base/Thread.h"
#include "../base/at_exist.h"

namespace rcib {

  struct async_t_handle {
    uv_async_t handle_;
  };

  enum WORKTYPE {
    TYPE_START = 0,
    TYPE_SHA_256,
    TYPE_SHA = TYPE_SHA_256,
    TYPE_ED25519,
    TYPE_VM,
    //...
    TYPE_END
  };

  class async_req {
  public:
    async_req() {
      out = NULL;
      isolate = NULL;
      result = 0;
    }
    std::string error;
    char *out;
    ssize_t result;
    v8::Isolate* isolate;
    v8::Persistent<v8::Function> callback;
    bool finished;
    WORKTYPE w_t;
  };

  /*A thread - safe allocator
  */
  class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
  public:
    virtual void* Allocate(size_t length);
    virtual void* AllocateUninitialized(size_t length);
    virtual void Free(void* data, size_t);
  };

  class Param {
  public:
    Param() {}
    virtual ~Param() {}
  };

  class RcibHelper {
  public:
    explicit RcibHelper();
    //static
    static RcibHelper* GetInstance();
    static void AfterAsync(uv_async_t* h);
    static void DoNopAsync(async_req* r);
    static void DoNopAsync(async_req* r, size_t size);
    static void EMark(async_req* req, std::string message);
    static void EMark2(async_req* req, std::string message);
    static void init_async_req(async_req *req);

    void Init();
    void Terminate();
    void Uv_Send(async_req* req, uv_async_t* h);
    inline void PickFinished();

    inline void Push(async_req *itme) {
      pending_queue_.push_back(itme);
    }

    inline async_req* Pop() {
      if (working_queue_.empty())
        return NULL;
      async_req * item = working_queue_.front();
      working_queue_.pop_front();
      return item;
    }

    inline size_t taskNum() {
      return 0;
    }

  private:
    std::list<async_req *> pending_queue_;
    std::list<async_req *> working_queue_;
    async_t_handle *handle_;
  };

  class furOfThread : public node::ObjectWrap {
  public:

    furOfThread(): thread_(nullptr){
    }
 
    void* Wrap(v8::Local<v8::Object> object, base::Thread::Codes &cole) {
      node::ObjectWrap::Wrap(object);
      base::Thread *thread = new base::Thread();
      if (!thread) return nullptr;
      if (!thread->IsRunning()) {
        thread->set_thread_name("distribute_task_thread");
        thread->SetCods(cole);
        thread->StartWithOptions(base::Thread::Options{});
      }
      thread_ = thread;
      return thread;
    }

    bool IsRunning() {
      if (thread_) {
        return thread_->IsRunning();
      }
      return false;
    }

    void Close() {
      if (thread_) {
        delete thread_;
      }
      thread_ = nullptr;
    }

    base::Thread* thread() {
      return thread_;
    }

  private:
    virtual ~furOfThread() {
      if (thread_) {
        delete thread_;
      }
      thread_ = nullptr;
    }

    base::Thread* thread_ = nullptr;

  };

} //end rcib

#endif
