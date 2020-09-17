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
        // comment the line below and compile with -O2
        //std::lock_guard<std::mutex> lock(m);
        return balance;
    }

    void deposit(int amount) {
        std::lock_guard<std::mutex> lock(m);
        balance += amount;
    }

    bool withdraw(int amount) {
        std::lock_guard<std::mutex> lock(m);
        if (balance >= amount) {
            balance -= amount;
            return true;
        } else {
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

void client2(int client_id, Account& a, int amount) {
    while (a.getBalance() == amount)
        ;
}

int main(int argc, char* argv[]) {
    Account a(100);

    std::thread t1(client, 1, std::ref(a), 90);
    std::thread t2(client2, 2, std::ref(a), 100);

    t1.join();
    t2.join();

    std::printf("balance %d\n", a.getBalance());
}


