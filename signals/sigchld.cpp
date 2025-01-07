#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <thread>
using namespace std;
void handle_sigchld(int sig)
{
    int status;
    pid_t pid = wait(&status);
    if (pid > 0)
    {
        cout << "Child process " << pid << " exited with status " << status << endl;
    }
}

int main()
{
    signal(SIGCHLD, handle_sigchld);
    pid_t pid = fork();
    if (pid == 0)
    {
        // child
        cout << "Child process" << pid << "running...\n";
        sleep(2);
        cout << "Child process exiting...\n";
        exit(0);
    }
    else if (pid > 0)
    {
        // parent
        cout << "Parent waiting for child...\n";
        while (1)
        {
            sleep(1);
        }
    }
    return 0;
}
