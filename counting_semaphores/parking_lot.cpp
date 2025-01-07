#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>
#include <chrono>
#include <vector>

using namespace std;

sem_t parkingSpots;
void parkCar(int carId)
{
    sem_wait(&parkingSpots);
    std::cout << "Car " << carId << " has parked.\n";
    // std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate parking
    sleep(3);
    std::cout << "Car " << carId << " is leaving.\n";
    sem_post(&parkingSpots); // Release the spot
}

int main()
{
    sem_init(&parkingSpots, 0, 3); // Initialize the semaphore with 3 spots
    // std::thread cars[8];
    vector<thread> cars;
    for (int i = 0; i < 8; ++i)
    {
        // cars[i] = std::thread(parkCar, i + 1);
        cars.emplace_back(parkCar, i + 1);
    }

    for (int i = 0; i < 8; ++i)
    {
        cars[i].join();
    }
    return 0;
}
