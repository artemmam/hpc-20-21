#include <iostream>
#include <pthread.h>
#include <chrono>

const double a = 0;
const double b = 1;

double S = 0;
double h;
int n ;
int num_threads;

double f(double x) {
    return 4. / (1. + x * x);
}


void* compute(void* p) {
    double s = 0;
    int myn = *(int*)p;
    //std::cout<<"Thread number " << myn << "\n";
    for(int i = myn; i < n; i += num_threads){
        double x = a + 0.5 * h + h * i;
        s += f(x) * h;
    }
    S += s;
    return NULL;
}

int main(int argc, char *argv[]) {
    num_threads = atoi (argv[1]);
    n = atoi (argv[2]);
    h = (b - a) / n;
    int num_th[num_threads];
    pthread_t th_arr[num_threads];
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int i = 0; i < num_threads; i ++) {
        num_th[i] = i;
        pthread_create(&th_arr[i], NULL, compute, (void*)&num_th[i]);
    }
    for(int i = 0; i < num_threads; i ++)
        pthread_join(th_arr[i], NULL);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-begin;
    std::cout << "Execution time = " << elapsed_seconds.count() << "s\n" << std::endl;
    std::cout << "Result: " << S << "\n";
}
