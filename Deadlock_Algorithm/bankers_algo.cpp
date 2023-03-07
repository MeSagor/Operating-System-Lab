#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int type_a;
    int type_b;
    int type_c;
    int max_type_a;
    int max_type_b;
    int max_type_c;
    int need_type_b;
    int need_type_c;
    int need_type_a;
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
        cout << "Resources_available: ";
        cout << r.type_a << ' ' << r.type_b << ' ' << r.type_c << " [" << id << "]" << endl;
        bool is_deadlock = true;
        for (int i = 0; i < n; i++) {
            if (!p[i].is_completed) {
                if (p[i].need_type_a <= r.type_a and p[i].need_type_b <= r.type_b and p[i].need_type_c <= r.type_c) {
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
                << "No Safe Sequence Found....!";
            return;
        }
    }

    cout << endl << "One of the Safe Sequence: ";
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
        cin >> p[i].type_a >> p[i].type_b >> p[i].type_c >> p[i].max_type_a >> p[i].max_type_b >> p[i].max_type_c;
        p[i].pid = i;
        p[i].need_type_a = p[i].max_type_a - p[i].type_a;
    }

    // for (auto x : p) {
    //     cout << x.type_a << ' ' << x.type_b << ' ' << x.type_c << endl;
    // }

    Check(n, r, p);
}

