#include <iostream>
#include <pthread.h>
#include <string>

const int n = 8;
//int sum = 1;
void* hello_func(void* p) {
    printf("You passed '%d' to thread function!\n", *(int*) p);
    //sum = sum * *(int*) p + 1;
    return (void*) nullptr;
}

int main() {
    int arg[n];
    //void* a;
    pthread_t th_arr[n];
    for(int i = 0; i < n; i ++) {
        arg[i] = i;
        pthread_create(&th_arr[i], nullptr, hello_func, (void*)&arg[i]);
    }

    for(int i = 0; i < n; i ++) {
        pthread_join(th_arr[i], nullptr);
    }
    //printf("Sum var =  %d\n", sum);
}



