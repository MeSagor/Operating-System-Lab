#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void pageFaults(int n, int f, vector<int> pages) {
    int pageFault = 0;
    vector<int> frames;
    map<int, int>mp;

    for (int i = 0; i < n; i++) {
        cout << pages[i] << "  ";
        auto it = find(frames.begin(), frames.end(), pages[i]);

        if (it == frames.end()) {
            if (frames.size() == f) {
                mp[frames[0]]--;
                frames.erase(frames.begin());
            }
            frames.push_back(pages[i]);
            mp[pages[i]]++;
            pageFault++;
        } else {
            mp[pages[i]]++;
            frames.erase(it);
            frames.push_back(pages[i]);
        }

        int k = frames.size() - 2;
        while (mp[k] > mp[k + 1] and k >= 0) {
            swap(frames[k], frames[k + 1]);
            k--;
        }
        for (auto x : frames) cout << x << ' ';
        cout << endl;
    }
    cout << "Total Page Faults: " << pageFault << endl;
}


int main() {
    freopen("input.txt", "r", stdin);

    int noPage, noFrame;
    cin >> noPage >> noFrame;
    vector<int>pages(noPage);
    for (int& x : pages) cin >> x;

    pageFaults(noPage, noFrame, pages);
}
