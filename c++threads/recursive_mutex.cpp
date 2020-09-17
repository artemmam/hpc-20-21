#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rec_mut;
std::mutex mut;

void recursive_function(int a)
{
    rec_mut.lock();
    std::cout<<a<<" ";
    std::this_thread::sleep_for(std::chrono::milliseconds (600));
    if (a<=1)
    {
        std::cout<<"\n";
        rec_mut.unlock();
        return;
    }
    a--;
    recursive_function(a);
    rec_mut.unlock();
}


int main()
{
    std::thread t(recursive_function, 10);
    std::thread t1(recursive_function, 10);
    t.join();
    t1.join();
}

