#include <iostream>

using namespace std;

int count0 = 0, countthou = 0;

void trythou() {
    countthou++;
    for (int i = 0; i < 1000; i++) {
        int c;
        cin >> c;
        cout << 0 << endl;
        string s;
        cin >> s;
        if (s.length() == 3) {
            if (c == 1) count0++;
        } else {
            if (c == 0) count0++;
        }
    }
}

int main() {
    trythou();
    bool f = true;
    double p = (double) count0 / (double) (countthou * 1000);
    while (f) {
        if (p >= 0.7) {
            f = false;
            for (int i = 0; i < 10000 - countthou * 1000; i++) {
                int c;
                cin >> c;
                if (c == 0) cout << 1 << endl; else cout << 0 << endl;
                string s;
                cin >> s;
            }
        } else if (p <= 0.3) {
            f = false;
            for (int i = 0; i < 10000 - countthou * 1000; i++) {
                int c;
                cin >> c;
                cout << c << endl;
                string s;
                cin >> s;
            }
        } else {
            if (countthou < 10) {
                trythou();
                p = (double) count0 / (double) (countthou * 1000);
            } else {
                f = false;
            }
        }
    }
    return 0;
}