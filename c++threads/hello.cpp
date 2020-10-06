#include <iostream>
#include <thread>

using namespace std;


void hello()
{
    std::cout<<"Hello from function\n";
}



int main()
{
    int c = thread::hardware_concurrency();
    cout << "Number of threads: " << c <<"\n";
    thread t(hello);
    t.join();
    thread th_lambda([]()
                  {
                      std::cout << "Hello from lambda function\n";
                  }
    );
    th_lambda.join();
    return 0;
}

