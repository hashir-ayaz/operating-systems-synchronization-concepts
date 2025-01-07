#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

int main()
{
    int yummy_pipe[2]; // 0 is read | 1 is write
    char buffer[25];

    int make_pipe = pipe(yummy_pipe);
    if (make_pipe == -1)
    {
        cout << "error making pipe \n";
    }
    else
    {
        cout << "pipe made!!!\n";
    }

    int pid1 = fork();
    if (pid1 == 0)
    {
        // in child

        // close write end
        close(yummy_pipe[1]);

        // read from pipe
        int bytesRead = read(yummy_pipe[0], buffer, sizeof(buffer));

        if (bytesRead > 0) // if the number of bytes read is >0 then cout warna nothing to print
        {
            buffer[bytesRead] = '\0'; // need to terminate with with null value so cout knows till where to print
            cout << "received in child\n";
            cout << buffer << endl;
        }
        else
        {
            cout << "no more data to read\n";
        }
    }

    else
    {
        // in parent

        // close read end
        close(yummy_pipe[0]);

        // string message = "hello beta\n";
        const char *message = "Hello BETA from parent!";

        write(yummy_pipe[1], message, strlen(message) + 1);
        cout << "parent sent msg: " << message << endl;
        cout << "parent sent a message to the child \n";

        close(yummy_pipe[1]);
    }

    return 0;
}