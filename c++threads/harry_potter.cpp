#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

int main() {
    std::fstream newfile;
    std::ifstream fs("harry.txt");
    std::vector <std::string> lines;
    for (std::string line; std::getline(fs, line);) {
        lines.push_back(line);
    }

    std::cout << lines.size() << "\n";
    string needle = "harry";
    int count = 0;
    for (std::string str : lines) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        if (str.find(needle) != std::string::npos) {
            count++;
        }
    }
    std::cout << "Found " << count << " matches" << std::endl;
}

