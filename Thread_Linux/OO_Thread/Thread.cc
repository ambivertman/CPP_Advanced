#include "Thread.hpp"
#include <string.h>
#include <stdio.h>

Thread::Thread()
    :_pthid(0)
    ,_isRunning(false)
    {}

void Thread::start(){
    if(!_isRunning){
        int ret = pthread_create(&_pthid, NULL,
                       start_routine, this);
        if(0 == ret){
            fprintf(stderr, "%s", strerror(ret));                
        }
        _isRunning = true;
    }
}
    
void Thread::join(){
    if(_isRunning){
        pthread_join(_pthid, NULL);
        _isRunning = false;
    }
}

void * Thread::start_routine(void * arg){
    Thread * pthread = static_cast<Thread*>(arg);
    if(pthread){
        pthread->run();
    }
    return NULL;
}

