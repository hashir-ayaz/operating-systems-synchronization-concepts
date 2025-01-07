/*
Create a program where you pass the same structure to multiple threads. The structure contains fields for id, result, and a mutex.
Each thread:

- Updates the result field based on its thread ID.
- Uses the mutex to ensure that updates do not conflict. After all threads complete, print the final values of the structure.
*/

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

struct my_struct
{
    int id;
    int result;
};

void updateStruct(my_struct &s, int id)
{
    unique_lock<mutex> lock(mtx);
    {
        s.id = id;
        s.result = id;
    }
}

int main()
{
    my_struct s1;
    my_struct s2;
    my_struct s3;

    thread t1(updateStruct, ref(s1), 1);
    thread t2(updateStruct, ref(s2), 2);
    thread t3(updateStruct, ref(s3), 3);

    t1.join();
    t2.join();
    t3.join();

    // print all 3 structs
    cout << "details of struct 1 are: " << s1.id << endl;
    cout << "details of struct 2 are: " << s2.id << endl;
    cout << "details of struct 3 are: " << s3.id << endl;

    return 0;
}