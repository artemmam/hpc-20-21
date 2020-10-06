#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>

int value = 0;
std::mutex mutex;
std::shared_mutex sh_mutex;

// Reads the value and sets v to that value
void readValue(int& v) {
    //mutex.lock();
    sh_mutex.lock_shared();
    // Simulate some latency
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Read" << "\n";
    v = value;
   sh_mutex.unlock_shared();
    // mutex.unlock();
}

// Sets value to v
void setValue(int v) {
    //mutex.lock();
    sh_mutex.lock();
    // Simulate some latency
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Write" << "\n";
    value = v;
    sh_mutex.unlock();
    //mutex.unlock();
}

int main() {
    int read1;
    int read2;
    int read3;
    std::thread t1(readValue, std::ref(read1));
    std::thread t2(readValue, std::ref(read2));
    std::thread t3(readValue, std::ref(read3));
    std::thread t4(setValue, 1);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

