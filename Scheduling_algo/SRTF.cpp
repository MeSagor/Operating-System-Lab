#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct process {
    int pid;
    int burst_time;
    int burst_remain;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    bool is_completed;
};


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

void print_gantt_chart(vector<pair<int, int>>& list) {
    cout << "Gantt Chart:" << endl;

    int time = 0, n = list.size();
    for (int i = 0; i < n; i++) {
        cout << "|\tp" << list[i].first << "\t";
    }
    cout << "|" << endl;
    cout << "0";
    for (int i = 0; i < n; i++) {
        time += list[i].second;
        cout << "\t\t" << time;
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;
    vector<process> readyQueue(n);
    for (int i = 0; i < n; i++) {
        cin >> readyQueue[i].burst_time >> readyQueue[i].arrival_time;
        readyQueue[i].pid = i + 1;
        readyQueue[i].burst_remain = readyQueue[i].burst_time;
        readyQueue[i].is_completed = false;
    }

    vector<pair<int, int>> list;
    int time = 0, completed = 0, prv_selectedIdx = -1, burstUsed = 0;
    while (completed != n) {
        int selectedProcessIdx = -1, min_burst = 1000;
        for (int i = 0; i < n; i++) {
            if (!readyQueue[i].is_completed and readyQueue[i].arrival_time <= time) {
                if (readyQueue[i].burst_remain < min_burst) {
                    min_burst = readyQueue[i].burst_remain;
                    selectedProcessIdx = i;
                } else if (readyQueue[i].burst_remain == min_burst) {
                    if (readyQueue[i].arrival_time < readyQueue[selectedProcessIdx].arrival_time) {
                        selectedProcessIdx = i;
                    }
                }
            }
        }

        if (selectedProcessIdx != -1) {
            if (selectedProcessIdx != prv_selectedIdx) {
                if (prv_selectedIdx != -1) {
                    list.push_back({ readyQueue[prv_selectedIdx].pid, burstUsed });
                }
                prv_selectedIdx = selectedProcessIdx;
                burstUsed = 1;
            } else {
                burstUsed++;
            }

            readyQueue[selectedProcessIdx].burst_remain--;
            time++;
            if (readyQueue[selectedProcessIdx].burst_remain == 0) {
                readyQueue[selectedProcessIdx].is_completed = true;
                readyQueue[selectedProcessIdx].turnaround_time = time - readyQueue[selectedProcessIdx].arrival_time;
                readyQueue[selectedProcessIdx].waiting_time = readyQueue[selectedProcessIdx].turnaround_time
                    - readyQueue[selectedProcessIdx].burst_time;
                completed++;
            }
        } else {
            time++;
        }
    }
    list.push_back({ readyQueue[prv_selectedIdx].pid, burstUsed });

    print_table(readyQueue, n);
    cout << endl;
    print_gantt_chart(list);
}
