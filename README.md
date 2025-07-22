# Threads, Mutexes, and Wrapper Functions in C

---

## 🧵 Threads: Lightweight Processes

A **thread** is a single sequence of instructions within a program. Multiple threads in a process share:

- **Memory space:** All threads have access to the same variables and data.
- **File descriptors:** Threads can read/write through the same open files.
- **Global variables:** Changes made by one thread are visible to others.


### How to Create a Thread

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);
```

| Parameter                     | Description                                         |
|-------------------------------|-----------------------------------------------------|
| `pthread_t *thread`           | Pointer to a variable that will hold the thread ID  |
| `pthread_attr_t *attr`        | Thread attributes (`NULL` for default)              |
| `void *(*start_routine)(void *)` | Function to run in the thread                    |
| `void *arg`                   | Argument to pass to the thread function             |

---

## 🔧 Waiting for Threads (`pthread_join`)

To wait for a thread to finish, use:

```c
int pthread_join(pthread_t thread, void **retval);
```

| Parameter            | Description                                              |
|----------------------|---------------------------------------------------------|
| `pthread_t thread`   | Thread ID to wait for                                   |
| `void **retval`      | Pointer to get thread's return value (`NULL` if unused) |

### ❗ Why Use `pthread_join`?

Ensures that a thread finishes before the program continues or exits, preventing issues like the main thread exiting too early.

---

## 🔒 Mutexes: Preventing Race Conditions

A **mutex** (mutual exclusion) is a lock that ensures only one thread accesses a shared resource at a time.

### Why Use Mutexes?

- Prevents **race conditions**—bugs that occur when threads try to access or modify shared data simultaneously.
- Ensures **data integrity** and predictable program behavior.

#### 🧠 Real-life analogy

Imagine a bathroom with a lock: only one person can use it at a time, and others must wait for it to be unlocked. That’s how a mutex works!


## 📦 What Is a Wrapper Function?

A **wrapper function** is a function that calls another function, often adding extra behavior before or after the call.

- Think of it as a "helper" or "cover" around an existing function.
- Useful for logging, error handling, or simplifying complex APIs.

---
