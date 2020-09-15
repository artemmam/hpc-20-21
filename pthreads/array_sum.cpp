#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <chrono>

int n;
int size;
std::vector<int> vec_A;
std::vector<int> vec_B;
std::vector<int> vec_C;
void* sum_vector(void* p) {
    int th_num = *(int*)p;
    printf("Thread number = %d \n", th_num);
    for(int i = th_num; i < size; i += n){
        vec_C[i] = vec_A[i] + vec_B[i];
    }
    return (void*) nullptr;
}

void set_vector(std::vector<int> &A)
{
    for(int i = 0; i < size; i ++) {
        A[i] = 0 + rand() % 5;
    }
}
void show_vector(std::vector<int> &A)
{
    for(int i = 0; i < size; i ++) {
        printf("%d   ", A[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    n = atoi (argv[1]);
    size = atoi (argv[2]);
    vec_A.resize(size);
    vec_B.resize(size);
    vec_C.resize(size);
    int arg[n];
    pthread_t th_arr[n];
    set_vector(vec_A);
    set_vector(vec_B);
    for(int i = 0; i < size; i ++) {
        vec_C[i] = 0;
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int i = 0; i < n; i ++) {
        arg[i] = i;
        pthread_create(&th_arr[i], nullptr, sum_vector, (void*)&arg[i]);
    }

    for(int i = 0; i < n; i ++) {
        pthread_join(th_arr[i], nullptr);
    }
//    show_vector(vec_A);
//    show_vector(vec_B);
//    show_vector(vec_C);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-begin;
    std::cout << "Time difference = " << elapsed_seconds.count() << "s\n" << std::endl;
}
