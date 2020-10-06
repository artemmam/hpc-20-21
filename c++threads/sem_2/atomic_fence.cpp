#include <iostream>
#include <atomic>
#include <thread>

std::atomic<bool> flag(false);
int a;

void func1()
{
    a = 100;
    atomic_thread_fence(std::memory_order_release);
    flag.store(true, std::memory_order_relaxed);
}

void func2()
{
    while(!flag.load(std::memory_order_relaxed))
        ;

    atomic_thread_fence(std::memory_order_acquire);
    std::cout << a << '\n'; // guaranteed to print 100
}

int main()
{
    std::thread t1 (func1);
    std::thread t2 (func2);

    t1.join(); t2.join();
}

