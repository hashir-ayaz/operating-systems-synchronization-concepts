#include <stdio.h>
#include <signal.h>
#include <unistd.h>
using namespace std;
void handle_sigterm(int sig) {
    cout<<"Caught SIGTERM. Cleaning up before exiting...\n";
    _exit(0);
}

int main() {
    signal(SIGTERM, handle_sigterm); // Register handler
    while (1) {
        cout<<"Running...\n";
        sleep(1);
    }
    return 0;
}

// run `ps` in terminal to get the process id of the running program
// run `kill -SIGTERM <pid>` to send SIGTERM signal to the process