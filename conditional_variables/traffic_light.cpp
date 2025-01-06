// Problem Description
// A traffic light controller thread changes the light every 5 seconds in the following sequence:
// Red → Green → Yellow → Red (and repeats).
// Multiple vehicle threads continuously approach the traffic light.
// If the light is red or yellow, vehicles wait.
// If the light is green, vehicles pass through and display a message.
// Requirements
// Use a shared variable to store the current state of the traffic light.
// Use a conditional variable to signal vehicle threads when the light turns green.
// Synchronize access to the shared variable using a mutex.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

int traffic_light = 1; // 1: Red, 2: Yellow, 3: Green
condition_variable cv;
mutex mtx;

// Traffic light controller
void trafficLightController()
{
    while (true)
    {
        {
            unique_lock<mutex> lock(mtx);
            if (traffic_light == 1)
            {
                cout << "Traffic Light: Red" << endl;
                traffic_light = 3; // Turn green
            }
            else if (traffic_light == 3)
            {
                cout << "Traffic Light: Green" << endl;
                traffic_light = 2; // Turn yellow
            }
            else if (traffic_light == 2)
            {
                cout << "Traffic Light: Yellow" << endl;
                traffic_light = 1; // Turn red
            }
            cv.notify_one(); // Notify waiting cars
        }
        this_thread::sleep_for(chrono::seconds(5)); // Wait 5 seconds for each state
    }
}

// Car thread function
void car(int id)
{
    while (true)
    {
        unique_lock<mutex> lock(mtx);
        while (traffic_light != 3)
        { // Wait for green light
            cout << "Car " << id << " is waiting..." << endl;
            cv.wait(lock);
        }
        // Traffic light is green; car can proceed
        cout << "Car " << id << " has crossed the traffic light." << endl;
        break; // Exit after crossing
    }
}

int main()
{
    // Create traffic light controller thread
    thread lightController(trafficLightController);

    // Create car threads
    vector<thread> cars;
    for (int i = 1; i <= 5; ++i)
    {
        cars.emplace_back(car, i);
    }

    // Wait for all cars to finish
    for (auto &car : cars)
    {
        car.join();
    }

    // Terminate the traffic light controller (manually, for simplicity)
    lightController.detach();

    return 0;
}
