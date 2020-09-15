#include <iostream>
#include <pthread.h>
#include <string>

void* hello_func(void* p) {
    //pthread_exit((void*) "I'm ur first exit thread!");
    printf("You passed '%s' to thread function!\n", (char*) p);
    return (void*) "I'm ur first thread!";
}

int main() {
    void* a;
    pthread_t th1;
    pthread_create(&th1, nullptr, hello_func, (void*)"Hello!");
    pthread_join(th1, &a);
    printf("Returned message: %s", (char*)a);
}

