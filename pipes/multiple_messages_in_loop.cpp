#include <iostream>
#include <unistd.h>
#include <cstring>

int main()
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("Pipe creation failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0)
    {                     // Child process
        close(pipefd[1]); // Close unused write end

        char buffer[100];
        while (true)
        {
            ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));
            if (bytesRead <= 0)
                break; // End of data
            buffer[bytesRead] = '\0';
            std::cout << "Child received: " << buffer << std::endl;
        }

        close(pipefd[0]);
    }
    else
    {                     // Parent process
        close(pipefd[0]); // Close unused read end

        const char *messages[] = {"Message 1", "Message 2", "Message 3"};
        for (const char *message : messages)
        {
            write(pipefd[1], message, strlen(message) + 1);
            sleep(1); // Simulate delay
        }

        close(pipefd[1]); // Close write end
    }

    return 0;
}
