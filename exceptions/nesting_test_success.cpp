#include <iostream>

#include "exceptions.h"

DECLARE_EXCEPTIONS
    EXCEPTION_A,
    EXCEPTION_B
END

void throwing_a() {
    THROW(EXCEPTION_A);
}

void throwing_b() {
    THROW(EXCEPTION_B);
}

void passing_b() {
    TRY (
        throwing_a();
    )
    CATCH(EXCEPTION_A,
        std::cout << "Caught EXCEPTION_A in passing_b()" << std::endl;
    )
    END_TRY

    TRY (
        throwing_b();
    )
    CATCH(EXCEPTION_A,
        std::cout << "Caught EXCEPTION_A in passing_b()" << std::endl;
    )
    END_TRY
}

int main() {
    TRY (
        passing_b();
    )
    CATCH(EXCEPTION_B,
        std::cout << "Caught EXCEPTION_B in main()" << std::endl;
    )
    END_TRY
}
