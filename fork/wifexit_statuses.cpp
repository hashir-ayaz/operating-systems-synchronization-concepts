#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
        exit(42); // Exit with status code 42
    }
    else
    {
        // Parent process
        int status;
        wait(&status); // Wait for the child process to terminate

        if (WIFEXITED(status))
        {
            printf("Child terminated normally with exit code: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child was terminated by signal: %d\n", WTERMSIG(status));
        }
        else if (WIFSTOPPED(status))
        {
            printf("Child was stopped by signal: %d\n", WSTOPSIG(status));
        }
        else if (WIFCONTINUED(status))
        {
            printf("Child continued execution\n");
        }
    }

    return 0;
}
