#include <unistd.h>
#include <pthread.h>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

pthread_mutex_t m;
int wait_time = 10;
void * thread_func(void * arg){
    cout << "sub thread started " << endl;
    pthread_mutex_lock(&m);
    cout << "sub thread now hold the lock" << endl;
    cout << "working" << endl;
    sleep(2);

    pthread_mutex_unlock(&m);

#if 0

#endif

    return NULL;
}


void test() {
    //初始化互斥锁
    pthread_mutex_init(&m, NULL);

    //开启子线程
    pthread_t pthid;
    pthread_create(&pthid, NULL, thread_func, NULL);

    //锁定主线程
    pthread_mutex_lock(&m);
    cout << "main thread was locked" << endl;
    while(wait_time--){
        cout << "main thread will be unlocked in " << wait_time << " seconds." << endl; 
        sleep(1);
    }
    pthread_mutex_unlock(&m);
    cout << "main thread unlocked" << endl;
    
    //等待子线程执行完毕
    pthread_join(pthid, NULL);
}

int main() {
    test();
    return 0;
}

