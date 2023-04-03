#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    freopen("input.txt", "r", stdin);

    int noPage, noFrame;
    cin >> noPage >> noFrame;
    vector<int>pages(noPage);
    vector<pair<int, int>> frames(noFrame, { -1,-1 });
    for (int& x : pages) cin >> x;

    int first = 0, pageFault = 0;
    for (int i = 0; i < noPage; i++) {
        cout << pages[i] << "  ";
        bool pageFound = false;
        for (int j = 0; j < noFrame; j++) {
            if (frames[j].first == pages[i]) {
                frames[j].second = i;
                pageFound = true;
                break;
            }
        }

        if (!pageFound) {
            int LRU = 100000, LRU_idx = -1;
            for (int j = 0; j < noFrame; j++) {
                if (frames[j].second < LRU) {
                    LRU = frames[j].second;
                    LRU_idx = j;
                }
            }
            frames[LRU_idx].first = pages[i];
            frames[LRU_idx].second = i;

            pageFault++;
            for (auto x : frames) cout << x.first << ' ';
        }
        cout << endl;
    }
    cout << "Total Page Faults: " << pageFault << endl;
}
