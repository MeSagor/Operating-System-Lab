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
    vector<int> pages(noPage);
    vector<pair<int, int>> frames(noFrame, { -1, -1 });
    for (int& x : pages) cin >> x;

    int firstIdx = 0, pageFaults = 0;
    for (int i = 0; i < noPage; i++) {
        cout << pages[i] << "  ";
        bool pageFound = false;
        for (int j = 0; j < noFrame; j++) {
            if (pages[i] == frames[j].first) {
                frames[j].second = i;
                pageFound = true;
                break;
            }
        }

        if (!pageFound) {
            int LRU = 10000, LRU_idx = -1;
            for (int j = 0; j < noFrame; j++) {
                if (frames[j].second < LRU) {
                    LRU = frames[j].second;
                    LRU_idx = j;
                }
            }
            frames[LRU_idx] = { pages[i], i };
            pageFaults++;
            for (auto x : frames) cout << x.first << ' ';
        }
        cout << endl;
    }
    cout << "Total Page Faults: " << pageFaults << endl;
}
