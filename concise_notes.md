### **Short Notes for Exam: Syntax Reference**

#### Necessary Libraries

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
```

#### **1. Binary Semaphore (`sem_t`)**

- **Initialization**:

  ```cpp
  sem_t semaphore;
  sem_init(&semaphore, 0, 1); // Binary semaphore (initial value 1)
  ```

  - `0`: Semaphore is shared between threads in the same process.
  - `1`: Initial value (1 for binary semaphore).

- **Wait (Decrement)**:

  ```cpp
  sem_wait(&semaphore);
  ```

- **Post (Increment)**:

  ```cpp
  sem_post(&semaphore);
  ```

- **Destroy**:
  ```cpp
  sem_destroy(&semaphore);
  ```

---

#### **2. Counting Semaphore (`sem_t`)**

- **Initialization**:

  ```cpp
  sem_t semaphore;
  sem_init(&semaphore, 0, 5); // Counting semaphore (initial value 5)
  ```

- **Wait (Decrement)**:

  ```cpp
  sem_wait(&semaphore);
  ```

- **Post (Increment)**:

  ```cpp
  sem_post(&semaphore);
  ```

- **Destroy**:
  ```cpp
  sem_destroy(&semaphore);
  ```

---

#### **3. Mutex (`std::mutex`)**

- **Declaration**:

  ```cpp
  std::mutex mtx;
  ```

- **Locking and Unlocking**:

  ```cpp
  mtx.lock();
  // Critical section
  mtx.unlock();
  ```

- **Using `std::lock_guard` for RAII**:
  ```cpp
  std::lock_guard<std::mutex> lock(mtx);
  // Critical section
  ```

---

#### **4. Thread (`std::thread`)**

- **Creating Threads**:

  ```cpp
  void threadFunction(int id) {
      std::cout << "Thread ID: " << id << std::endl;
  }

  std::thread t1(threadFunction, 1); // Passing arguments
  std::thread t2([]() { std::cout << "Lambda thread\n"; }); // Using lambda
  ```

- **Joining Threads**:

  ```cpp
  t1.join();
  t2.join();
  ```

- **Detaching Threads**:
  ```cpp
  t1.detach();
  ```

---

#### **5. Conditional Variable (`std::condition_variable`)**

- **Declaration**:

  ```cpp
  std::condition_variable cv;
  std::mutex mtx;
  bool ready = false;
  ```

- **Waiting**:

  ```cpp
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [] { return ready; }); // Predicate ensures spurious wakeups are handled
  ```

- **Notifying**:
  ```cpp
  cv.notify_one(); // Wake up one thread
  cv.notify_all(); // Wake up all threads
  ```

---

#### **6. Struct**

- **Definition**:

  ```cpp
  struct Data {
      int id;
      std::string name;
  };
  ```

- **Usage**:

  ```cpp
  Data d = {1, "Example"};
  std::cout << d.id << ", " << d.name << std::endl;
  ```

- **Passing to Threads**:

  ```cpp
  void processData(Data &data) {
      data.id++;
      data.name = "Updated";
  }

  Data d = {1, "Test"};
  std::thread t(processData, std::ref(d)); // Pass by reference
  t.join();
  ```

---

#### **7. Timers and Sleep**

- **Sleep for Seconds**:

  ```cpp
  sleep(1); // 1 second (POSIX)
  std::this_thread::sleep_for(std::chrono::seconds(1)); // C++11
  ```

- **Sleep for Milliseconds**:
  ```cpp
  std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 100 ms
  ```

---

#### **8. Process Handling**

- **Fork**:

  ```cpp
  pid_t pid = fork();
  if (pid == 0) {
      // Child process
  } else if (pid > 0) {
      // Parent process
  }
  ```

- **Wait for Child**:

  ```cpp
  int status;
  wait(&status);
  ```

- **Exit Status**:
  ```cpp
  if (WIFEXITED(status)) {
      std::cout << "Exit code: " << WEXITSTATUS(status) << std::endl;
  }
  ```

---

#### **9. Common Utilities**

- **Vector**:
  ```cpp
  std::vector<int> vec = {1, 2, 3};
  vec.push_back(4);
  for (int v : vec) {
      std::cout << v << std::endl;
  }
  ```

---

#### **1. Signal Setup**

- **Include Required Header**:

  ```cpp
  #include <signal.h>
  #include <unistd.h>
  #include <iostream>
  ```

- **Signal Handler Declaration**:

  ```cpp
  void signalHandler(int signum) {
      std::cout << "Signal received: " << signum << std::endl;
  }
  ```

- **Set Up Signal Handling**:
  ```cpp
  signal(SIGTERM, signalHandler); // Example for SIGTERM
  ```

---

#### **2. Sending/Triggering Signals**

- **From the Same Program**:

  ```cpp
  kill(getpid(), SIGTERM); // Send SIGTERM to the current process
  ```

- **From the Command Line**:
  ```bash
  kill -SIGTERM <pid>   # Send SIGTERM to process with <pid>
  kill -SIGINT <pid>    # Send SIGINT (e.g., Ctrl+C equivalent)
  kill -SIGKILL <pid>   # Send SIGKILL (force termination)
  kill -SIGUSR1 <pid>   # Send SIGUSR1 (user-defined)
  kill -SIGUSR2 <pid>   # Send SIGUSR2 (user-defined)
  kill -SIGALRM <pid>   # Send SIGALRM
  ```

---

#### **3. Common Signals**

| **Signal** | **Description**                                     | **Triggering Examples**                               |
| ---------- | --------------------------------------------------- | ----------------------------------------------------- |
| `SIGTERM`  | Termination signal (graceful shutdown).             | `kill -SIGTERM <pid>`                                 |
| `SIGINT`   | Interrupt signal (Ctrl+C).                          | Press `Ctrl+C` in the terminal running the process.   |
| `SIGKILL`  | Forcefully terminates a process (cannot be caught). | `kill -SIGKILL <pid>`                                 |
| `SIGCHLD`  | Sent to parent when a child process terminates.     | Triggered automatically by child process termination. |
| `SIGUSR1`  | User-defined signal 1.                              | `kill -SIGUSR1 <pid>`                                 |
| `SIGUSR2`  | User-defined signal 2.                              | `kill -SIGUSR2 <pid>`                                 |
| `SIGALRM`  | Alarm signal (used with `alarm()` for timers).      | `alarm(5); // Triggers SIGALRM after 5 seconds`       |

---

#### **4. Example Code**

```cpp
#include <signal.h>
#include <unistd.h>
#include <iostream>

// Signal handler
void signalHandler(int signum) {
    std::cout << "Signal received: " << signum << std::endl;
}

int main() {
    // Set up signal handlers
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);
    signal(SIGALRM, signalHandler);

    // Trigger SIGALRM after 5 seconds
    alarm(5);

    // Infinite loop to keep the program running
    while (true) {
        pause(); // Wait for signals
    }

    return 0;
}
```

---

#### **5. Key Functions**

- **Set Up a Signal Handler**:

  ```cpp
  signal(SIGINT, signalHandler);
  ```

- **Send a Signal**:

  ```cpp
  kill(getpid(), SIGUSR1); // Send SIGUSR1 to the current process
  ```

- **Timer for `SIGALRM`**:
  ```cpp
  alarm(5); // Triggers SIGALRM after 5 seconds
  ```

#### **6. Notes**

- `SIGKILL` and `SIGSTOP` cannot be caught, ignored, or handled.
- Use `pause()` or `sleep()` to keep the program waiting for signals.
- The `kill` command can target any process using its PID.

---

### **Concise Notes: Unnamed Pipes**

#### **1. Overview**

- **Unnamed Pipes**:

  - Allow one-way communication between processes (parent and child).
  - Exist only while the processes are running.
  - Data flows in FIFO (First In, First Out) order.

- **Include Required Headers**:
  ```cpp
  #include <unistd.h>
  #include <sys/types.h>
  #include <iostream>
  #include <cstring>
  ```

---

#### **2. Key Functions**

- **Creating a Pipe**:

  ```cpp
  int pipefd[2];
  pipe(pipefd); // Creates a pipe
  ```

  - `pipefd[0]`: Read end of the pipe.
  - `pipefd[1]`: Write end of the pipe.

- **Writing to a Pipe**:

  ```cpp
  write(pipefd[1], "Message", strlen("Message") + 1);
  ```

- **Reading from a Pipe**:

  ```cpp
  char buffer[100];
  read(pipefd[0], buffer, sizeof(buffer));
  ```

- **Closing a Pipe**:
  ```cpp
  close(pipefd[0]); // Close read end
  close(pipefd[1]); // Close write end
  ```

---

#### **3. Example: Parent Writing, Child Reading**

```cpp
#include <unistd.h>
#include <iostream>
#include <cstring>

int main() {
    int pipefd[2];
    char buffer[100];

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) { // Child process
        close(pipefd[1]); // Close unused write end
        read(pipefd[0], buffer, sizeof(buffer));
        std::cout << "Child received: " << buffer << std::endl;
        close(pipefd[0]); // Close read end
    } else { // Parent process
        close(pipefd[0]); // Close unused read end
        const char* message = "Hello from parent";
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]); // Close write end
        wait(NULL);       // Wait for child to finish
    }

    return 0;
}
```

---

#### **4. Notes**

- **Synchronization**:

  - Ensure proper closing of unused ends in both parent and child to prevent deadlocks.
  - Use `wait()` in the parent to synchronize.

- **Limitations**:
  - Unnamed pipes are for communication between related processes (e.g., parent-child).
  - Unidirectional communication only.

---

#### **5. Common Scenarios**

- **Parent Sending Data to Child**:

  - Parent writes to `pipefd[1]`, child reads from `pipefd[0]`.

- **Child Sending Data to Parent**:
  - Child writes to `pipefd[1]`, parent reads from `pipefd[0]`.

---
