#include <iostream>
#include <thread>

class background_task
{
public:
    void operator()()
    {
        std::cout << "Hello from class\n";
    }
};

void hello()
{
    std::cout<<"Hello from function\n";
}


int main()
{
    int c = std::thread::hardware_concurrency();
    std::cout << "Number of threads: " << c <<"\n";
    std::thread t(hello);
    t.join();
    background_task f;
    std::thread my_thread(f);  // the copy of class example in thread
    my_thread.join();
    std::thread th_lambda([]()
                  {
                      std::cout << "Hello from lambda function\n";
                  }
    );
    th_lambda.join();
}

