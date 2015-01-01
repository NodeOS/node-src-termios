#include <sys/ioctl.h>
#include <v8.h>
#include <node.h>
#include <unistd.h>
#include <nan.h>

using namespace v8;
using namespace node;

NAN_METHOD(SetControllingTTY) {
  NanScope();
  int fd = args[0]->Int32Value();
  int rt = ioctl (fd, TIOCSCTTY, NULL);
  NanReturnValue(NanNew<Integer>(rt));
}

NAN_METHOD(VHangUp) {
  NanScope();
  int ret = 1; vhangup();
  NanReturnValue(NanNew<Integer>(ret));
}
  
NAN_METHOD(SetSID) {
  NanScope();
  int sid = setsid();
  NanReturnValue(NanNew<Integer>(sid));
}
  
NAN_METHOD(Fork) {
  NanScope();
  int pid = fork();
  NanReturnValue(NanNew<Integer>(pid));
}
  
NAN_METHOD(Dup) {
  NanScope();
  int fd = args[0]->Int32Value();
  int dd = dup(fd);
  NanReturnValue(NanNew<Integer>(dd));
}

void init(Handle<Object> exports) {
  exports->Set(NanNew<String>("dup"),
    NanNew<FunctionTemplate>(Dup)->GetFunction());
  exports->Set(NanNew<String>("fork"),
    NanNew<FunctionTemplate>(Fork)->GetFunction());
  exports->Set(NanNew<String>("setControllingTTY"),
    NanNew<FunctionTemplate>(SetControllingTTY)->GetFunction());
  exports->Set(NanNew<String>("vhangup"),
    NanNew<FunctionTemplate>(VHangUp)->GetFunction());
  exports->Set(NanNew<String>("setsid"),
    NanNew<FunctionTemplate>(SetSID)->GetFunction());
}

NODE_MODULE(binding, init)
