#include <iostream>
#include <signal.h>
#include <unistd.h>

// Signal handlers
void sigusr1_handler(int signum)
{
    std::cout << "Received SIGUSR1\n";
}

void sigusr2_handler(int signum)
{
    std::cout << "Received SIGUSR2\n";
}

int main()
{
    // Register signal handlers
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);

    // Print process ID so we can send signals to it
    pid_t pid = getpid();
    std::cout << "Process ID: " << pid << std::endl;

    // Keep program running
    while (1)
    {
        std::cout << "Waiting for signals...\n";
        sleep(2);
    }

    return 0;
}

/*
# First compile and run the program
g++ program.cpp -o program
./program

# From another terminal, use the PID shown by the program
kill -SIGUSR1 <PID>
kill -SIGUSR2 <PID>

# Or using signal numbers
kill -10 <PID>  # SIGUSR1
kill -12 <PID>  # SIGUSR2


or
use the following in another cpp file
#include <iostream>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t target_pid;
    std::cout << "Enter target process ID: ";
    std::cin >> target_pid;

    // Send SIGUSR1
    kill(target_pid, SIGUSR1);
    sleep(1);

    // Send SIGUSR2
    kill(target_pid, SIGUSR2);

    return 0;
}
*/