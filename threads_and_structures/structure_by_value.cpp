#include <iostream>
#include <thread>

// Define a structure
struct Data
{
    int id;
    std::string name;
};

// Thread function
void printData(Data d)
{
    std::cout << "ID: " << d.id << ", Name: " << d.name << std::endl;
}

int main()
{
    // Create a structure instance
    Data d1 = {1, "Alice"};

    // Create a thread and pass the structure by value
    std::thread t1(printData, d1);

    // Wait for the thread to finish
    t1.join();

    return 0;
}
