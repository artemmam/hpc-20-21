#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

long sum = 0;
long threads_sum = 0;
//std::atomic <long> threads_sum = {0};

void thread_sum(const std::vector<int> &vec, int start, int end) {
    for (int i = start; i <= end; i++) {
        threads_sum += vec[i];
    }
}


int main() {
    std::vector<int> vec;
    int m = 30000;
    int n = 8;
    int mv = m / n;
    for (int i = 0; i < m; i++) {
        vec.push_back(rand());
    }
    for (int i = 0; i < m; i++) {
        sum += vec[i];
    }

    std::vector <std::thread> v;

    for (int i = 0; i < n; i++) {
        std::thread th(thread_sum, std::ref(vec), i * mv, (i + 1) * mv - 1);
        v.push_back(std::move(th));
    }
    for (auto &t : v)
        t.join();
    std::cout << sum << "\n";
    std::cout << threads_sum;
}

