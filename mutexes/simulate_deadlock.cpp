#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx1, mtx2;

void thread1_func()
{
    mtx1.lock();
    std::cout << "Thread 1 locked mtx1" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    mtx2.lock();
    std::cout << "Thread 1 locked mtx2" << std::endl;
    mtx2.unlock();
    mtx1.unlock();
}

void thread2_func()
{
    mtx2.lock();
    std::cout << "Thread 2 locked mtx2" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    mtx1.lock();
    std::cout << "Thread 2 locked mtx1" << std::endl;
    mtx1.unlock();
    mtx2.unlock();
}

int main()
{
    std::thread t1(thread1_func);
    std::thread t2(thread2_func);

    t1.join();
    t2.join();

    return 0;
}
