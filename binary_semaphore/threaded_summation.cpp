#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>

sem_t semaphore;
int totalSum = 0;

void partialSum(const std::vector<int> &arr, int start, int end)
{
    int sum = 0;
    for (int i = start; i < end; ++i)
    {
        sum += arr[i];
    }

    sem_wait(&semaphore); // Lock before updating shared sum
    totalSum += sum;
    sem_post(&semaphore); // Unlock
}

int main()
{
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = arr.size();
    int numThreads = 2;

    sem_init(&semaphore, 0, 1);

    std::thread t1(partialSum, std::ref(arr), 0, n / 2);
    std::thread t2(partialSum, std::ref(arr), n / 2, n);

    t1.join();
    t2.join();

    std::cout << "Total Sum: " << totalSum << std::endl;

    sem_destroy(&semaphore);
    return 0;
}
