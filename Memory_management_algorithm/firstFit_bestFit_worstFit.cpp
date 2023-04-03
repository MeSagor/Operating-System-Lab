#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void firstFit(vector<int>bsizes, int bn, vector<int>psizes, int pn) {
    vector<int> allocation(pn, -1);

    for (int i = 0; i < pn; i++) {
        for (int j = 0; j < bn; j++) {
            if (bsizes[j] >= psizes[i]) {
                allocation[i] = j;
                bsizes[j] -= psizes[i];
                break;
            }
        }
    }

    cout << "Process No.\tProcess Size.\tBlock no.\n";
    for (int i = 0; i < pn; i++) {
        cout << " " << i + 1 << "\t\t" << psizes[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

void bestFit(vector<int>bsizes, int bn, vector<int>psizes, int pn) {
    vector<int> allocation(pn, -1);

    for (int i = 0; i < pn; i++) {
        int worstIdx = -1;
        for (int j = 0; j < bn; j++) {
            if (bsizes[j] >= psizes[i]) {
                if (worstIdx == -1) worstIdx = j;
                else if (bsizes[worstIdx] > bsizes[j]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            bsizes[worstIdx] -= psizes[i];
        }
    }

    cout << "Process No.\tProcess Size.\tBlock no.\n";
    for (int i = 0; i < pn; i++) {
        cout << " " << i + 1 << "\t\t" << psizes[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

void worstFit(vector<int>bsizes, int bn, vector<int>psizes, int pn) {
    vector<int> allocation(pn, -1);

    for (int i = 0; i < pn; i++) {
        int worstIdx = -1;
        for (int j = 0; j < bn; j++) {
            if (bsizes[j] >= psizes[i]) {
                if (worstIdx == -1) worstIdx = j;
                else if (bsizes[worstIdx] < bsizes[j]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            bsizes[worstIdx] -= psizes[i];
        }
    }

    cout << "Process No.\tProcess Size.\tBlock no.\n";
    for (int i = 0; i < pn; i++) {
        cout << " " << i + 1 << "\t\t" << psizes[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}



int main() {
    freopen("input.txt", "r", stdin);

    int bn, pn;
    cin >> bn >> pn;
    vector<int>bsizes(bn), psizes(pn);
    for (int i = 0; i < bn; i++) {
        cin >> bsizes[i];
    }
    for (int i = 0; i < pn; i++) {
        cin >> psizes[i];
    }

    cout << endl << "Block Sizes: ";
    for (int x : bsizes) cout << x << ' ';
    cout << endl << "Process Sizes: ";
    for (int x : psizes)cout << x << ' ';

    cout << endl << endl << "First Fit: " << endl;
    firstFit(bsizes, bn, psizes, pn);
    cout << endl << "Best Fit: " << endl;
    bestFit(bsizes, bn, psizes, pn);
    cout << endl << "Worst Fit: " << endl;
    worstFit(bsizes, bn, psizes, pn);
}
