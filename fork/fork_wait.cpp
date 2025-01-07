#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process running...\n");
        sleep(5);
        exit(42); // Exit with status code 42
    }
    else
    {
        // Parent process
        int status;
        wait(&status); // Wait for the child process to terminate
        cout << "child has ended" << endl;
        }

    return 0;
}