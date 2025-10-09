#ifndef __THREAD_H__ 
#define __THREAD_H__

#include <pthread.h>

class Thread
{
public:
    Thread();
    void start();
    void join();

private:
    static void * start_routine(void *arg);
    virtual void run() = 0;

private:
   pthread_t _pthid;
   bool      _isRunning;
    
};

#endif

