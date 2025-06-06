#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

// Function to sort by arrival time and then by priority
bool compareArrival(const Process &a, const Process &b) {
    if (a.arrivalTime == b.arrivalTime) 
        return a.priority < b.priority;
    return a.arrivalTime < b.arrivalTime;
}

// Non-preemptive Priority Scheduling Algorithm
void priorityScheduling(vector<Process> &processes) 
{
    int n = processes.size();
    int currentTime = 0;

    // Sort processes by arrival time and priority
    sort(processes.begin(), processes.end(), compareArrival);

    for (int i = 0; i < n; ++i) {
        int idx = -1;
        int minPriority = INT_MAX;

        // Find the next process with the highest priority that has arrived
        for (int j = 0; j < n; ++j) {
            if (processes[j].arrivalTime <= currentTime && processes[j].completionTime == 0) {
                if (processes[j].priority < minPriority) {
                    minPriority = processes[j].priority;
                    idx = j;
                }
            }
        }

        // If no process has arrived yet, move to the next arrival time
        if (idx == -1) {
            currentTime = processes[i].arrivalTime;
            --i;  // Repeat this iteration
            continue;
        }

        // Execute the selected process
        currentTime += processes[idx].burstTime;
        processes[idx].completionTime = currentTime;
        processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
    }
}

void printResults(const vector<Process> &processes) {
    cout << "ID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &p : processes) {
        cout << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.priority << "\t\t" << p.completionTime << "\t\t"
             << p.turnaroundTime << "\t\t" << p.waitingTime << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter arrival time, burst time, and priority for each process:\n";
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].completionTime = 0;  // Initialize completion time to 0
    }
    
    priorityScheduling(processes);
    printResults(processes);

    return 0;
}
