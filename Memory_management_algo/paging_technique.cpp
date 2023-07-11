#include<iostream>

using namespace std;

int main() {
    int memsize = 20;
    int pagesize;
    int p[100];

    cout << "Your memsize is: " << memsize << endl;
    cout << "Enter page size: ";
    cin >> pagesize;

    int nofpage = memsize / pagesize;

    for (int i = 0; i < nofpage; i++) {
        printf("\nEnter the frame of page-%d: ", i + 1);
        scanf("%d", &p[i]);
    }

    while (true) {
        printf("\nEnter a logical address: ");
        int logadd;
        cin >> logadd;
        int pageno = logadd / pagesize;
        int offset = logadd % pagesize;
        int phyadd = (p[pageno] * pagesize) + offset;
        cout << "Physical address is: " << phyadd << endl;
    }
}