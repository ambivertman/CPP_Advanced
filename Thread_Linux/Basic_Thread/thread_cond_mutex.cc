#include <pthread.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

pthread_mutex_t m;
pthread_cond_t cond;

void * threadFunc1(void * arg){

}

void * threadFunc2(void * arg){

}

void test() {
    //参数2 attr 指定锁的属性, 默认为普通锁 
    pthread_mutex_init(&m, NULL);
    //参数2 attr 指定条件变量的属性,一般默认设置为NULL 
    pthread_cond_init(&cond, NULL);

    pthread_t pthid1, pthid2;
    pthread_create(&pthid1, NULL, threadFunc1, NULL);

}

int main() {
    test();
    return 0;
}

