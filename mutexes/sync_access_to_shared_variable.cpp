#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // Mutex for synchronization
int counter = 0; // Shared counter

void increment(int id)
{
    for (int i = 0; i < 5; i++)
    {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        counter++;
        std::cout << "Thread " << id << " incremented counter to " << counter << std::endl;
    }
}

int main()
{
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();

    std::cout << "Final Counter Value: " << counter << std::endl;
    return 0;
}
