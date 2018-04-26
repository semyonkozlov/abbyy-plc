#include <cstring>

struct VtableInitializer
{
    template<typename F>
    VtableInitializer(F* vtable, int func_index, F function)
    {
        vtable[func_index] = function;
    }

    template<typename FuncBase, typename FuncDerived>
    VtableInitializer(FuncBase* vtable_base, FuncDerived* vtable_derived, int num_base_methods)
    {
        static_assert(sizeof(FuncDerived) == sizeof(FuncBase));
        std::memcpy(vtable_derived, vtable_base, num_base_methods * sizeof(FuncDerived));
    }
};

#define CLASS(Class) struct Class { \
    Class(); \
    typedef void(*Func)(Class*); \
    Func* _v_ptr;

#define END() };

#define BEGIN_INTERFACE(Class) enum Class##_methods {

#define DECLARE_METHOD(method) method,

#define END_INTERFACE(Class) Class##_num_methods \
}; \
Class::Func Class##_vtbl[Class##_num_methods] = {0}; \
Class::Class() : _v_ptr(Class##_vtbl) {}

#define BEGIN_METHOD(Class, method) void Class##_##method(Class* self) {
#define END_METHOD(Class, method) } \
VtableInitializer Class##_##method##_initializer(Class##_vtbl, (method), Class##_##method);

#define CALL_METHOD(object_ptr, method) (*(object_ptr)->_v_ptr[(method)])((object_ptr))

#define DERIVED_CLASS(Derived, Base) struct Derived : Base { \
    typedef void(*Func)(Derived*); \
    Derived();

#define BEGIN_DERIVED_INTERFACE(Derived, Base) enum Derived##_methods { \
    Derived##_interface_begin = Base##_num_methods,

#define END_DERIVED_INTERFACE(Derived, Base) Derived##_num_methods \
}; \
Derived::Func Derived##_vtbl[Derived##_num_methods] = {0}; \
Derived::Derived() { _v_ptr = reinterpret_cast<Base::Func*>(Derived##_vtbl); } \
VtableInitializer Derived##_vtable_initizlizer(Base##_vtbl, Derived##_vtbl, Base##_num_methods);

