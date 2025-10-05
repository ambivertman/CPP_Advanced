#include <unistd.h>
#include <pthread.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

pthread_mutex_t m;
pthread_cond_t cond;

void * threadFunc(void * arg){
    cout << "sub thread is running " << endl;
    int wait_time = 3;
    while(wait_time--){
        cout << "main thread will wake in " << wait_time  <<  " sec" << endl;
        sleep(1);
    }

    pthread_cond_signal(&cond);
    
    return NULL;
}

void test() {
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cond, NULL);
 
    pthread_t pthid;
    pthread_create(&pthid, NULL, threadFunc, NULL);

    cout << "main thread gonna be paused" << endl;
    pthread_cond_wait(&cond, &m);
    
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&cond);
    cout << "main thread exit." << endl;
}

int main() {
    test();
    return 0;
}

