/*
Problem Description
There is 1 ATM machine shared by multiple customers.
N customer threads will simulate customers trying to use the ATM.
When a customer accesses the ATM:
Print a message: "Customer X is using the ATM."
Simulate ATM usage by having the thread sleep for 3 seconds.
Print a message: "Customer X has finished using the ATM."
Use a binary semaphore to ensure that only one customer accesses the ATM at a time.
Requirements
Semaphore Initialization:
Initialize the semaphore to allow one thread (customer) at a time.
Critical Section:
Protect the ATM access using the semaphore.
Thread Synchronization:
Use sem_wait to lock access to the ATM.
Use sem_post to release the ATM for other customers.
Main Function:
Create 5 customer threads.
Ensure all threads complete before the program ends.
*/
#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>
#include <chrono> //
using namespace std;

sem_t semaphore;

void useATM(int id)
{
    sem_wait(&semaphore);

    cout << "customer: " << id << " is using the ATM\n";
    this_thread::sleep_for(chrono::seconds(3));
    cout << "customer: " << id << " is DONE using the ATM\n";

    sem_post(&semaphore);
}

int main()
{
    sem_init(&semaphore, 0, 1);
    vector<thread>
        customers;
    for (int i = 0; i < 5; i++)
    {
        // create new customers
        customers.emplace_back(useATM, i + 1);
    }

    for (int i = 0; i < 5; i++)
    {
        // create new customers
        customers[i].join();
    }
    sem_destroy(&semaphore);
    return 0;
}