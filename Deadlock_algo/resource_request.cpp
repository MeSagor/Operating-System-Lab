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

void Check(vector<Process>& p_list, Resource& available, int n) {
    for (int i = 0; i < n; i++) {
        p_list[i].is_completed = false;
    }
    int completed = 0, id = -1;
    vector<int> safe_sequence;
    while (completed != n) {
        cout << "Resources_available: ";
        cout << available.type_a << ' ' << available.type_b << ' ' << available.type_c << " [" << id << "]" << endl;

        bool is_unsafe = true;
        for (int i = 0; i < n; i++) {
            if (!p_list[i].is_completed) {
                if (p_list[i].request_type_a <= available.type_a and p_list[i].request_type_b <= available.type_b
                    and p_list[i].request_type_c <= available.type_c) {
                    id = p_list[i].pid;
                    p_list[i].is_completed = true;
                    safe_sequence.push_back(p_list[i].pid);
                    completed++;
                    is_unsafe = false;

                    available.type_a += p_list[i].type_a;
                    available.type_b += p_list[i].type_b;
                    available.type_c += p_list[i].type_c;
                    break;
                }
            }
        }
        if (is_unsafe) {
            cout << endl << "No Safe Sequence Found....!" << endl;
            return;
        }
    }
    cout << endl << "One of the Safe Sequence: ";
    for (int x : safe_sequence) {
        cout << x << " ";
    }
    cout << endl;
}


int main() {
    freopen("input.txt", "r", stdin);

    // 3 3 2
    // 5
    // 0 1 0 7 4 3
    // 2 0 0 1 2 2
    // 3 0 2 6 0 0
    // 2 1 1 0 1 1
    // 0 0 2 4 3 1
    // 1
    // 7 4 7

    Resource available, available1;
    cin >> available.type_a >> available.type_b >> available.type_c;
    available1 = available;
    int n;
    cin >> n;
    vector<Process> p_list(n);
    for (int i = 0; i < n; i++) {
        cin >> p_list[i].type_a >> p_list[i].type_b >> p_list[i].type_c
            >> p_list[i].request_type_a >> p_list[i].request_type_b >> p_list[i].request_type_c;
        p_list[i].pid = i + 1;
    }

    Check(p_list, available, n);

    int pid, request_type_a, request_type_b, request_type_c;
    cin >> pid >> request_type_a >> request_type_b >> request_type_c;
    p_list[pid - 1].request_type_a = request_type_a;
    p_list[pid - 1].request_type_b = request_type_b;
    p_list[pid - 1].request_type_c = request_type_c;

    cout << endl << "Can p" << pid << " request (" << request_type_a << ' ' << request_type_b << ' ' << request_type_c << ")?" << endl;
    Check(p_list, available1, n);
}

