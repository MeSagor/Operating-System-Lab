#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    freopen("input.txt", "r", stdin);

    // 20 3
    // 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

    int noPage, noFrame;
    cin >> noPage >> noFrame;
    vector<int> pages(noPage), frames(noFrame, -1);
    for (int& x : pages) cin >> x;

    int firstIdx = 0, pageFaults = 0;
    for (int i = 0; i < noPage; i++) {
        cout << pages[i] << "  ";
        bool pageFound = false;
        for (int j = 0; j < noFrame; j++) {
            if (pages[i] == frames[j]) {
                pageFound = true;
                break;
            }
        }

        if (!pageFound) {
            frames[firstIdx] = pages[i];
            firstIdx = (firstIdx + 1) % noFrame;
            pageFaults++;
            for (int x : frames) cout << x << ' ';
        }
        cout << endl;
    }
    cout << endl << "Total Page Faults: " << pageFaults << endl;
}
