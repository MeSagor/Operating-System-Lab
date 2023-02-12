#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Process {
    int pid;
    int brust_time;
    int waiting_time;
    int turnaround_time;
};


void print_table(vector<Process>& p, int n) {
    cout << "TABLE:" << endl;
    puts("+-----+------------+--------------+-----------------+");
    puts("| PID | Burst Time | Waiting Time | Turnaround Time |");
    puts("+-----+------------+--------------+-----------------+");

    for (int i = 0; i < n; i++) {
        printf("| %2d  |     %2d     |      %2d      |        %2d       |\n"
            , p[i].pid, p[i].brust_time, p[i].waiting_time, p[i].turnaround_time);
        puts("+-----+------------+--------------+-----------------+");
    }
}

void print_gantt_chart(vector<Process>& p, int n) {
    cout << endl << "GANTT CHART:" << endl;

    cout << " ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].brust_time; j++) {
            cout << "--";
        }
        cout << " ";
    }
    cout << "\n|";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].brust_time - 1; j++) cout << " ";
        cout << "P" << p[i].pid;
        for (int j = 0; j < p[i].brust_time - 1; j++) cout << " ";
        cout << "|";
    }
    cout << endl;

    cout << " ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].brust_time; j++) {
            cout << "--";
        }
        cout << " ";
    }

    cout << "\n0";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].brust_time; j++) cout << "  ";
        if (p[i].turnaround_time > 9) printf("\b"); // backspace : remove 1 space
        cout << p[i].turnaround_time;
    }
    cout << endl;
}

bool cmp(Process p1, Process p2) {
    if (p1.brust_time != p2.brust_time) return p1.brust_time < p2.brust_time;
    else return p1.pid < p2.pid;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;
    vector<Process>p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].brust_time;
        p[i].pid = i + 1;
    }

    sort(p.begin(), p.end(), &cmp);

    // for (int i = 0; i < n; i++) {
    //     cout << p[i].pid << " " << p[i].brust_time << " " << p[i].waiting_time << " " << p[i].turnaround_time << endl;
    // }

    p[0].turnaround_time = p[0].brust_time;
    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].brust_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].brust_time;
    }

    print_table(p, n);
    print_gantt_chart(p, n);
    cout << endl;

    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
    }
    cout << "Total Waiting Time     : " << total_waiting_time << endl;
    cout << "Average Waiting Time   : " << total_waiting_time / (n * 1.0) << endl;
    cout << "Total Turnaround Time  : " << total_turnaround_time << endl;
    cout << "Average Turnaround Time: " << total_turnaround_time / (n * 1.0) << endl;
}