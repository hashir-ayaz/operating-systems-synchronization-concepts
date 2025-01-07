#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
using namespace std;
void handle_sigalrm(int sig) {
    cout<<"ALARM WOOOH\n";
}

int main() {
    signal(SIGALRM, handle_sigalrm);
    // set alarm 
    alarm(5); 
    // pause until alarm goes off
    pause(); 
    return 0;
}
