#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

int main()
{
    int yummy_pipe[2]; // 0 is read | 1 is write
    char buffer[20];

    int make_pipe = pipe(yummy_pipe);
    if (make_pipe == -1)
    {
        cout << "error making pipe \n";
        return;
    }
    else
    {
        cout << "pipe made!!!";
    }

    return 0;
}