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

void Check(vector<Process>& p_list, Resource& available, int n) {
    int completed = 0, id = -1;
    vector<int> safe_sequence;
    while (completed != n) {
        cout << "Resources_available: ";
        cout << available.type_a << ' ' << available.type_b << ' ' << available.type_c << " [" << id << "]" << endl;

        bool is_unsafe = true;
        for (int i = 0; i < n; i++) {
            if (!p_list[i].is_completed) {
                if (p_list[i].need_type_a <= available.type_a and p_list[i].need_type_b <= available.type_b
                    and p_list[i].need_type_c <= available.type_c) {
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
    
    // 3 3 2
    // 5
    // 0 1 0 7 5 3
    // 2 0 0 3 2 2
    // 3 0 2 9 0 2
    // 2 1 1 2 2 2
    // 0 0 2 4 3 3

    Resource available;
    cin >> available.type_a >> available.type_b >> available.type_c;
    int n;
    cin >> n;
    vector<Process> p_list(n);
    for (int i = 0; i < n; i++) {
        cin >> p_list[i].type_a >> p_list[i].type_b >> p_list[i].type_c
            >> p_list[i].max_type_a >> p_list[i].max_type_b >> p_list[i].max_type_c;
        p_list[i].pid = i + 1;
        p_list[i].need_type_a = p_list[i].max_type_a - p_list[i].type_a;
        p_list[i].need_type_b = p_list[i].max_type_b - p_list[i].type_b;
        p_list[i].need_type_c = p_list[i].max_type_c - p_list[i].type_c;
    }

    Check(p_list, available, n);
}

