#include "Thread.hpp"
#include <iostream>
#include <memory>

using std::cin;
using std::cout;
using std::endl;
using std::unique_ptr;

class MyThread : public Thread{
    void run() override{
        cout << "sub thread: " << pthread_self() << " is running" << endl; 
    }
};

void test() {
    cout << "main thread is running" << endl;
    unique_ptr<MyThread> th1(new MyThread());
    unique_ptr<MyThread> th2(new MyThread());
    th1->start();
    th2->start();
    th1->join();
    th2->join();
    cout << "all threads finished" << endl;
}

int main() {
    test();
    return 0;
}

