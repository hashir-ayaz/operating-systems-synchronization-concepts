#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::timed_mutex mtx;

void thread_func(int id)
{
    if (mtx.try_lock_for(std::chrono::seconds(1)))
    {
        std::cout << "Thread " << id << " acquired the lock" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
        mtx.unlock();
    }
    else
    {
        std::cout << "Thread " << id << " timed out" << std::endl;
    }
}

int main()
{
    std::thread t1(thread_func, 1);
    std::thread t2(thread_func, 2);

    t1.join();
    t2.join();

    return 0;
}
