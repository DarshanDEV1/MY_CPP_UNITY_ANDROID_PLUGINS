#include <iostream>
#include <queue>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

// Task struct representing each task
struct Task {
    int gameId;
    int taskType;
    int priority; 
    int executionTime; // Time the task needs to execute (in milliseconds)
    
    Task(int gId, int tType, int prio, int execTime) 
        : gameId(gId), taskType(tType), priority(prio), executionTime(execTime) {}
};

// Enum for scheduling algorithms
enum SchedulingAlgorithm { ROUND_ROBIN, PRIORITY };

class Scheduler {
private:
    std::queue<Task> roundRobinQueue;  // Queue for Round Robin
    std::priority_queue<Task, std::vector<Task>, std::function<bool(Task, Task)>> priorityQueue;  // Queue for Priority Scheduling
    SchedulingAlgorithm algorithm;
    std::mutex queueMutex;
    int timeQuantum; // Used for Round Robin
    
public:
    Scheduler(SchedulingAlgorithm alg, int quantum = 50) : algorithm(alg), timeQuantum(quantum),
        priorityQueue([](Task a, Task b) { return a.priority < b.priority; }) {}

    // Set the scheduling algorithm and time quantum
    void SetAlgorithm(SchedulingAlgorithm alg, int quantum) {
        std::lock_guard<std::mutex> lock(queueMutex);
        algorithm = alg;
        timeQuantum = quantum;
    }

    // Add a task to the queue
    void AddTask(Task task) {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (algorithm == ROUND_ROBIN) {
            roundRobinQueue.push(task);
        } else if (algorithm == PRIORITY) {
            priorityQueue.push(task);
        }
    }

    // Fetch the next task to execute
    bool GetNextTask(Task& task) {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (algorithm == ROUND_ROBIN && !roundRobinQueue.empty()) {
            task = roundRobinQueue.front();
            roundRobinQueue.pop();
            return true;
        } else if (algorithm == PRIORITY && !priorityQueue.empty()) {
            task = priorityQueue.top();
            priorityQueue.pop();
            return true;
        }
        return false;
    }

    // Execute the tasks using worker threads
    void ExecuteTasks() {
        while (true) {
            Task task(0, 0, 0, 0);
            if (GetNextTask(task)) {
                std::cout << "Executing Task from Game " << task.gameId 
                          << " with Type " << task.taskType 
                          << " and Priority " << task.priority << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(task.executionTime));
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep when no tasks
            }
        }
    }
};

// Global scheduler instance
Scheduler scheduler(ROUND_ROBIN);

// Exposing the C++ functions to Unity (C#)
extern "C" {

    // Set the scheduling algorithm (Android-compatible attribute)
    __attribute__((visibility("default"))) void SetSchedulingAlgorithm(int algorithmType, int quantum) {
        scheduler.SetAlgorithm(static_cast<SchedulingAlgorithm>(algorithmType), quantum);
    }

    // Add a task to the scheduler (Android-compatible attribute)
    __attribute__((visibility("default"))) void AddTask(int gameId, int taskType, int priority, int executionTime) {
        Task newTask(gameId, taskType, priority, executionTime);
        scheduler.AddTask(newTask);
    }

    // Start executing tasks (run on a separate thread from Unity) (Android-compatible attribute)
    __attribute__((visibility("default"))) void StartTaskExecution() {
        std::thread workerThread(&Scheduler::ExecuteTasks, &scheduler);
        workerThread.detach();  // Detach the worker thread so it runs independently
    }
}
