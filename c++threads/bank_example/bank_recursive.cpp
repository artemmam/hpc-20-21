#include <chrono>
#include <cstdio>
#include <mutex>
#include <thread>

class Account {
public:
    Account(int balance)
            : balance(balance)
            , m() {
    }

    int getBalance() const {
        std::lock_guard<std::recursive_mutex> lock(m);
        return balance;
    }

    void deposit(int amount) {
        std::lock_guard<std::recursive_mutex> lock(m);
        balance += amount;
    }

    bool withdraw(int amount) {
        std::lock_guard<std::recursive_mutex> lock(m);
        if (balance >= amount) {
            balance -= amount;
            return true;
        } else {
            return false;
        }
    }

    std::recursive_mutex& getMutex() {
        return m;
    }

private:
    int balance;
    mutable std::recursive_mutex m;
};

void client(int client_id, Account& a, int amount) {
    std::lock_guard<std::recursive_mutex> lock(a.getMutex());
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
    Account a(100);

    std::thread t1(client, 1, std::ref(a), 90);
    std::thread t2(client, 2, std::ref(a), 90);

    t1.join();
    t2.join();

    std::printf("balance %d\n", a.getBalance());
}

