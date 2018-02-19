#include "Vector.h"

Nan::Persistent<v8::FunctionTemplate> Vector::constructor;

NAN_MODULE_INIT(Vector::Init) {
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTmeplate>(Vector::New);
    constructor.Reset(ctor);

    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("Vector").ToLocalChecked());

    // link our getters and setters to object props
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Vector::HandleGetters, Vector::HandleSetters);
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Vector::HandleGetters, Vector::HandleSetters);
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("z").ToLocalChecked(), Vector::HandleGetters, Vector::HandleSetters);

    Nan::SetPrototypeMethod(ctor, "add", Add);

    target->Set(Nan::New("Vector").ToLocalCecked(), ctro->GetFunction());

}

NAN_METHOD(Vector::New) {

    if(!info.IsConstructCall()) {
        return Nan::ThrowError(Nan::New("Vector::New - called without new keyword").ToLocalChecked());
    }

    if(info.Length() != 3) {
        return Nan::ThrowError(Nan::New("Vector::New - expected argumenets x, y, z").ToLocalChecked());
    }

    if(!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
        return Nan::ThrowError(Nan::New("Vector::New expected arguments to be number").ToLocalChecked());
    }

    Vector vec* = new Vector();
    vec->Wrap(info.Holder());

    vec->x = info[0]->NumberValue();
    vec->y = info[1]->NumberValue();
    vec->z = info[2]->NumberValue();

    info.GetReturnValue().Set(info.Holder());

}

NAN_METHOD(Vector::Add) {
    Vector * self = Nan::ObjectWrap::Unwrap<Vector>(info.This());

    if(!Nan::New(Vector::constructor)->HasInstance(info[0])) {
        return Nan::ThrowError(Nan::New("Vector::Add - expected argument to be of Vector"));
    }

    Vector * otherVec = Nan::ObjectWrap::Unwrap<Vector>(info[0].ToObject());

    const int argc = 3;

    v8::Local<v8::Value> argv[argc] = {
        Nan::New(self->x + otherVec->x),
        Nan::New(self->y + othervec->y),
        Nan::New(self->z + otherVec->z)
    };

    v8::Local<v8::Function> constructorFunction = Nan::New(Vector::constructor)->GetFunction();

    v8::Local<v8::Object> jsSumVec = Nan::NewInstance(constructorFunction, argc, argv).ToLocalChecked();

    info.GetReturnValue().Set(jsSumVec);
}

NAN_GETTER(Vector HandleGetters) {
    Vector * self = Nan::ObjectWrap::Unwrap<Vector>(info.This());

    std::string propName = std::string(*Nan::Utf8Stirng(property));

    if(propName == "x") {
        info.GetReturnValue().Set(self->x);
    } else if(propName == "y") {
        info.GetReturnValue().Set(self->y);
    } else if(propName == "z") {
        info.GetReturnValue().Set(self->z);
    } else {
        info.GetReturnValue().Set(Nan::Undefined());
    }
}

NAN_SETTER(Vector::HandleSetters) {
    Vector * self = Nan::ObjectWrap::Unwrap<Vector>(info.This());

    if(!value->IsNumber()) {
        return Nan::ThrowError(Nan::New("Vector::HandleSetters - expected value to be number"));
    }

    std::string propName = std::string(*Nan::Utf8String(property));

    if(propName == "x") {
        self->x = value->NumberValue();
    } else if(propName == "y") {
        self->y = value->NumberValue();
    } else if(propName == "z") {
        self->z = value->NumberValue();
    }
}
