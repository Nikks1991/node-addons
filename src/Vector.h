#include <nan.h>;

class Vector : public Nan::ObjectWrap {
public:
    double x;
    double y;
    double z;

    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
    static NAN_METHOD(Add);

    static NAN_GETTERS(HandleGetters);
    static NAN_SETTERS(HandleSetters);

    static Nan::Persistent<v8::FunctionTemplate> constructor;
};
