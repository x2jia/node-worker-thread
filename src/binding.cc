#include <iostream>
#include "node/rcib.h"
#include "vm/vm.h"

using namespace rcib;

namespace rcib {

  extern bool bterminating_;
}

static void NewThread(const v8::FunctionCallbackInfo<v8::Value>& args) {
  NOTH
  DCHECK(args.IsConstructCall());
  void *data = NULL;
  if (args.Length() == 1 && node::Buffer::HasInstance(args[0])){
    base::Thread::Codes codes(node::Buffer::Data(args[0]), node::Buffer::Length(args[0]));
    rcib::furOfThread* fur = new rcib::furOfThread;
    data = fur->Wrap(args.This(), codes);
  } else {
   assert(0);
  }
  args.GetReturnValue().Set(args.This());
}

static void Close(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  rcib::furOfThread* fur = node::ObjectWrap::Unwrap<rcib::furOfThread>(args.Holder());
  fur->Close();
}

static void IsRunning(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  rcib::furOfThread* fur = node::ObjectWrap::Unwrap<rcib::furOfThread>(args.Holder());
  args.GetReturnValue().Set(v8::Boolean::New(isolate, fur->IsRunning()));
}

static void QueueNum(const v8::FunctionCallbackInfo<v8::Value>& args) {
  THREAD;
  uint32_t num = static_cast<uint32_t>(thr->Computational());
  args.GetReturnValue().Set(num);
}

void Independent0(const v8::FunctionCallbackInfo<v8::Value>& args) {
  ISOLATE(args);
  VmHelper::ParamWrapper2 param_all(0);
  if (2 == args.Length() &&
    node::Buffer::HasInstance(args[0]) &&
    args[1]->IsFunction()
    ) {
    param_all.name = node::Buffer::Data(args[0]);
    param_all.name_len = node::Buffer::Length(args[0]);
  } else {
    TYPEERROR;
  }
  THREAD;
  INITHELPER(args, 1);
  req->w_t = TYPE_VM;
  req->out = (char*)(new VMRe(thr->AsWeakPtr()));
  thr->message_loop()->PostTask(base::Bind(base::Unretained(VmHelper::GetInstance()),
    &VmHelper::Controller2, param_all, req, thr));
  RETURN_TRUE
}

void Independent1(const v8::FunctionCallbackInfo<v8::Value>& args) {
  ISOLATE(args);
  VmHelper::ParamWrapper2 param_all(1);
  if (3 == args.Length() &&
    node::Buffer::HasInstance(args[0]) &&
    node::Buffer::HasInstance(args[1]) &&
    args[2]->IsFunction()
    ) {
    param_all.name = node::Buffer::Data(args[0]);
    param_all.name_len = node::Buffer::Length(args[0]);
    param_all.p1 = node::Buffer::Data(args[1]);
    param_all.p1_len = node::Buffer::Length(args[1]);
  } else {
    TYPEERROR;
  }
  THREAD;
  INITHELPER(args, 2);
  req->w_t = TYPE_VM;
  req->out = (char*)(new VMRe(thr->AsWeakPtr()));
  thr->message_loop()->PostTask(base::Bind(base::Unretained(VmHelper::GetInstance()),
    &VmHelper::Controller2, param_all, req, thr));
  RETURN_TRUE
}

void Independent2(const v8::FunctionCallbackInfo<v8::Value>& args) {
  ISOLATE(args);
  VmHelper::ParamWrapper2 param_all(2);
  if (4 == args.Length() &&
    node::Buffer::HasInstance(args[0]) &&
    node::Buffer::HasInstance(args[1]) &&
    node::Buffer::HasInstance(args[2]) &&
    args[3]->IsFunction()
    ) {
    param_all.name = node::Buffer::Data(args[0]);
    param_all.name_len = node::Buffer::Length(args[0]);
    param_all.p1 = node::Buffer::Data(args[1]);
    param_all.p1_len = node::Buffer::Length(args[1]);
    param_all.p2 = node::Buffer::Data(args[2]);
    param_all.p2_len = node::Buffer::Length(args[2]);
  } else {
    TYPEERROR;
  }
  THREAD;
  INITHELPER(args, 3);
  req->w_t = TYPE_VM;
  req->out = (char*)(new VMRe(thr->AsWeakPtr()));
  thr->message_loop()->PostTask(base::Bind(base::Unretained(VmHelper::GetInstance()),
    &VmHelper::Controller2, param_all, req, thr));
  RETURN_TRUE
}

void Independent3(const v8::FunctionCallbackInfo<v8::Value>& args) {
  ISOLATE(args);
  VmHelper::ParamWrapper4 param_all(3);
  if (5 == args.Length() &&
    node::Buffer::HasInstance(args[0]) &&
    node::Buffer::HasInstance(args[1]) &&
    node::Buffer::HasInstance(args[2]) &&
    node::Buffer::HasInstance(args[3]) &&
    args[4]->IsFunction()
    ) {
    param_all.name = node::Buffer::Data(args[0]);
    param_all.name_len = node::Buffer::Length(args[0]);
    param_all.p1 = node::Buffer::Data(args[1]);
    param_all.p1_len = node::Buffer::Length(args[1]);
    param_all.p2 = node::Buffer::Data(args[2]);
    param_all.p2_len = node::Buffer::Length(args[2]);
    param_all.p3 = node::Buffer::Data(args[3]);
    param_all.p3_len = node::Buffer::Length(args[3]);
  } else {
    TYPEERROR;
  }
  THREAD;
  INITHELPER(args, 4);
  req->w_t = TYPE_VM;
  req->out = (char*)(new VMRe(thr->AsWeakPtr()));
  thr->message_loop()->PostTask(base::Bind(base::Unretained(VmHelper::GetInstance()),
    &VmHelper::Controller4, param_all, req, thr));
  RETURN_TRUE
}

void Independent4(const v8::FunctionCallbackInfo<v8::Value>& args) {
  ISOLATE(args);
  VmHelper::ParamWrapper4 param_all(4);
  if (6 == args.Length() &&
    node::Buffer::HasInstance(args[0]) &&
    node::Buffer::HasInstance(args[1]) &&
    node::Buffer::HasInstance(args[2]) &&
    node::Buffer::HasInstance(args[3]) &&
    node::Buffer::HasInstance(args[4]) &&
    args[5]->IsFunction()
    ) {
    param_all.name = node::Buffer::Data(args[0]);
    param_all.name_len = node::Buffer::Length(args[0]);
    param_all.p1 = node::Buffer::Data(args[1]);
    param_all.p1_len = node::Buffer::Length(args[1]);
    param_all.p2 = node::Buffer::Data(args[2]);
    param_all.p2_len = node::Buffer::Length(args[2]);
    param_all.p3 = node::Buffer::Data(args[3]);
    param_all.p3_len = node::Buffer::Length(args[3]);
    param_all.p4 = node::Buffer::Data(args[4]);
    param_all.p4_len = node::Buffer::Length(args[4]);
  } else {
    TYPEERROR;
  }
  THREAD;
  INITHELPER(args, 5);
  req->w_t = TYPE_VM;
  req->out = (char*)(new VMRe(thr->AsWeakPtr()));
  thr->message_loop()->PostTask(base::Bind(base::Unretained(VmHelper::GetInstance()),
    &VmHelper::Controller4, param_all, req, thr));
  RETURN_TRUE
}

void Independent5(const v8::FunctionCallbackInfo<v8::Value>& args) {
  ISOLATE(args);
  VmHelper::ParamWrapper8 param_all(5);
  if (7 == args.Length() &&
    node::Buffer::HasInstance(args[0]) &&
    node::Buffer::HasInstance(args[1]) &&
    node::Buffer::HasInstance(args[2]) &&
    node::Buffer::HasInstance(args[3]) &&
    node::Buffer::HasInstance(args[4]) &&
    node::Buffer::HasInstance(args[5]) &&
    args[6]->IsFunction()
    ) {
    param_all.name = node::Buffer::Data(args[0]);
    param_all.name_len = node::Buffer::Length(args[0]);
    param_all.p1 = node::Buffer::Data(args[1]);
    param_all.p1_len = node::Buffer::Length(args[1]);
    param_all.p2 = node::Buffer::Data(args[2]);
    param_all.p2_len = node::Buffer::Length(args[2]);
    param_all.p3 = node::Buffer::Data(args[3]);
    param_all.p3_len = node::Buffer::Length(args[3]);
    param_all.p4 = node::Buffer::Data(args[4]);
    param_all.p4_len = node::Buffer::Length(args[4]);
    param_all.p5 = node::Buffer::Data(args[5]);
    param_all.p5_len = node::Buffer::Length(args[5]);
  } else {
    TYPEERROR;
  }
  THREAD;
  INITHELPER(args, 6);
  req->w_t = TYPE_VM;
  req->out = (char*)(new VMRe(thr->AsWeakPtr()));
  thr->message_loop()->PostTask(base::Bind(base::Unretained(VmHelper::GetInstance()),
    &VmHelper::Controller8, param_all, req, thr));
  RETURN_TRUE
}

void Independent6(const v8::FunctionCallbackInfo<v8::Value>& args) {
  ISOLATE(args);
  VmHelper::ParamWrapper8 param_all(6);
  if (8 == args.Length() &&
    node::Buffer::HasInstance(args[0]) &&
    node::Buffer::HasInstance(args[1]) &&
    node::Buffer::HasInstance(args[2]) &&
    node::Buffer::HasInstance(args[3]) &&
    node::Buffer::HasInstance(args[4]) &&
    node::Buffer::HasInstance(args[5]) &&
    node::Buffer::HasInstance(args[6]) &&
    args[7]->IsFunction()
    ) {
    param_all.name = node::Buffer::Data(args[0]);
    param_all.name_len = node::Buffer::Length(args[0]);
    param_all.p1 = node::Buffer::Data(args[1]);
    param_all.p1_len = node::Buffer::Length(args[1]);
    param_all.p2 = node::Buffer::Data(args[2]);
    param_all.p2_len = node::Buffer::Length(args[2]);
    param_all.p3 = node::Buffer::Data(args[3]);
    param_all.p3_len = node::Buffer::Length(args[3]);
    param_all.p4 = node::Buffer::Data(args[4]);
    param_all.p4_len = node::Buffer::Length(args[4]);
    param_all.p5 = node::Buffer::Data(args[5]);
    param_all.p5_len = node::Buffer::Length(args[5]);
    param_all.p6 = node::Buffer::Data(args[6]);
    param_all.p6_len = node::Buffer::Length(args[6]);
  } else {
    TYPEERROR;
  }
  THREAD;
  INITHELPER(args, 7);
  req->w_t = TYPE_VM;
  req->out = (char*)(new VMRe(thr->AsWeakPtr()));
  thr->message_loop()->PostTask(base::Bind(base::Unretained(VmHelper::GetInstance()),
    &VmHelper::Controller8, param_all, req, thr));
  RETURN_TRUE
}

void Independent7(const v8::FunctionCallbackInfo<v8::Value>& args) {
  ISOLATE(args);
  VmHelper::ParamWrapper8 param_all(7);
  if (9 == args.Length() &&
    node::Buffer::HasInstance(args[0]) &&
    node::Buffer::HasInstance(args[1]) &&
    node::Buffer::HasInstance(args[2]) &&
    node::Buffer::HasInstance(args[3]) &&
    node::Buffer::HasInstance(args[4]) &&
    node::Buffer::HasInstance(args[5]) &&
    node::Buffer::HasInstance(args[6]) &&
    node::Buffer::HasInstance(args[7]) &&
    args[8]->IsFunction()
    ) {
    param_all.name = node::Buffer::Data(args[0]);
    param_all.name_len = node::Buffer::Length(args[0]);
    param_all.p1 = node::Buffer::Data(args[1]);
    param_all.p1_len = node::Buffer::Length(args[1]);
    param_all.p2 = node::Buffer::Data(args[2]);
    param_all.p2_len = node::Buffer::Length(args[2]);
    param_all.p3 = node::Buffer::Data(args[3]);
    param_all.p3_len = node::Buffer::Length(args[3]);
    param_all.p4 = node::Buffer::Data(args[4]);
    param_all.p4_len = node::Buffer::Length(args[4]);
    param_all.p5 = node::Buffer::Data(args[5]);
    param_all.p5_len = node::Buffer::Length(args[5]);
    param_all.p6 = node::Buffer::Data(args[6]);
    param_all.p6_len = node::Buffer::Length(args[6]);
    param_all.p7 = node::Buffer::Data(args[7]);
    param_all.p7_len = node::Buffer::Length(args[7]);
  } else {
    TYPEERROR;
  }
  THREAD;
  INITHELPER(args, 8);
  req->w_t = TYPE_VM;
  req->out = (char*)(new VMRe(thr->AsWeakPtr()));
  thr->message_loop()->PostTask(base::Bind(base::Unretained(VmHelper::GetInstance()),
    &VmHelper::Controller8, param_all, req, thr));
  RETURN_TRUE
}

void Independent8(const v8::FunctionCallbackInfo<v8::Value>& args) {
  ISOLATE(args);
  VmHelper::ParamWrapper8 param_all(8);
  if (10 == args.Length() &&
    node::Buffer::HasInstance(args[0]) &&
    node::Buffer::HasInstance(args[1]) &&
    node::Buffer::HasInstance(args[2]) &&
    node::Buffer::HasInstance(args[3]) &&
    node::Buffer::HasInstance(args[4]) &&
    node::Buffer::HasInstance(args[5]) &&
    node::Buffer::HasInstance(args[6]) &&
    node::Buffer::HasInstance(args[7]) &&
    node::Buffer::HasInstance(args[8]) &&
    args[9]->IsFunction()
    ) {
    param_all.name = node::Buffer::Data(args[0]);
    param_all.name_len = node::Buffer::Length(args[0]);
    param_all.p1 = node::Buffer::Data(args[1]);
    param_all.p1_len = node::Buffer::Length(args[1]);
    param_all.p2 = node::Buffer::Data(args[2]);
    param_all.p2_len = node::Buffer::Length(args[2]);
    param_all.p3 = node::Buffer::Data(args[3]);
    param_all.p3_len = node::Buffer::Length(args[3]);
    param_all.p4 = node::Buffer::Data(args[4]);
    param_all.p4_len = node::Buffer::Length(args[4]);
    param_all.p5 = node::Buffer::Data(args[5]);
    param_all.p5_len = node::Buffer::Length(args[5]);
    param_all.p6 = node::Buffer::Data(args[6]);
    param_all.p6_len = node::Buffer::Length(args[6]);
    param_all.p7 = node::Buffer::Data(args[7]);
    param_all.p7_len = node::Buffer::Length(args[7]);
    param_all.p8 = node::Buffer::Data(args[8]);
    param_all.p8_len = node::Buffer::Length(args[8]);
  } else {
    TYPEERROR;
  }
  THREAD;
  INITHELPER(args, 9);
  req->w_t = TYPE_VM;
  req->out = (char*)(new VMRe(thr->AsWeakPtr()));
  thr->message_loop()->PostTask(base::Bind(base::Unretained(VmHelper::GetInstance()),
    &VmHelper::Controller8, param_all, req, thr));
  RETURN_TRUE
}

static void Terminate(void*) {
  RcibHelper::GetInstance()->Terminate();
}

template <typename TypeName>
inline void NODE_CREATE_FUNCTION(const TypeName& target) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();

    v8::Local<v8::ObjectTemplate> t = v8::ObjectTemplate::New(isolate);
    t->SetInternalFieldCount(1);
    v8::Local<v8::Object> addon_data = t->NewInstance(context).ToLocalChecked();

    v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, NewThread, addon_data);
    tpl->SetClassName(v8::String::NewFromUtf8(
      isolate, "THREAD", v8::NewStringType::kNormal).ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(tpl, "close", Close);
    NODE_SET_PROTOTYPE_METHOD(tpl, "isRunning", IsRunning);
    NODE_SET_PROTOTYPE_METHOD(tpl, "queNum", QueueNum);
    NODE_SET_PROTOTYPE_METHOD(tpl, "Independent0", Independent0);
    NODE_SET_PROTOTYPE_METHOD(tpl, "Independent1", Independent1);
    NODE_SET_PROTOTYPE_METHOD(tpl, "Independent2", Independent2);
    NODE_SET_PROTOTYPE_METHOD(tpl, "Independent3", Independent3);
    NODE_SET_PROTOTYPE_METHOD(tpl, "Independent4", Independent4);
    NODE_SET_PROTOTYPE_METHOD(tpl, "Independent5", Independent5);
    NODE_SET_PROTOTYPE_METHOD(tpl, "Independent6", Independent6);
    NODE_SET_PROTOTYPE_METHOD(tpl, "Independent7", Independent7);
    NODE_SET_PROTOTYPE_METHOD(tpl, "Independent8", Independent8);

    v8::Local<v8::Function> constructor = tpl->GetFunction(context).ToLocalChecked();
    addon_data->SetInternalField(0, constructor);
    target->Set(context, v8::String::NewFromUtf8(
      isolate, "THREAD", v8::NewStringType::kNormal).ToLocalChecked(),
      constructor).FromJust();

}

#define NODE_CREATE_FUNCTION NODE_CREATE_FUNCTION

void Init(v8::Local<v8::Object> target) {
  NODE_CREATE_FUNCTION(target);
  RcibHelper::GetInstance()->Init();
  node::AtExit(Terminate);

}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)
