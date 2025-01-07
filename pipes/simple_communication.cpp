#include <iostream>
#include <unistd.h> // For pipe(), fork(), read(), write()
#include <cstring>  // For strlen()

int main()
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
    { // Create the pipe
        perror("Pipe failed");
        return 1;
    }

    pid_t pid = fork(); // Fork the process
    if (pid == -1)
    {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0)
    {                     // Child process
        close(pipefd[1]); // Close unused write end
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer)); // Read from the pipe
        std::cout << "Child received: " << buffer << std::endl;
        close(pipefd[0]); // Close the read end
    }
    else
    {                     // Parent process
        close(pipefd[0]); // Close unused read end
        const char *message = "Hello from parent!";
        write(pipefd[1], message, strlen(message) + 1); // Write to the pipe
        close(pipefd[1]);                               // Close the write end
    }

    return 0;
}
