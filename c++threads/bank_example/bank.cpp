#include <chrono>
#include <cstdio>
#include <mutex>
#include <thread>
#include <iostream>

class Account {
public:
    Account(int balance)
            : balance(balance)
            , m() {
    }

    int getBalance() const {
        //std::lock_guard<std::mutex> lock(m);
        return balance;
    }

    void deposit(int amount) {
        //std::lock_guard<std::mutex> lock(m);
        balance += amount;
    }

    bool withdraw(int amount) {
        //std::unique_lock<std::mutex> ul(m);
        //std::lock_guard<std::mutex> lg(m);
        m.lock();
        if (balance >= amount) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            balance -= amount;
            m.unlock();
            //ul.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            return true;
        } else {
            m.unlock();
            //ul.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            return false;
        }

    }

private:
    int balance;
    mutable std::mutex m;
};

void client(int client_id, Account& a, int amount) {
    std::printf("%d: balance %d\n", client_id, a.getBalance());
    bool result = a.withdraw(amount);
    if (result) {
        std::printf("%d: withdraw %d OK\n", client_id, amount);
    } else {
        std::printf("%d: withdraw %d ERROR\n", client_id, amount);
    }
    std::printf("%d: balance %d\n", client_id, a.getBalance());
}

int main(int argc, char* argv[]) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Account a(100);
    std::thread t1(client, 1, std::ref(a), 90);
    std::thread t2(client, 2, std::ref(a), 90);
    t1.join();
    t2.join();
    std::printf("balance %d\n", a.getBalance());
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-begin;
    std::printf("elapsed time = %f", elapsed_seconds);
}
