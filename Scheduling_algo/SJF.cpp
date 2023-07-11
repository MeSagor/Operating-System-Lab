#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct process {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

bool cmp(process p1, process p2) {
    if (p1.burst_time != p2.burst_time) return p1.burst_time < p2.burst_time;
    else return p1.pid < p2.pid;
}

void print_table(vector<process>& p, int n) {
    cout << "TABLE:" << endl;
    puts("+-----+------------+--------------+-----------------+");
    puts("| PID | Burst Time | Waiting Time | Turnaround Time |");
    puts("+-----+------------+--------------+-----------------+");

    for (int i = 0; i < n; i++) {
        // cout << "|  " << p[i].pid << "  |      " << p[i].brust_time << "     |       " << p[i].waiting_time << "      |        " << p[i].turnaround_time << "        |\n";

        printf("| %2d  |     %2d     |      %2d      |        %2d       |\n"
            , p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
        puts("+-----+------------+--------------+-----------------+");
    }
}

void print_gantt_chart(vector<process>& p, int n) {
    cout << "Gantt Chart:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "|\tp" << p[i].pid << "\t";
    }
    cout << "|" << endl;
    cout << "0";
    for (int i = 0; i < n; i++) {
        cout << "\t\t" << p[i].turnaround_time;
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;
    vector<process> readyQueue(n);
    for (int i = 0; i < n; i++) {
        cin >> readyQueue[i].burst_time;
        readyQueue[i].pid = i + 1;
    }

    sort(readyQueue.begin(), readyQueue.end(), cmp);

    readyQueue[0].turnaround_time = readyQueue[0].burst_time;
    for (int i = 1; i < n; i++) {
        readyQueue[i].waiting_time = readyQueue[i - 1].waiting_time + readyQueue[i - 1].burst_time;
        readyQueue[i].turnaround_time = readyQueue[i].waiting_time + readyQueue[i].burst_time;
    }

    print_table(readyQueue, n);
    cout << endl;
    print_gantt_chart(readyQueue, n);
}
