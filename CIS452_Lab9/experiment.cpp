#include <iostream>
#include <cstdlib>

int global_init = 10;
int global_uninit;

static int static_global_init = 123;
static int static_global_uninit;

void exploreStack() {
    int stack_var = 789;
    std::cout << std::hex << &stack_var << " Address of stack_var in exploreStack(): " << std::endl;
}

void allocateOnHeap() {
    int* heap_var = static_cast<int*>(std::malloc(sizeof(int)));
    std::cout << std::hex << heap_var << " Address of heap_var in allocateOnHeap(): " << std::endl;
    free(heap_var);
}

void recursiveFunction(int depth) {
    if (depth > 0) {
        int local_var = depth * 100;
        std::cout << std::hex << &local_var << " Address of local_var in recursiveFunction(): " << std::endl;
        recursiveFunction(depth - 1);
    }
}

int main() {
    int balls = 100;
    static int blah = 101;

    int* yahoo = new int(123);
    std::cout << std::hex << yahoo << " Address of yahoo in main()" << std::endl;

    exploreStack();

    recursiveFunction(3);

    allocateOnHeap();

    std::cout << std::hex << &global_init << " Address of global_init: " << std::endl;
    std::cout << std::hex << &global_uninit << " Address of global_uninit: " << std::endl;
    std::cout << std::hex << &static_global_init << " Address of static_global_init: " << std::endl;
    std::cout << std::hex << &static_global_uninit << " Address of static_global_uninit: " << std::endl;
    std::cout << std::hex << &balls << " Address of balls in main(): " << std::endl;
    std::cout << std::hex << &blah << " Address of blah in main(): " << std::endl;

    delete yahoo;

    return 0;
}
