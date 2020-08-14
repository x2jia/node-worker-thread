#include "rcib_object.h"
#include "../vm/vm.h"
#include <iostream>

#define ONE ((char*)1)
#define TWO ((char *)2)

namespace rcib {

  extern bool bterminating_;

  // constructor
  RcibHelper::RcibHelper()
    :handle_(nullptr) {
  }

  //static
  RcibHelper* RcibHelper::GetInstance() {
    static RcibHelper This;
    return &This;
  }

  static void RunCallBack(async_req *req) {
    static const char * const prtFIN = "finished";
    v8::Isolate* isolate = req->isolate;
    v8::HandleScope scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    // there is always at least one argument. "error"
    int argc = 1;

    v8::Local<v8::Value> argv[2];

    if (-1 == req->result || !req->out) {
      argv[0] = node::UVException(isolate, -1, req->error.c_str());
    } else if (ONE == req->out) {
      req->out = nullptr;
      argv[0] = v8::Null(isolate);
      argc = 2;
      argv[1] = v8::String::NewFromUtf8(isolate, prtFIN, v8::NewStringType::kNormal).ToLocalChecked();
    } else if (TWO == req->out) {
      req->out = nullptr;
      argv[0] = v8::Null(isolate);
      argc = 2;
      argv[1] = v8::Uint32::NewFromUnsigned(isolate, static_cast<size_t>(req->result));
    } else {
      switch(req->w_t) {
      case TYPE_VM: {
        argv[0] = v8::Null(isolate);
        argc = 2;
        VMRe *hre = reinterpret_cast<VMRe *>(req->out);
        argv[1] = node::Buffer::Copy(isolate, (char *)hre->_data, req->result).ToLocalChecked();
        delete hre;
        req->out = nullptr;  // should be set null
      }
        break;
      default: {
        argv[0] = v8::Null(isolate);
        argc = 2;
        char *data = (char *)req->out;
        argv[1] = v8::String::NewFromUtf8(isolate, data, v8::NewStringType::kNormal).ToLocalChecked();
      }
        break;
      }
    }

    v8::TryCatch try_catch(isolate);
    try_catch.SetVerbose(false);

    v8::Local<v8::Function> callback =
      v8::Local<v8::Function>::New(isolate, req->callback);
    callback->Call(context, Null(isolate), argc, argv);

    // cleanup
    req->callback.Reset();
    if (req->out) {
      free(req->out);
      req->out = nullptr;
    }
    delete req;

    if (try_catch.HasCaught()) {
      node::FatalException(isolate, try_catch);
    }
  }

  //static
  void RcibHelper::AfterAsync(uv_async_t* h) {
    RcibHelper::GetInstance()->PickFinished();

    async_req * req = nullptr;
    while (true) {
      req = RcibHelper::GetInstance()->Pop();
      if (!req)
        break;
      RunCallBack(req);
    } //end while
  }

  //static
  void RcibHelper::DoNopAsync(async_req* req) {
    req->result = 1;
    req->out = ONE;
  }

  //static
  void RcibHelper::DoNopAsync(async_req* r, size_t size) {
    r->result = size;
    r->out = TWO;
  }

  //static
  void RcibHelper::EMark(async_req* req, std::string message) {
    req->out = nullptr;
    req->result = -1;
    req->error = message;
  }

  //static
  void RcibHelper::EMark2(async_req* req, std::string message) {
    if (req->out) {
      Param *hre = reinterpret_cast<Param *>(req->out);
      delete hre;
    }
    req->out = nullptr;
    req->result = -1;
    req->error = message;
  }

  //static
  void RcibHelper::init_async_req(async_req *req) {
    if (!req)
      return;
    req->finished = false;
    req->out = nullptr;
    req->result = 0;
    req->w_t = TYPE_START;
    RcibHelper::GetInstance()->Push(req);
  }

  void RcibHelper::Init() {
    //init this
    handle_ = new async_t_handle;
    uv_async_init(uv_default_loop(), (uv_async_t*)handle_, RcibHelper::AfterAsync);
  }

  void RcibHelper::Terminate() {
    bterminating_ = true;
  }

  void RcibHelper::Uv_Send(async_req* req, uv_async_t* h) {
    h = h ? h : (uv_async_t*)handle_;
    req->finished = true;
    uv_async_send(h);
  }

  //this function runs in main
  void RcibHelper::PickFinished() {
    std::list<async_req *> tmp_q;
    async_req * item = nullptr;
    while (!pending_queue_.empty()) {
      item = pending_queue_.front();
      pending_queue_.pop_front();
      if (!item)
        continue;
      if (item->finished) {
        working_queue_.push_back(item);
      } else {
        tmp_q.push_back(item);
      }
    }// end while
    pending_queue_.swap(tmp_q);
    DCHECK_EQ(tmp_q.size(), 0);
  }

} // end rcib
