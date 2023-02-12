#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

struct Process {
    int pid;
    int brust_time;
    int brust_remain;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int start_time;
    int complete_time;
    bool is_complete;
    bool is_in_ready_queue;
};


void print_table(vector<Process>& p, int n) {
    cout << "TABLE:" << endl;
    puts("+-----+------------+--------------+-----------------+--------------+---------------+");
    puts("| PID | Burst Time | Arrival Time | Turnaround Time | Waiting Time | Complete Time |");
    puts("+-----+------------+--------------+-----------------+--------------+---------------+");

    for (int i = 0; i < n; i++) {
        printf("| %2d  |     %2d     |      %2d      |        %2d       |      %2d      |      %2d       |\n"
            , p[i].pid, p[i].brust_time, p[i].arrival_time, p[i].turnaround_time, p[i].waiting_time, p[i].complete_time);
        puts("+-----+------------+--------------+-----------------+--------------+---------------+");
    }
}

bool cmp(Process p1, Process p2) {
    if (p1.arrival_time != p2.arrival_time) return p1.arrival_time < p2.arrival_time;
    else return p1.pid < p2.pid;
}
bool cmp1(Process p1, Process p2) {
    return p1.pid < p2.pid;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n, time_quantum;
    cin >> n >> time_quantum;
    vector<Process>p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].brust_time >> p[i].arrival_time;
        p[i].pid = i + 1;
        p[i].brust_remain = p[i].brust_time;
        p[i].is_complete = false;
        p[i].is_in_ready_queue = false;
    }
    sort(p.begin(), p.end(), cmp);
    // for (int i = 0; i < n; i++) {
    //     cout << p[i].pid << " " << p[i].brust_time << " " << p[i].arrival_time << " " << p[i].complete_time << " " << p[i].waiting_time << " " << p[i].turnaround_time << endl;
    // }

    queue<int>ready_queue;
    int time = 0, completed = 0;
    vector<pair<pair<int, int>, pair<int, int>>>list(100);
    int cnt = 0;
    while (completed != n) {
        int idx = -1;
        if (!ready_queue.empty()) {
            idx = ready_queue.front();
            ready_queue.pop();
            p[idx].is_in_ready_queue = false;
        }

        // cout << p[idx].pid << endl;
        if (idx != -1) {
            if (p[idx].brust_remain - time_quantum > 0) {
                p[idx].brust_remain -= time_quantum;
                time += time_quantum;

                list[cnt] = { {p[idx].pid, time_quantum}, {p[idx].brust_remain, time} };
                cnt++;
            } else {
                list[cnt] = { {p[idx].pid, p[idx].brust_remain}, {0, time} };
                cnt++;

                time += p[idx].brust_remain;
                p[idx].brust_remain = 0;
                completed++;

                p[idx].complete_time = time;
                p[idx].turnaround_time = p[idx].complete_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].brust_time;
                p[idx].is_complete = true;
            }
        }
        for (int i = 0; i < n; i++) {
            if (!p[i].is_complete and p[i].arrival_time <= time and !p[i].is_in_ready_queue and i != idx) {
                ready_queue.push(i);
                p[i].is_in_ready_queue = true;
            }
        }
        if (idx != -1) {
            if (p[idx].brust_remain > 0) {
                ready_queue.push(idx);
                p[idx].is_in_ready_queue = true;
            }
        }
        if (ready_queue.empty()) {
            time++;
        }
    }
    sort(p.begin(), p.end(), cmp1);

    puts("+-----+------------+--------------+------+");
    puts("| PID | Cycle Use  | Burst Remain | Time |");
    puts("+-----+------------+--------------+------+");
    for (int i = 0; i < cnt; i++) {
        printf("| %2d  |     %2d     |      %2d      |  %2d  |\n", list[i].first.first, list[i].first.second, list[i].second.first, list[i].second.second);
        puts("+-----+------------+--------------+------+");
    }
    cout << endl;
    print_table(p, n);

    // for (int i = 0; i < n; i++) {
    //     cout << p[i].pid << " " << p[i].brust_time << " " << p[i].arrival_time << " " << p[i].complete_time << " " << p[i].waiting_time << " " << p[i].turnaround_time << endl;
    // }
}