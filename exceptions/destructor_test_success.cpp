#include <iostream>

#include "exceptions.h"

DECLARE_EXCEPTIONS
    EXCEPTION_A,
    EXCEPTION_B
END

CLASS(Data)
public:
    Data(int data) : data(data) {
        std::cout << "Data() : " << data << std::endl;
    }

    virtual ~Data() {
        std::cout << "~Data() :  " << data << std::endl;
    }

    int data;
END

void f(Data a) {
    Data b(1337);
    if (a.data > 5) {
        THROW(EXCEPTION_A);
    }
    Data c(420);
}

int main() {
    TRY (
        Data a(0);
        f({1});
        f({3});
        f({37});
    )
    CATCH(EXCEPTION_A,
        std::cout << "Caught EXCEPTION_A in main()" << std::endl;
    )
    CATCH(EXCEPTION_B,
        std::cout << "Caught EXCEPTION_B in main()" << std::endl;
    )
    END_TRY
}
