#include <string.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>
using std::cin;
using std::cout;
using std::endl;

void * thread_func(void * arg){
    cout << "thread is running " << endl;
    //获取线程id
    cout << "sub thread ID : " << pthread_self() << endl;

    return NULL;
}

int test() {
    //创建和使用线程
    pthread_t pthid;
    int ret = pthread_create(&pthid,
                             NULL,
                             thread_func,
                             NULL);
    if(ret != 0){
        fprintf(stderr, "%s\n", strerror(ret));
        return EXIT_FAILURE;
    }
    cout << "sub thread created" << endl;
    cout << "main thread shouldn't shut before sub thread" << endl;
    cout << "main thread ID : " << pthread_self() << endl;
    cout << "thread ID : " << pthid << endl;
    
    pthread_join(pthid, NULL);
    return 0;
}

int main() {
    test();
    return 0;
}

