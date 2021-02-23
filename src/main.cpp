#include "memory_guard.cpp"
#include <iostream>

int main(int argc, char* const argv[]) {
    auto [data, guard] = gc::new_object<int>();
    guard.try_freeing();
    return 0;
}
