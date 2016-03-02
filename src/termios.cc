#include <sys/ioctl.h>
#include <v8.h>
#include <node.h>
#include <unistd.h>
#include <nan.h>

using namespace v8;
using namespace node;

NAN_METHOD(SetControllingTTY) {
  Nan::HandleScope scope;

  int fd = info[0]->Int32Value();
  int rt = ioctl (fd, TIOCSCTTY, NULL);

  info.GetReturnValue().Set(Nan::New<Integer>(rt));
}

NAN_METHOD(VHangUp) {
  Nan::HandleScope scope;

  int ret = 1;
  vhangup();

  info.GetReturnValue().Set(Nan::New<Integer>(ret));
}

NAN_METHOD(SetSID) {
  Nan::HandleScope scope;

  int sid = setsid();

  info.GetReturnValue().Set(Nan::New<Integer>(sid));
}

NAN_METHOD(Fork) {
  Nan::HandleScope scope;

  int pid = fork();

  info.GetReturnValue().Set(Nan::New<Integer>(pid));
}

NAN_METHOD(Dup) {
  Nan::HandleScope scope;

  int fd = info[0]->Int32Value();
  int dd = dup(fd);

  info.GetReturnValue().Set(Nan::New<Integer>(dd));
}

void init(Handle<Object> exports) {
  exports->Set(Nan::New<String>("dup").ToLocalChecked(),
    Nan::New<FunctionTemplate>(Dup)->GetFunction());
  exports->Set(Nan::New<String>("fork").ToLocalChecked(),
    Nan::New<FunctionTemplate>(Fork)->GetFunction());
  exports->Set(Nan::New<String>("setControllingTTY").ToLocalChecked(),
    Nan::New<FunctionTemplate>(SetControllingTTY)->GetFunction());
  exports->Set(Nan::New<String>("vhangup").ToLocalChecked(),
    Nan::New<FunctionTemplate>(VHangUp)->GetFunction());
  exports->Set(Nan::New<String>("setsid").ToLocalChecked(),
    Nan::New<FunctionTemplate>(SetSID)->GetFunction());
}

NODE_MODULE(binding, init)
