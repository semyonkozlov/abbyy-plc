#include <iostream>

#include "vtable.h"

CLASS(Base)
    int a;
END()

BEGIN_INTERFACE(Base)
    DECLARE_METHOD(both)
    DECLARE_METHOD(only_base)
END_INTERFACE(Base)

BEGIN_METHOD(Base, both)
    self->a = 0;
    std::cout << "Base::both: a = " << self->a << std::endl;
END_METHOD(Base, both)

BEGIN_METHOD(Base, only_base)
    std::cout << "Base::only_base" << std::endl;
END_METHOD(Base, only_base)

DERIVED_CLASS(Derived, Base)
    int b;
END()

BEGIN_DERIVED_INTERFACE(Derived, Base)
    DECLARE_METHOD(only_derived)
END_DERIVED_INTERFACE(Derived, Base)

BEGIN_METHOD(Derived, only_derived)
    std::cout << "Derived::only_derived" << std::endl;
END_METHOD(Derived, only_derived)

BEGIN_METHOD(Derived, both)
    self->b = 1;
    std::cout << "Derived::both: b = " << self->b << std::endl;
END_METHOD(Derived, both)

int main()
{
    Base base;
    base.a = -1;
    Derived derived;
    Base* base_but_really_derived = new Derived;
    CALL_METHOD(&base, both);
    CALL_METHOD(base_but_really_derived, both);
    CALL_METHOD(base_but_really_derived, only_base);
    CALL_METHOD(base_but_really_derived, only_derived);
    return 0;
}