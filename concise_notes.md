### **Short Notes for Exam: Syntax Reference**

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

These concise notes cover the key syntax you need to remember for exams related to multithreading, synchronization, and process handling in C++.
