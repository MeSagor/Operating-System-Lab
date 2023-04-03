#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    freopen("input.txt", "r", stdin);

    int noPage, noFrame;
    cin >> noPage >> noFrame;
    vector<int>pages(noPage), frames(noFrame, -1);
    for (int& x : pages) cin >> x;

    int first = 0, pageFault = 0;
    for (int i = 0; i < noPage; i++) {
        cout << pages[i] << "  ";
        bool pageFound = false;
        for (int j = 0; j < noFrame; j++) {
            if (frames[j] == pages[i]) {
                pageFound = true;
                break;
            }
        }

        if (!pageFound) {
            frames[first] = pages[i];
            first = (first + 1) % noFrame;
            pageFault++;
            for (int x : frames) cout << x << ' ';
        }
        cout << endl;
    }
    cout << "Total Page Faults: " << pageFault << endl;
}
