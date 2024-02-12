// Compile with -lpthread flag
#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

void do_greeting();

int main() {
    cout << "From PID " << getpid()
        << " thread id " << std::this_thread::get_id() << endl;

    // start thread at a function
    std::thread one(do_greeting);
    //sleep(2);

    one.join();  // join() or detach() is required
    return 0;
}

void do_greeting() {
    std::this_thread::sleep_for(chrono::seconds(1));

    cout << "Thread version of Hello, world. PID=" << getpid() 
        << " TID=" << std::this_thread::get_id() << endl;
}