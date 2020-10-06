#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>
#include <deque>

int sum = 0;

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
    int m = 1000;
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

    std::deque<std::packaged_task<int(const std::vector <int>&, int, int)>> pt_vec;
    for (int i= 0; i < n; ++i){
        std::packaged_task<int(const std::vector <int>&, int, int)> SumTask(thread_sum);
        pt_vec.push_back(std::move(SumTask));
    }

    // get the futures
    std::vector< std::future<int>> sumResult;
    for ( unsigned int i= 0; i < n; ++i){
        sumResult.push_back(pt_vec[i].get_future());
    }

    for ( unsigned int i= 0; i < n; ++i){
        std::packaged_task<int(const std::vector <int>&, int, int)> myTask = std::move(pt_vec.front());
        pt_vec.pop_front();
        std::thread sumThread(std::move(myTask), std::ref(vec), i*mv, (i + 1)*mv - 1);
        sumThread.detach();
    }


    int a_sum = 0;
    for ( int i= 0; i < n; ++i){
        a_sum += sumResult[i].get();
    }

    std::cout<<sum<<"\n";
    std::cout<<a_sum;
}






