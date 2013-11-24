#include <sys/ioctl.h>
#include <v8.h>
#include <node.h>
#include <unistd.h>

using namespace v8;
using namespace node;

namespace NodeOS
{
  
  static Handle<Value> SetControllingTTY(const Arguments& args) {
    HandleScope scope;
    int fd = args[0]->Int32Value();
    int rt = ioctl (fd, TIOCSCTTY, NULL);
    return scope.Close(Integer::New(rt));
  }

  static Handle<Value> VHangUp(const Arguments& args) {
    HandleScope scope;
    int ret = 1; vhangup();
    return scope.Close(Integer::New(ret));
  }
  
  static Handle<Value> SetSID(const Arguments& args) {
    HandleScope scope;
    int sid = setsid();
    return scope.Close(Integer::New(sid));
  }
  
  static Handle<Value> Fork(const Arguments& args) {
    HandleScope scope;
    int pid = fork();
    return scope.Close(Integer::New(pid));
  }
  
  static Handle<Value> Dup(const Arguments& args) {
    HandleScope scope;
    int fd = args[0]->Int32Value();
    int dd = dup(fd);
    return scope.Close(Integer::New(dd));
  }
  
  static void init(Handle<Object> target) {
    target->Set(String::NewSymbol("dup"),
      FunctionTemplate::New(Dup)->GetFunction());
    target->Set(String::NewSymbol("fork"),
      FunctionTemplate::New(Fork)->GetFunction());
    target->Set(String::NewSymbol("setControllingTTY"),
      FunctionTemplate::New(SetControllingTTY)->GetFunction());
    target->Set(String::NewSymbol("vhangup"),
      FunctionTemplate::New(VHangUp)->GetFunction());
    target->Set(String::NewSymbol("setsid"),
      FunctionTemplate::New(SetSID)->GetFunction());
  };

}

NODE_MODULE(binding, NodeOS::init)
