#include <thread>
#include <iostream>
#include <vector>

void bt() {
    printf("Hello from\n");
}

int main() {
    std::vector <std::thread> v;
    std::vector<int> a;
    int length_vec = v.size();
    for (int i = 0; i < 8; i++) {
        std::thread th(bt);
        v.push_back(std::move(th));
    }
    for (int i = 0; i < 8; i++) {
        a.push_back(i);
    }
    for (int i = 0; i < 8; i++)
        v[i].join();
}
