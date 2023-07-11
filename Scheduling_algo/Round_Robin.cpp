#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

struct process {
    int pid;
    int burst_time;
    int burst_remain;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    bool is_completed;
    bool is_in_ready_queue;
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

bool cmp(process p1, process p2) {
    if (p1.arrival_time != p2.arrival_time) return p1.arrival_time < p2.arrival_time;
    else return p1.pid < p2.pid;
}

bool cmp1(process p1, process p2) {
    return p1.pid < p2.pid;
}

int main() {
    freopen("input.txt", "r", stdin);

    // 4 2
    // 5 0
    // 4 1
    // 2 2
    // 1 4

    int n, timeQuantum;
    cin >> n >> timeQuantum;
    vector<process> p_list(n);
    for (int i = 0; i < n; i++) {
        cin >> p_list[i].burst_time >> p_list[i].arrival_time;
        p_list[i].pid = i + 1;
        p_list[i].burst_remain = p_list[i].burst_time;
        p_list[i].is_completed = false;
        p_list[i].is_in_ready_queue = false;
    }

    sort(p_list.begin(), p_list.end(), cmp);

    vector<pair<int, int>> list;
    queue<int>readyQueue;
    int time = 0, completed = 0;
    while (completed != n) {
        int selected_pidx = -1;
        if (!readyQueue.empty()) {
            selected_pidx = readyQueue.front();
            readyQueue.pop();
            p_list[selected_pidx].is_in_ready_queue = false;
        }

        if (selected_pidx != -1) {
            if (p_list[selected_pidx].burst_remain - timeQuantum > 0) {
                p_list[selected_pidx].burst_remain -= timeQuantum;
                time += timeQuantum;
                list.push_back({ p_list[selected_pidx].pid, timeQuantum });
            } else {
                time += p_list[selected_pidx].burst_remain;
                list.push_back({ p_list[selected_pidx].pid, p_list[selected_pidx].burst_remain });
                p_list[selected_pidx].burst_remain = 0;
                completed++;

                p_list[selected_pidx].turnaround_time = time - p_list[selected_pidx].arrival_time;
                p_list[selected_pidx].waiting_time = p_list[selected_pidx].turnaround_time -
                    p_list[selected_pidx].burst_time;
                p_list[selected_pidx].is_completed = true;
            }
        }

        // check for new process
        for (int i = 0; i < n; i++) {
            if (!p_list[i].is_completed and p_list[i].arrival_time <= time and !p_list[i].is_in_ready_queue and i != selected_pidx) {
                readyQueue.push(i);
                p_list[i].is_in_ready_queue = true;
            }
        }

        if (selected_pidx != -1) {
            if (p_list[selected_pidx].burst_remain > 0) {
                readyQueue.push(selected_pidx);
                p_list[selected_pidx].is_in_ready_queue = true;
            }
        }

        if (readyQueue.empty()) {
            time++;
        }

    }

    sort(p_list.begin(), p_list.end(), cmp1);


    print_table(p_list, n);
    cout << endl;
    print_gantt_chart(list);
}
