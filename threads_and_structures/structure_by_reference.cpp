#include <iostream>
#include <thread>
#include <string>

// Define a structure
struct Data
{
    int id;
    std::string name;
};

// Thread function
void modifyData(Data &d)
{
    d.id += 1;
    d.name = "Updated " + d.name;
}

int main()
{
    // Create a structure instance
    Data d1 = {2, "Bob"};

    // Create a thread and pass the structure by reference
    std::thread t1(modifyData, std::ref(d1));

    // Wait for the thread to finish
    t1.join();

    // Print updated structure
    std::cout << "Updated ID: " << d1.id << ", Updated Name: " << d1.name << std::endl;

    return 0;
}
