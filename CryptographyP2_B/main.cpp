#include <iostream>
#include <vector>

using namespace std;

int count0 = 0, countthou = 0;

vector<int> bit;

void trythou() {
    countthou++;
    for (int i = 0; i < 1000; i++) {
        int c;
        cin >> c;
        cout << 0 << endl;
        string s;
        cin >> s;
        if (s.length() == 3) {
            bit.push_back(c);
        } else {
            if (c == 0) bit.push_back(1); else bit.push_back(0);
        }
    }
}

int main() {
    trythou();
    trythou();
    int per = 1000;
    bool f = true;
    while (f) {
        bool pf = true;
        for (int i = 0; i < per; i++) {
            if (bit[i] != bit[i + per]) {
                pf = false;
                break;
            }
        }
        if (!pf && per > 0) per--; else f = false;
    }
    int k = 1;
    while (k * per < 2000) k++;
    for (int i = 0; i < k * per - 2000; i++) {
        int c;
        cin >> c;
        cout << 0 << endl;
        string s;
        cin >> s;
    }
    int perc = 0;
    for (int i = k * per; i < 10000; i++) {
        if (perc == per) perc = 0;
        int c;
        cin >> c;
        if (c == 0) {
            cout << bit[perc] << endl;
        } else {
            if (bit[perc] == 0) cout << 1 << endl; else cout << 0 << endl;
        }
        string s;
        cin >> s;
        perc++;
    }
    return 0;
}