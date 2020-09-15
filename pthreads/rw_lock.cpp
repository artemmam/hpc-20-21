#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <unistd.h>

std::vector <int> vec;
int n = 8;
int m = 4;
pthread_rwlock_t rw=PTHREAD_RWLOCK_INITIALIZER;


void add_element(int a)
{
    vec.push_back(a);
    sleep(2);
    std::cout << "Adding element to vec ...\n";
    //std::cout.flush();
}
void calculate_mean()
{
    sleep(2);
    std::cout << "Some calculation ...\n";

    //std::cout.flush();
}
void *read(void *args)
{
    pthread_rwlock_rdlock(&rw);
    calculate_mean();
    pthread_rwlock_unlock(&rw);
    return (void*) nullptr;
}
void *write(void* num)
{

    pthread_rwlock_wrlock(&rw);
    add_element(*(int*)num);
    pthread_rwlock_unlock(&rw);
    return (void*) nullptr;
}
int main() {
    int arg[n];
    //void* a;
    pthread_rwlock_init(&rw, NULL);
    pthread_t th_arr_readers[n];
    pthread_t th_arr_writers[m];
    for(int i = 0; i < m; i ++) {
        arg[i] = i;
        pthread_create(&th_arr_writers[i], nullptr, write, (void*)&arg[i]);
    }
    for(int i = 0; i < n; i ++) {
        //arg[i] = i;
        pthread_create(&th_arr_readers[i], nullptr, read, nullptr);
    }

    for(int i = 0; i < n; i ++) {
        pthread_join(th_arr_readers[i], nullptr);
    }
    for(int i = 0; i < m; i ++) {
        pthread_join(th_arr_writers[i], nullptr);
    }
    //printf("Sum of 'a' symbols=  %d\n", number_of_sym);
}

