#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <future>

int sum = 0;
std::mutex m;

int thread_sum(const std::vector <int>& vec, int start, int end)
{
    int threads_sum = 0;
    for(int i = start; i <= end; i ++) {
        threads_sum +=vec[i];
    }
    return threads_sum;
}


int main()
{
    std::vector <int> vec;
    int m = 64;
    int n = 8;
    int mv = m/n;
    for(int i = 0; i < m; i ++)
    {
        vec.push_back(0 + rand() % 10);
    }
    for(int i = 0; i < m; i ++)
    {
        sum+=vec[i];
    }

    std::vector<std::future<int>> a_sumResult;
    for(int i = 0; i < n; i ++)
    {
        a_sumResult.push_back(std::async(std::launch::async, thread_sum, std::ref(vec), i*mv, (i + 1)*mv - 1));
    }
    int a_sum = 0;
    for ( int i= 0; i < n; ++i){
        std::cout<<"Calculate results for "<<i<<"\n";
        a_sum += a_sumResult[i].get();
    }

    std::cout<<sum<<"\n";
    std::cout<<a_sum;
}
