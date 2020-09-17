#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>



void ref_func(int &i)
{
    std::cout << "";
    std::cout << "thread function with std::ref message is = " << i<< std::endl;
    i+=10;
}

void func(int i)
{
    std::cout << "";
    std::cout << "thread function message is = " << i<< std::endl;
    i+=10;
}

int sum(int a, int b)
{
    return a+b;
}

int main()
{
    int i = 10;
    int result = 0;
    auto f = [&result]()
            {result = sum(1, 2);};
    std::cout << "Hello from lambda function\n";
    std::thread t1(func, i);
    sleep(1);
    std::cout << "main thread message after function = " << i << std::endl;
    t1.join();
    std::thread t(ref_func, std::ref(i));
    sleep(1);
    std::cout << "main thread message after ref function = " << i << std::endl;
    t.join();
    std::thread lam_th(f);
    sleep(1);
    std::cout << "main thread message after lambda return = " << result << std::endl;
    lam_th.join();
    return 0;
}

