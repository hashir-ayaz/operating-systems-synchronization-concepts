#include <iostream>
#include <thread>
#include <string>
#include <mutex>

struct Person
{
    int age;
    std::string name;
};

struct shared_data
{
    int counter;
};

void isOld(Person p)
{
    if (p.age > 30)
    {
        std::cout << "this dude is old!!!";
    }
    else
    {
        std::cout << "this dude young as hell";
    }
}

std::mutex my_mutex;

void incrementCounter(shared_data &data)
{
    // lock mutex first
    std::lock_guard<std::mutex> lock(my_mutex);

    // increment counter
    data.counter++;
    std::cout << "data has been incremented by 1 in thread with id:" << std::this_thread::get_id();
}

int main()
{
    shared_data s = {0};

    std::thread t1(incrementCounter, std::ref(s));
    std::thread t2(incrementCounter, std::ref(s));

    t1.join();
    t2.join();

    std::cout << "the final value of the counter is :" << s.counter;

    return 0;
}