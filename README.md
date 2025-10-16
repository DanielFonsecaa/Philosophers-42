# Philosophers-42
<div align="center">
<img width="150" height="150" alt="philosopherse" src="https://github.com/user-attachments/assets/3c7273e7-6156-4c0f-8948-6a39397b1294" />
</div>

A C implementation of the classic **Dining Philosophers Problem** using threads and mutexes, created for the 42 School curriculum.

---

<div align="center">
  
| Grade                                                             | Evaluation Information           |
| :---------------------------------------------------------------- | :------------------------------- |
| <img src="https://img.shields.io/badge/100%20%2F%20100%20%E2%98%85-sucess"/>  | `3 peers` `30 mins`  |
</div>

---

## 🗒️ Table of Contents

- [About](#about)
- [Problem Statement](#problem-statement)
- [Features](#features)
- [Project Structure](#project-structure)
- [How to Run](#how-to-run)
- [Usage](#usage)
- [Code Concepts](#code-concepts)

---

## About

**Philosophers-42** is a concurrency project designed to simulate the Dining Philosophers Problem. It demonstrates handling multiple threads, synchronization, and race condition prevention using C and POSIX threads (`pthread`). The project is part of the 42 School program.

---

## Problem Statement

The Dining Philosophers Problem describes five philosophers sitting around a table, alternating between thinking and eating. Each philosopher needs two forks to eat, but forks are shared with their neighbors. The main challenge is to prevent deadlocks and starvation by managing resource allocation and thread synchronization.

---

## Features

- **Threaded simulation**: Each philosopher is represented by a thread.
- **Fork mutexes**: Forks are protected by mutexes to prevent race conditions.
- **Monitor thread**: Supervises the simulation and detects when philosophers die or finish their meals.
- **Safe wrapper functions**: For thread and mutex operations, improving robustness.
- **Configurable parameters**: Number of philosophers, time to die, eat, sleep, and meal limits.

---

## Project Structure

```
Philosophers-42/
├── src/          # Source code (main logic, thread handling, simulation)
├── include/      # Header files (structs, prototypes, enums)
├── Makefile      # Build and run commands
└── README.md     # Documentation
```

Key files:
- `src/main.c`: Entry point, argument parsing, simulation start.
- `src/dinner.c`: Core thread simulation, fork handling, eating logic.
- `include/philo.h`: Structs (`t_philo`, `t_table`, `t_fork`), enums, prototypes.

---

## How to Run

### Prerequisites

- GCC or Clang
- POSIX compliant system (Linux, macOS)
- `make`

### Build

```bash
make
```

### Run

You can run the program with:

```bash
make run ARGS="5 800 200 200 3"
```

Manual run example:
```bash
./philo 5 800 200 200 3
```
**Arguments:**
1. Number of philosophers
2. Time to die (ms)
3. Time to eat (ms)
4. Time to sleep (ms)
5. [Optional] Number of times each philosopher must eat

---

## Usage

- The simulation will print philosopher actions: picking up forks, eating, sleeping, thinking, and dying.
- The monitor thread stops the simulation if a philosopher dies or all have eaten the required number of times.

---

## Code Concepts

- **Threads**: Each philosopher runs in a separate thread.
- **Mutexes**: Forks are protected by mutexes to avoid race conditions.
- **Monitor**: A dedicated thread monitors for death or completion.
- **Safe wrappers**: Functions like `safe_mutex_handle` and `safe_thread_handle` simplify thread/mutex management.

### Thread

A **thread** is a single sequence of instructions within a program. Multiple threads in a process share:

- **Memory space:** All threads have access to the same variables and data.
- **File descriptors:** Threads can read/write through the same open files.
- **Global variables:** Changes made by one thread are visible to others.


#### How to Create a Thread

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

#### 🔧 Waiting for Threads (`pthread_join`)

To wait for a thread to finish, use:

```c
int pthread_join(pthread_t thread, void **retval);
```

| Parameter            | Description                                              |
|----------------------|---------------------------------------------------------|
| `pthread_t thread`   | Thread ID to wait for                                   |
| `void **retval`      | Pointer to get thread's return value (`NULL` if unused) |

#### ❗ Why Use `pthread_join`?

Ensures that a thread finishes before the program continues or exits, preventing issues like the main thread exiting too early.

---

### 🔒 Mutexes

A **mutex** (mutual exclusion) is a lock that ensures only one thread accesses a shared resource at a time.

#### Why Use Mutexes?

- Prevents **race conditions** bugs that occur when threads try to access or modify shared data simultaneously.
- Ensures **data integrity** and predictable program behavior.

#### 🧠 Real-life analogy

Imagine a bathroom with a lock: only one person can use it at a time, and others must wait for it to be unlocked. That’s how a mutex works!

---

### 📦 Wrapper Function

A **wrapper function** is a function that  adds safety or logging around thread/mutex call, calls another function, often adding extra behavior before or after the call.

- Think of it as a "helper" or "cover" around an existing function.
- Useful for logging, error handling, or simplifying complex APIs.
