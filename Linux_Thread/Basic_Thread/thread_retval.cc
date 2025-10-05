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
    int * stack_arg = (int *) arg;
    cout << "arg = " << *stack_arg + 1 << endl;

    return &(++*stack_arg);
}

int test() {
    //创建和使用线程
    pthread_t pthid;
    //向线程传入一个栈变量
    int stack_arg = 10;
    int ret = pthread_create(&pthid,
                             NULL,
                             thread_func,
                             &stack_arg);
    if(ret != 0){
        fprintf(stderr, "%s\n", strerror(ret));
        return EXIT_FAILURE;
    }
    
    cout << "sub thread created" << endl;
    cout << "main thread shouldn't shut before sub thread" << endl;

    void * arg = 0;
    pthread_join(pthid, &arg); 
    cout << "sub thread retval : " << *(int *)arg << endl;

    return 0;
}

int main() {
    test();
    return 0;
}

