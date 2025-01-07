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
void modifyData(Data &d, std::string &fname, float PI)
{
    d.id += 1;
    d.name = "Updated " + d.name;
    std::cout << "ID: " << d.id << ", Name: " << d.name << std::endl;
    std::cout << "Name: " << fname << std::endl;
    std::cout << "PI: " << PI << std::endl;
}

int main()
{
    // Create a structure instance
    Data d1 = {2, "Bob"};
    // const char name[] = "Hashr";
    std::string name = "Hashr";

    float PI = 3.14;
    // Create a thread and pass the structure by reference
    std::thread t1(modifyData, std::ref(d1), std::ref(name), PI);
    // std::thread t1(modifyData, &d1);

    // Wait for the thread to finish
    t1.join();

    // Print updated structure
    std::cout << "Updated ID: " << d1.id << ", Updated Name: " << d1.name << std::endl;

    return 0;
}
