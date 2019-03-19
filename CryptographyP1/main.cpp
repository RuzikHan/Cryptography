#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

string s;
string alpha = "abcdefghijklmnopqrstuvwxyz";
string alphafreq = "etaoinshrdlcumwfgypbvkjxqz";

string code(string line, string key) {
    int pos = 0, keypos = 0;
    string ans = "";
    while (pos < line.length()) {
        auto checkcode = int(line[pos]);
        auto keycode = int(key[keypos]);
        checkcode -= 97;
        keycode -= 96;
        ans += alpha[(checkcode + keycode) % 26];
        keypos = (keypos + 1) % key.length();
        pos++;
    }
    return ans;
}

string decode(string line, string key) {
    int pos = 0, keypos = 0;
    string ans = "";
    while (pos < line.length()) {
        auto checkcode = int(line[pos]);
        auto keycode = int(key[keypos]);
        checkcode -= 97;
        keycode -= 96;
        ans += alpha[(checkcode - keycode + 26) % 26];
        keypos = (keypos + 1) % key.length();
        pos++;
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    freopen("028.cipher", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> s;
    for (int i = 6; i <= 10; i++) {
        string key = "";
        for (int j = 0; j < i; j++) {
            vector<pair<int, char>> numc;
            for (int k = 0; k < 26; k++)
                numc.push_back(make_pair(0, alpha[k]));
            for (int k = 0; k < s.length(); k++) {
                if (k % i == j) {
                    auto checkcode = int(s[k]);
                    numc[checkcode - 97].first++;
                }
            }
            sort(numc.begin(), numc.end());
            reverse(numc.begin(), numc.end());
            vector<int> diff;
            diff.resize(26, 0);
            for (int k = 0; k < 26; k++) {
                char c = numc[k].second;
                char ck = alphafreq[k];
                diff[((int) c - (int) ck + 26) % 26]++;
            }
            bool f = false;
            int save = -1;
            for (int k = 0; k < 26; k++) {
                if (diff[k] >= 9) {
                    f = true;
                    save = k;
                    break;
                }
            }
            if (f) {
                key += alpha[save - 1];
            } else break;
        }
        if (key.length() == i) {
            cout << decode(s, key);
            exit(0);
        }
    }
    return 0;
}