#include <thread>
#include <vector>
#include <iostream>
#include <atomic>

std::atomic_flag lock = ATOMIC_FLAG_INIT;

//bool lock;
void f(int n) {
    for (int cnt = 0; cnt < 100; ++cnt) {
        while (lock.test_and_set(std::memory_order_acquire))  // acquire lock
            //while (lock)
            ; // spin
        std::cout << "Output from thread " << n << '\n';
        //lock = false;
        lock.clear(std::memory_order_release);               // release lock
    }
}

int main() {
    std::vector <std::thread> v;
    for (int n = 0; n < 8; ++n) {
        v.emplace_back(f, n);
    }
    for (auto &t : v) {
        t.join();
    }
}