#include <iostream>
#include <pthread.h>
#include <string>
#include <queue>
#include <unistd.h>
int data_ready = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;

std::queue<int> q;
void* consumer( void* num){
    int data;
    printf("Consumer № %d\n", *(int*)num);

    while (1) {
        //sleep(1);

        pthread_mutex_lock(&mutex);
        while (q.empty()) {
            printf("Consumer № %d waiting...\n", *(int*)num);
            pthread_cond_wait(&condvar, &mutex);
        }
        data = q.front();
        q.pop();
        printf("Consumer № %d get data %d \n", *(int*)num, data);
        pthread_mutex_unlock(&mutex);
    }

}

void* producer (void* num) {
int new_data;
    printf("Producer № %d \n", *(int*)num);

    while (1) {
        sleep(2);
        new_data = 0 + rand() % 5;
        printf("Producer № %d GEN data %d \n", *(int*)num, new_data);
        pthread_mutex_lock(&mutex);
        q.push(new_data);
        pthread_cond_signal(&condvar);
        pthread_mutex_unlock(&mutex);
    }

}

int main() {
    int n =2;
    int m =4;
    pthread_t th_prod[m];
    pthread_t th_cons[n];
    int num_prod[m];
    int num_cons[n];
    for(int i = 0; i < m; i ++) {
        num_prod[i] = i;
        pthread_create(&th_prod[i], nullptr, producer, (void*)&num_prod[i]);
    }
    for(int i = 0; i < n; i ++) {
        num_cons[i] = i;
        pthread_create(&th_cons[i], nullptr, consumer, (void*)&num_cons[i]);
    }
    for(int i = 0; i < n; i ++) {
        pthread_join(th_cons[i], nullptr);
    }
    for(int i = 0; i < m; i ++) {
        pthread_join(th_prod[i], nullptr);
    }
}