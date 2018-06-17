#include <iostream>

#include "exceptions.h"

DECLARE_EXCEPTIONS
    EXCEPTION_A,
    EXCEPTION_B,
    EXCEPTION_C,
    EXCEPTION_D
END

CLASS(NotThrowing)
public:
    NotThrowing(int data) : data(data) {
        std::cout << "NotThrowing() : " << data << std::endl;
    }

    virtual ~NotThrowing() {
        std::cout << "~NotThrowing() : " << data << std::endl;
    }

    int data;
END

CLASS(ThrowingInDestructor)
public:
    ThrowingInDestructor(int data) : data(data) {
        std::cout << "ThrowingInDestructor() : " << data << std::endl;
    }

    virtual ~ThrowingInDestructor() {
        std::cout << "~ThrowingInDestructor() : " << data << std::endl;
        THROW(EXCEPTION_D);
    }

    int data;
END

int main() {
    TRY (
        NotThrowing not_throwing = 1;
        THROW(EXCEPTION_A)
    )
    CATCH(EXCEPTION_A,
        std::cout << "Caught EXCEPTION_A" << std::endl;
    )
    CATCH(EXCEPTION_B,
        std::cout << "Caught EXCEPTION_B" << std::endl;
    )
    END_TRY

    TRY (
        ThrowingInDestructor throwing = 2;
        THROW(EXCEPTION_B);
    )
    CATCH(EXCEPTION_A,
        std::cout << "Caught EXCEPTION_A" << std::endl;
    )
    CATCH(EXCEPTION_B,
        std::cout << "Caught EXCEPTION_B" << std::endl;
    )
    END_TRY
}
