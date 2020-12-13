#include <Menu.h>
#include <iostream>

int main() {
    try {
        view::menu();
    }
    catch (...) {
        std::cout << "received unhandled exception" << std::endl;
        return 0;
    }
    return 0;
}
