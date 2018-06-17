#include <iostream>

#include "exceptions.h"

DECLARE_EXCEPTIONS
    EXCEPTION_A,
    EXCEPTION_B,
    EXCEPTION_C
END

void throwing_a() {
    TRY (
        THROW(EXCEPTION_A);
    )
    CATCH(EXCEPTION_B,
        std::cout << "Caught EXCEPTION_B in throwing_a()" << std::endl;
    )
    END_TRY
}

int main() {
    TRY (
        throwing_a();
    )
    CATCH(EXCEPTION_C,
        std::cout << "Caught EXCEPTION_C main()" << std::endl;
    )
    END_TRY
}
