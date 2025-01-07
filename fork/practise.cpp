#include <iostream>
#include <unistd.h>
int main()
{
    int pid = fork();
    int pid2 = fork();
    if (pid == 0)
        std::cout << "wow in a child\n";
    if (pid2 == 0)
        std::cout << "in child 2\n";
    if (pid2 > 0)
        std::cout << "in parent of child2\n";
    if (pid > 0)
        std::cout << "in parent \n";
}