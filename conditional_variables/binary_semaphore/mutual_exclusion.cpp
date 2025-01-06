#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore; // Binary semaphore

void printMessage(const std::string &message)
{
    for (int i = 0; i < 5; ++i)
    {
        sem_wait(&semaphore); // Wait (P operation)
        std::cout << message << std::endl;
        sem_post(&semaphore); // Signal (V operation)
        sleep(1);             // Simulate work
    }
}

int main()
{
    sem_init(&semaphore, 0, 1); // Initialize semaphore with value 1 (unlocked)

    std::thread t1(printMessage, "Thread 1: Hello");
    std::thread t2(printMessage, "Thread 2: World");

    t1.join();
    t2.join();

    sem_destroy(&semaphore); // Clean up semaphore
    return 0;
}
