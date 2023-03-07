#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int type_a;
    int type_b;
    int type_c;
    int request_type_a;
    int request_type_b;
    int request_type_c;
    bool is_completed = false;
};
struct Resource {
    int type_a;
    int type_b;
    int type_c;
};

void Check(int n, Resource& r, vector<Process>& p) {
    int completed = 0, id = -1;
    vector<int> safe_sequence;
    while (completed != n) {
        cout << "Resources_Avaiable: ";
        cout << r.type_a << ' ' << r.type_b << ' ' << r.type_c << " [" << id << "]" << endl;
        bool is_deadlock = true;
        for (int i = 0; i < n; i++) {
            if (!p[i].is_completed) {
                if (p[i].request_type_a <= r.type_a and p[i].request_type_b <= r.type_b and p[i].request_type_c <= r.type_c) {
                    id = p[i].pid;
                    p[i].is_completed = true;
                    safe_sequence.push_back(p[i].pid);
                    is_deadlock = false;
                    completed++;
                    r.type_a += p[i].type_a;
                    r.type_b += p[i].type_b;
                    r.type_c += p[i].type_c;
                    break;
                }
            }
        }
        if (is_deadlock) {
            cout << endl
                << "DeadLock....!";
            return;
        }
    }

    cout << endl << "No DeadLock\nOne Safe Sequence: ";
    for (int x : safe_sequence) {
        cout << x << " ";
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;
    Resource r;
    cin >> r.type_a >> r.type_b >> r.type_c;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].type_a >> p[i].type_b >> p[i].type_c >> p[i].request_type_a >> p[i].request_type_b >> p[i].request_type_c;
        p[i].pid = i;
    }

    // for (auto x : p) {
    //     cout << x.type_a << ' ' << x.type_b << ' ' << x.type_c << endl;
    // }

    Check(n, r, p);
}
