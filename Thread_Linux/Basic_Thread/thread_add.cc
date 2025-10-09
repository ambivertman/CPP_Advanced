#include <string.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>
using std::cin;
using std::cout;
using std::endl;

int g_number = 0;

void * thread_func1(void * arg){
    int cnt = 100000;
    while(--cnt){
        ++g_number;
    }
    cout << "g_number in sub thread1 : " << g_number << endl;

    return NULL;
}

void * thread_func2(void * arg){
    int cnt = 100000;
    while(--cnt){
        ++g_number;
    }
    cout << "g_number in sub thread1 : " << g_number << endl;

    return NULL;
}

int test() {
    //创建和使用线程
    pthread_t pthid1, pthid2;
    pthread_create(&pthid1, NULL, thread_func1, NULL);
    pthread_create(&pthid2, NULL, thread_func2, NULL);
    cout << "sub thread created" << endl;
    cout << "main thread shouldn't shut before sub thread" << endl;
   
    pthread_join(pthid1, NULL);
    pthread_join(pthid2, NULL);

    return 0;
}

int main() {
    test();
    return 0;
}

