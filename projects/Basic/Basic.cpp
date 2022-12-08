// Verify mongo-c-driver static link

#include <iostream>
#include <mongoc.h>

int main() {
    std::cout << "Before mongoc_init!\n";
	mongoc_init();
    std::cout << "After mongoc_init!\n";

    std::cout << "Before mongoc_cleanup!\n";
	mongoc_cleanup();
    std::cout << "After mongoc_cleanup!\n";
    return 0;
}