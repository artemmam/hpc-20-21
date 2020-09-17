#include <thread>
#include <iostream>
#include <vector>
void bt()
{
    printf("Hello\n");
}
int main()
{
    std::vector<std::thread> v;
    for(int i = 0; i < 8; i ++)
    {
        std::thread th(bt);
        v.push_back(std::move(th));
    }
    for(auto& t : v)
        t.join();
}
