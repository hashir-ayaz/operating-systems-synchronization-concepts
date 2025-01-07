Here are some practice questions to help you prepare for your lab exam, focusing on **threads with structures** in C++:

---

### **1. Basic Thread with a Structure**

Write a program where a structure contains three integers. Pass the structure to a thread routine that calculates the sum of the integers and updates the structure with the result. Print the result in the main thread after the thread has finished execution.

---

### **2. Multiple Threads Operating on a Shared Structure**

Create a program where multiple threads operate on a shared structure that contains an array of integers. Each thread calculates the sum of a portion of the array and updates a shared total sum field in the structure. Use a mutex to ensure synchronization.

---

### **3. Passing a Structure to Multiple Threads**

Create a program where you pass the same structure to multiple threads. The structure contains fields for `id`, `result`, and a mutex. Each thread:

1. Updates the `result` field based on its thread ID.
2. Uses the mutex to ensure that updates do not conflict.
   After all threads complete, print the final values of the structure.

---

### **4. Thread with Dynamic Memory in a Structure**

Write a program where a structure contains a pointer to dynamically allocated memory (e.g., a string or array). Pass the structure to a thread, modify the dynamic memory in the thread, and print the modified result in the main thread.

---

### **5. Thread Communication via Structure**

Write a program where a structure is used for communication between threads. The structure should have:

1. A field for a message string.
2. A mutex and condition variable.
   The main thread sends a message to a worker thread via the structure, and the worker thread processes the message and responds back.

---

### **6. Simulating a Bank Account**

Create a program to simulate a bank account using a structure that contains:

1. Account balance.
2. Mutex for synchronization.
   Create two threads:

- One thread deposits money into the account.
- The other thread withdraws money.
  Print the final balance after all operations.

---

### **7. Producer-Consumer Problem**

Implement the producer-consumer problem using a structure that contains:

1. A fixed-size buffer (array).
2. Fields for buffer state (e.g., `count`, `head`, and `tail`).
3. Mutex and condition variables.
   Create one producer thread and one consumer thread that interact with the shared structure.

---

### **8. Thread Pool Simulation**

Write a program that simulates a thread pool. Use a structure to:

1. Store a task queue (e.g., a list of numbers to process).
2. Keep track of completed results.
   Create multiple threads that process tasks from the queue and store results back into the structure.

---

### **9. Structure with Nested Structures**

Create a program where a structure contains nested structures. For example, a structure for a family with fields for parents and children (each a nested structure). Pass the family structure to a thread, which calculates and updates the total age of the family. Print the updated structure in the main thread.

---

### **10. Thread-safe Logger**

Create a thread-safe logging system where:

1. A structure contains a log file name and a mutex.
2. Multiple threads write log messages to the file using the structure.
3. Ensure thread-safe access to the log file using the mutex.

---

### **11. Matrix Operations**

Write a program to perform matrix addition using threads. Each thread processes one row of the matrices, and the structure passed to each thread contains:

1. The two matrices.
2. The result matrix.
3. The row index to process.

---

### **12. Threads with Error Codes**

Write a program where a structure contains:

1. An array of error codes (e.g., `0` for success, `1` for failure).
2. A mutex for synchronization.
   Create multiple threads, each performing a task and updating its error code in the structure. Print all error codes after the threads finish.

---

### **General Steps to Practice**

1. **Define the Structure**: Include fields relevant to the task.
2. **Create Threads**: Use `std::thread` to create and pass the structure to thread routines.
3. **Use Synchronization Primitives**:
   - Use `std::mutex` to protect shared resources.
   - Use `std::condition_variable` for thread communication, if necessary.
4. **Join Threads**: Ensure all threads complete execution before accessing the final results.
5. **Print Results**: Validate the output for correctness.

---

### **Example Template for Passing a Structure**

```cpp
#include <iostream>
#include <thread>
#include <mutex>

struct Data {
    int value1;
    int value2;
    int result;
    std::mutex mtx;
};

void compute_sum(Data& data) {
    std::lock_guard<std::mutex> lock(data.mtx);
    data.result = data.value1 + data.value2;
    std::cout << "Sum calculated by thread: " << data.result << std::endl;
}

int main() {
    Data data = {10, 20, 0};

    // Create thread
    std::thread t(compute_sum, std::ref(data));

    // Wait for thread to finish
    t.join();

    // Print the result in main thread
    std::cout << "Final result in main: " << data.result << std::endl;

    return 0;
}
```

This template demonstrates:

- Passing a structure by reference to a thread.
- Using a mutex for synchronization.
- Accessing and updating the structure fields safely.

---

### **Practice Approach**

1. Start with basic examples (e.g., question 1).
2. Gradually move to advanced problems involving synchronization.
3. Focus on writing clean, synchronized code and ensure proper handling of shared resources.

Practicing these will prepare you for handling threads with structures in various scenarios.
