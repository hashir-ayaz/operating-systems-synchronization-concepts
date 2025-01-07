#include <iostream>
#include <unistd.h>
#include <cstring>

int main()
{
    int parentToChild[2], childToParent[2];

    if (pipe(parentToChild) == -1 || pipe(childToParent) == -1)
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
    {                            // Child process
        close(parentToChild[1]); // Close unused write end
        close(childToParent[0]); // Close unused read end

        char buffer[100];
        read(parentToChild[0], buffer, sizeof(buffer)); // Read message from parent
        std::cout << "Child received: " << buffer << std::endl;

        const char *response = "Hello back from child!";
        write(childToParent[1], response, strlen(response) + 1); // Send response to parent

        close(parentToChild[0]);
        close(childToParent[1]);
    }
    else
    {                            // Parent process
        close(parentToChild[0]); // Close unused read end
        close(childToParent[1]); // Close unused write end

        const char *message = "Hello from parent!";
        write(parentToChild[1], message, strlen(message) + 1); // Send message to child

        char buffer[100];
        read(childToParent[0], buffer, sizeof(buffer)); // Read response from child
        std::cout << "Parent received: " << buffer << std::endl;

        close(parentToChild[1]);
        close(childToParent[0]);
    }

    return 0;
}
