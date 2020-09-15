#include <iostream>
#include <pthread.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;;
int n = 8;
int iter = 100;
void* print_block (void* p) {
    // critical section
    int id = *(int*)p;
    pthread_mutex_lock (&mut);
    for (int i=0; i<iter; ++i){
        std::cout << id;
    }
    std::cout << '\n';
    pthread_mutex_unlock (&mut);
}

int main ()
{
    int arg[n];
    pthread_t th_arr[n];
    //pthread_mutex_init(&mut, NULL);
    for(int i = 0; i < n; i ++) {
        arg[i] = i;
        pthread_create(&th_arr[i], nullptr, print_block, (void*)&arg[i]);
    }

    for(int i = 0; i < n; i ++) {
        pthread_join(th_arr[i], nullptr);
    }
}