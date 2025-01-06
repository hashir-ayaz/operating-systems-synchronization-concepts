#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1, mtx2;

void thread1_func()
{
    std::lock(mtx1, mtx2); // Lock both mutexes
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);

    std::cout << "Thread 1 acquired both locks." << std::endl;
}

void thread2_func()
{
    std::lock(mtx1, mtx2); // Lock both mutexes
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);

    std::cout << "Thread 2 acquired both locks." << std::endl;
}

int main()
{
    std::thread t1(thread1_func);
    std::thread t2(thread2_func);

    t1.join();
    t2.join();

    return 0;
}
