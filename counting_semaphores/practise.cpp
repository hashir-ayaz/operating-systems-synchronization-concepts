#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>
#include <chrono>
#include <vector>

sem_t my_sem;

int print_id(int id)
{
    std::cout << "Thread waiting id: " << id << std::endl;
    sem_wait(&my_sem);
    std::cout << "\nThread id: " << id << std::endl;
    sleep(3);
    sem_post(&my_sem);
    return 0;
}

int main()
{
    sem_init(&my_sem, 0, 3);

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++)
    {
        threads.emplace_back(print_id, i);
    }

    for (int i = 0; i < 10; i++)
    {
        threads[i].join();
    }

    return 0;
}