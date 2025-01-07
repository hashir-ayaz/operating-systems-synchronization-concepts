#include <iostream>
#include <thread>
#include <semaphore.h>
#include <queue>

std::queue<int> buffer;
sem_t empty, full;

void producer()
{
    for (int i = 1; i <= 5; ++i)
    {
        sem_wait(&empty); // Wait for empty slot
        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;
        sem_post(&full); // Signal consumer
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void consumer()
{
    for (int i = 1; i <= 5; ++i)
    {
        sem_wait(&full); // Wait for a filled slot
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << item << std::endl;
        sem_post(&empty); // Signal producer
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    sem_init(&empty, 0, 1); // Semaphore for empty slots
    sem_init(&full, 0, 0);  // Semaphore for full slots

    std::thread prod(producer);
    std::thread cons(consumer);

    prod.join();
    cons.join();

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
