#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid;            // Process ID
    int arrivalTime;    // Arrival time of the process
    int burstTime;      // Burst time (time required for execution)
    int remainingTime;  // Remaining time for execution
    int completionTime; // Completion time of the process
    int waitingTime;    // Waiting time in the queue
    int turnaroundTime; // Turnaround time
};

bool arrivalComparator(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;  // imp *
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), arrivalComparator);

    int currentTime = 0;
    int completed = 0;
    int minRemainingTime;
    int shortest = 0;
    bool foundProcess;

    while (completed != n) 
    {
        minRemainingTime = INT_MAX;
        foundProcess = false;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < minRemainingTime) {
                    minRemainingTime = processes[i].remainingTime;
                    shortest = i;
                    foundProcess = true;
                }
            }
        }

        if (!foundProcess) {
            currentTime++;
            continue;
        }

        processes[shortest].remainingTime--;
        currentTime++;

        if (processes[shortest].remainingTime == 0) {
            completed++;
            processes[shortest].completionTime = currentTime;
            processes[shortest].turnaroundTime = processes[shortest].completionTime - processes[shortest].arrivalTime;
            processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime;
        }
    }

    // Displaying results
    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].pid << "\t\t"
             << processes[i].arrivalTime << "\t\t"
             << processes[i].burstTime << "\t\t"
             << processes[i].completionTime << "\t\t"
             << processes[i].turnaroundTime << "\t\t"
             << processes[i].waitingTime << endl;
    }

    // Calculating average waiting and turnaround time
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    cout << "\nAverage Waiting Time: " << totalWaitingTime / n;
    cout << "\nAverage Turnaround Time: " << totalTurnaroundTime / n << endl;

    return 0;
}

