#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <vector>
#include <deque>
#include <chrono>

using namespace std::chrono;

// Fetch some data from DB
int Sum_up( int beg, int end)
{
    // Do some stuff to fetch the data
    //std::cout<<std::this_thread::get_id<< std::endl;
    int sum = 0;
    for (int i= beg; i < end; ++i )
        sum += i;
    return sum;
}

int main()
{
    int p = 1000000;
    int hwConcurr = 8;

    //Packeged task version
    system_clock::time_point start = system_clock::now();

    // define the tasks
    std::deque<std::packaged_task<int(int,int)>> sumTask;
    for ( unsigned int i= 0; i < hwConcurr; ++i){
        std::packaged_task<int(int,int)> SumTask(Sum_up);
        sumTask.push_back(std::move(SumTask));
    }

    // get the futures
    std::vector< std::future<int>> sumResult;
    for ( unsigned int i= 0; i < hwConcurr; ++i){
        sumResult.push_back(sumTask[i].get_future());
    }

    int begin{1};
    int increment{p/hwConcurr};
    int end= begin + increment;
    // execute each task in a separate thread
    while ( not sumTask.empty() ){
        std::packaged_task<int(int, int)> myTask= std::move(sumTask.front());
        sumTask.pop_front();
        std::thread sumThread(std::move(myTask),begin,end);
        begin= end;
        end += increment;
        sumThread.detach();
    }

    // get the results
    int sum= 0;
    for ( unsigned int i= 0; i < hwConcurr; ++i){
        sum += sumResult[i].get();
    }
    auto endT = system_clock::now();

    auto diff = duration_cast < std::chrono::microseconds > (endT - start).count();
    std::cout << "Total Time Taken Packeged Task = " << diff << " MicroSeconds" << std::endl;
    std::cout << "sum of 0 .. "<< p << "= " << sum << std::endl;

    //Async version
    system_clock::time_point start1 = system_clock::now();
    begin =1;
    end= begin + increment;
    std::vector< std::future<int>> a_sumResult;
    for ( unsigned int i= 0; i < hwConcurr; ++i){
        a_sumResult.push_back(std::async(std::launch::async, Sum_up, begin, end));
        begin= end;
        end += increment;
    }
    int a_sum = 0;
    for ( unsigned int i= 0; i < hwConcurr; ++i){
        a_sum += a_sumResult[i].get();
    }

    auto endT1 = system_clock::now();
    auto diff1 = duration_cast < std::chrono::microseconds > (endT1 - start1).count();
    std::cout << "Total Time Taken Async = " << diff1 << " MicroSeconds" << std::endl;
    std::cout << "sum of 0 .. "<< p << "= " << a_sum << std::endl;

    start1 = system_clock::now();
    int alt_sum = Sum_up(1, p);
    alt_sum +=p;
    endT1 = system_clock::now();
    diff1 = duration_cast < std::chrono::microseconds > (endT1 - start1).count();
    std::cout << "Total Time Taken sequence = " << diff1 << " MicroSeconds" << std::endl;
    std::cout << "sum of 0 .. "<< p << "= " << alt_sum << std::endl;
    return 0;
}

