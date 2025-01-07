#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
using namespace std;
// the ctrl+c thing
void handle_sigint(int sig) {
    cout<<"GOTCHU SIGINT\n";
    _exit(0);
}

int main() {
    signal(SIGINT, handle_sigint); 
    while (1) {
        cout<<"waiting for ctrl+c\n";
        sleep(1);
    }
    return 0;
}
