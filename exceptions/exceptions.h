#pragma once

#include <csetjmp>
#include <stack>
#include <cassert>

class Object;

namespace {

    class JmpBuf : public __jmp_buf_tag
    { };

    std::stack<JmpBuf> _environments;
    std::stack<std::stack<Object*>> _objects;

    bool _unwinding_stack = false;
}

static std::stack<Object*>& _get_current_environment_objects() {
    return _objects.top();
}

class Object {
public:
    Object() {
        _get_current_environment_objects().push(this);
    }

    virtual ~Object() {
        assert(("Wrong destruction order", _get_current_environment_objects().top() == this));
        if (!_unwinding_stack) {
            _get_current_environment_objects().pop();
        }
    }
};

static void _unwind_stack() {
    assert(("Double exception", !_unwinding_stack));
    _unwinding_stack = true;
    while (!_get_current_environment_objects().empty()) {
        auto object = _get_current_environment_objects().top();
        object->~Object();
        _get_current_environment_objects().pop();
    }
    _unwinding_stack = false;
}

#define DECLARE_EXCEPTIONS \
enum Exception { \
    NO_EXCEPTION = 0,

#define CLASS(class_name) \
class class_name : public Object {

#define END };

#define TRY(statements) { \
    _environments.emplace(); \
    _objects.emplace(); \
    int exception = setjmp(&_environments.top()); \
    switch (exception) { \
        case NO_EXCEPTION: \
            { statements } \
            break;

#define CATCH(exception, statements) \
        case exception: \
            { statements } \
            break;

#define END_TRY \
        default: \
            _environments.pop(); \
            assert(("Non destroyed objects on stack", _get_current_environment_objects().empty())); \
            _objects.pop(); \
            assert(("Unhandled exception", !_environments.empty())); \
            longjmp(&_environments.top(), exception); \
    } \
}

#define THROW(exception) { \
    _unwind_stack(); \
    longjmp(&_environments.top(), exception); \
}

