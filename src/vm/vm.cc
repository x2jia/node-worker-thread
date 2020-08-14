#include <iostream>
#include "../node/rcib.h"
#include "vm.h"

VmHelper::ParamWrapper2::ParamWrapper2(int pNum) {
  this->pNum = pNum;
  p1 = p2 = NULL;
  p1_len = p2_len = 0;
  name = NULL;
  name_len = 0;
}

VmHelper::ParamWrapper4::ParamWrapper4(int pNum) {
  this->pNum = pNum;
  p1 = p2 = p3 = p4 = NULL;
  p1_len = p2_len = p3_len = p4_len = 0;
  name = NULL;
  name_len = NULL;
}

VmHelper::ParamWrapper8::ParamWrapper8(int pNum) {
  this->pNum = pNum;
  p1 = p2 = p3 = p4 = p5 = p6 = p7 = p8 = NULL;
  p1_len = p2_len = p3_len = p4_len = p5_len = p6_len = p7_len = p8_len = 0;
  name = NULL;
  name_len = 0;
}

//constructor
VmHelper::VmHelper() {
  Init();
}

void VmHelper::Init() {
}

//static
VmHelper* VmHelper::GetInstance(){
  static VmHelper This;
  return &This;
}

void VmHelper::Controller2(ParamWrapper2 params, rcib::async_req * req, base::Thread *thread) {
  VMRe *hre = reinterpret_cast<VMRe *>(req->out);
  v8::Isolate* isolate = thread->Isolate();
  do {
    v8::HandleScope scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Object> globalObj = context->Global();
    v8::Local<v8::Value> globalFunction =
      globalObj->Get(context, v8::String::NewFromUtf8(isolate,
                      params.name, 
                      v8::NewStringType::kNormal, 
                      params.name_len)
                           .ToLocalChecked()).ToLocalChecked();
    if (globalFunction.IsEmpty() || !globalFunction->IsFunction()) {
      std::string errMsg;
      errMsg = "error: no function";
      rcib::RcibHelper::EMark2(req, errMsg);
      break;
    }
    v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(globalFunction);
    v8::Local<v8::Value> tmpCallVal;
    switch (params.pNum) {
      case 0: {
        tmpCallVal = func->Call(context, globalObj, 0, nullptr).ToLocalChecked();
      }
        break;
      case 1: {
        v8::Local<v8::Value> v1 = v8::String::NewFromUtf8(isolate, params.p1, v8::NewStringType::kNormal, params.p1_len)
          .ToLocalChecked();
        v8::Local<v8::Value> args[1] = { v1 };
        tmpCallVal = func->Call(context, globalObj, 1, args).ToLocalChecked();
      }
        break;
      case 2: {
        v8::Local<v8::Value> v1 = v8::String::NewFromUtf8(isolate, params.p1, v8::NewStringType::kNormal, params.p1_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v2 = v8::String::NewFromUtf8(isolate, params.p2, v8::NewStringType::kNormal, params.p2_len)
          .ToLocalChecked();
        v8::Local<v8::Value> args[2] = { v1, v2 };
        tmpCallVal = func->Call(context, globalObj, 2, args).ToLocalChecked();
      }
        break;
      default: {
        assert(0);
      }
        break;
    }
    v8::Local<v8::String> V8String = tmpCallVal->ToString(context).ToLocalChecked();
    int len = V8String->Utf8Length(isolate);
    char *p = (char *)malloc(len + 1);
    V8String->WriteUtf8(isolate, p);
    hre->_data = (uint8_t *)p;
    req->result = len;
  } while (false);

  rcib::RcibHelper::GetInstance()->Uv_Send(req, nullptr);
}

void VmHelper::Controller4(ParamWrapper4 params, rcib::async_req * req, base::Thread *thread) {
  VMRe *hre = reinterpret_cast<VMRe *>(req->out);
  v8::Isolate* isolate = thread->Isolate();
  do {
    v8::HandleScope scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Object> globalObj = context->Global();
    v8::Local<v8::Value>  globalFunction =
      globalObj->Get(context, v8::String::NewFromUtf8(isolate,
      params.name,
      v8::NewStringType::kNormal,
      params.name_len)
      .ToLocalChecked()).ToLocalChecked();
    if (globalFunction.IsEmpty() || !globalFunction->IsFunction()) {
      std::string errMsg;
      errMsg = "error: no function";
      rcib::RcibHelper::EMark2(req, errMsg);
      break;
    }
    v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(globalFunction);
    v8::Local<v8::Value> tmpCallVal;
    switch (params.pNum) {
      case 3: {
        v8::Local<v8::Value> v1 = v8::String::NewFromUtf8(isolate, params.p1, v8::NewStringType::kNormal, params.p1_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v2 = v8::String::NewFromUtf8(isolate, params.p2, v8::NewStringType::kNormal, params.p2_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v3 = v8::String::NewFromUtf8(isolate, params.p3, v8::NewStringType::kNormal, params.p3_len)
          .ToLocalChecked();
        v8::Local<v8::Value> args[3] = { v1, v2, v3 };
        tmpCallVal = func->Call(context, globalObj, 3, args).ToLocalChecked();
      }
        break;
      case 4: {
        v8::Local<v8::Value> v1 = v8::String::NewFromUtf8(isolate, params.p1, v8::NewStringType::kNormal, params.p1_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v2 = v8::String::NewFromUtf8(isolate, params.p2, v8::NewStringType::kNormal, params.p2_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v3 = v8::String::NewFromUtf8(isolate, params.p3, v8::NewStringType::kNormal, params.p3_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v4 = v8::String::NewFromUtf8(isolate, params.p4, v8::NewStringType::kNormal, params.p4_len)
          .ToLocalChecked();
        v8::Local<v8::Value> args[4] = { v1, v2, v3, v4 };
        tmpCallVal = func->Call(context, globalObj, 4, args).ToLocalChecked();
      }
        break;
      default: {
        assert(0);
      }
        break;
    }
    v8::Local<v8::String> V8String = tmpCallVal->ToString(context).ToLocalChecked();
    int len = V8String->Utf8Length(isolate);
    char *p = (char *)malloc(len + 1);
    V8String->WriteUtf8(isolate, p);
    hre->_data = (uint8_t *)p;
    req->result = len;
  } while (false);

  rcib::RcibHelper::GetInstance()->Uv_Send(req, nullptr);
}

void VmHelper::Controller8(ParamWrapper8 params, rcib::async_req * req, base::Thread *thread) {
  VMRe *hre = reinterpret_cast<VMRe *>(req->out);
  v8::Isolate* isolate = thread->Isolate();
  do {
    v8::HandleScope scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Object> globalObj = context->Global();
    v8::Local<v8::Value>  globalFunction =
      globalObj->Get(context, v8::String::NewFromUtf8(isolate,
      params.name,
      v8::NewStringType::kNormal,
      params.name_len)
      .ToLocalChecked()).ToLocalChecked();
    if (globalFunction.IsEmpty() || !globalFunction->IsFunction()) {
      std::string errMsg;
      errMsg = "error: no function";
      rcib::RcibHelper::EMark2(req, errMsg);
      break;
    }
    v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(globalFunction);
    v8::Local<v8::Value> tmpCallVal;
    switch (params.pNum) {
      case 5: {
        v8::Local<v8::Value> v1 = v8::String::NewFromUtf8(isolate, params.p1, v8::NewStringType::kNormal, params.p1_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v2 = v8::String::NewFromUtf8(isolate, params.p2, v8::NewStringType::kNormal, params.p2_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v3 = v8::String::NewFromUtf8(isolate, params.p3, v8::NewStringType::kNormal, params.p3_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v4 = v8::String::NewFromUtf8(isolate, params.p4, v8::NewStringType::kNormal, params.p4_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v5 = v8::String::NewFromUtf8(isolate, params.p5, v8::NewStringType::kNormal, params.p5_len)
          .ToLocalChecked();
        v8::Local<v8::Value> args[5] = { v1, v2, v3, v4, v5 };
        tmpCallVal = func->Call(context, globalObj, 5, args).ToLocalChecked();
      }
        break;
      case 6: {
        v8::Local<v8::Value> v1 = v8::String::NewFromUtf8(isolate, params.p1, v8::NewStringType::kNormal, params.p1_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v2 = v8::String::NewFromUtf8(isolate, params.p2, v8::NewStringType::kNormal, params.p2_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v3 = v8::String::NewFromUtf8(isolate, params.p3, v8::NewStringType::kNormal, params.p3_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v4 = v8::String::NewFromUtf8(isolate, params.p4, v8::NewStringType::kNormal, params.p4_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v5 = v8::String::NewFromUtf8(isolate, params.p5, v8::NewStringType::kNormal, params.p5_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v6 = v8::String::NewFromUtf8(isolate, params.p6, v8::NewStringType::kNormal, params.p6_len)
          .ToLocalChecked();
        v8::Local<v8::Value> args[6] = { v1, v2, v3, v4, v5, v6 };
        tmpCallVal = func->Call(context, globalObj, 6, args).ToLocalChecked();
      }
        break;
      case 7: {
        v8::Local<v8::Value> v1 = v8::String::NewFromUtf8(isolate, params.p1, v8::NewStringType::kNormal, params.p1_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v2 = v8::String::NewFromUtf8(isolate, params.p2, v8::NewStringType::kNormal, params.p2_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v3 = v8::String::NewFromUtf8(isolate, params.p3, v8::NewStringType::kNormal, params.p3_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v4 = v8::String::NewFromUtf8(isolate, params.p4, v8::NewStringType::kNormal, params.p4_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v5 = v8::String::NewFromUtf8(isolate, params.p5, v8::NewStringType::kNormal, params.p5_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v6 = v8::String::NewFromUtf8(isolate, params.p6, v8::NewStringType::kNormal, params.p6_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v7 = v8::String::NewFromUtf8(isolate, params.p7, v8::NewStringType::kNormal, params.p7_len)
          .ToLocalChecked();
        v8::Local<v8::Value> args[7] = { v1, v2, v3, v4, v5, v6, v7 };
        tmpCallVal = func->Call(context, globalObj, 7, args).ToLocalChecked();
      }
        break;
      case 8: {
        v8::Local<v8::Value> v1 = v8::String::NewFromUtf8(isolate, params.p1, v8::NewStringType::kNormal, params.p1_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v2 = v8::String::NewFromUtf8(isolate, params.p2, v8::NewStringType::kNormal, params.p2_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v3 = v8::String::NewFromUtf8(isolate, params.p3, v8::NewStringType::kNormal, params.p3_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v4 = v8::String::NewFromUtf8(isolate, params.p4, v8::NewStringType::kNormal, params.p4_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v5 = v8::String::NewFromUtf8(isolate, params.p5, v8::NewStringType::kNormal, params.p5_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v6 = v8::String::NewFromUtf8(isolate, params.p6, v8::NewStringType::kNormal, params.p6_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v7 = v8::String::NewFromUtf8(isolate, params.p7, v8::NewStringType::kNormal, params.p7_len)
          .ToLocalChecked();
        v8::Local<v8::Value> v8 = v8::String::NewFromUtf8(isolate, params.p8, v8::NewStringType::kNormal, params.p8_len)
          .ToLocalChecked();
        v8::Local<v8::Value> args[8] = { v1, v2, v3, v4, v5, v6, v7, v8 };
        tmpCallVal = func->Call(context, globalObj, 8, args).ToLocalChecked();
      }
        break;
      default: {
        assert(0);
      }
        break;
    }
    v8::Local<v8::String> V8String = tmpCallVal->ToString(context).ToLocalChecked();
    int len = V8String->Utf8Length(isolate);
    char *p = (char *)malloc(len + 1);
    V8String->WriteUtf8(isolate, p);
    hre->_data = (uint8_t *)p;
    req->result = len;
  } while (false);

  rcib::RcibHelper::GetInstance()->Uv_Send(req, nullptr);
}
