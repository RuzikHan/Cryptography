#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";


static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const *bytes_to_encode, unsigned int in_len) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';

    }

    return ret;

}

std::string base64_decode(std::string const &encoded_string) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_];
        in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = 0; j < i; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }

    return ret;
}

string encode(vector<int> data) {
    string s;
    for (int i : data)
        s += (char) i;
    return base64_encode(reinterpret_cast<const unsigned char *>(s.c_str()), s.length());
}

vector<int> decode(const string &s) {
    string data = base64_decode(s);
    vector<int> ans;
    for (char i : data)
        ans.push_back((int) i);
    return ans;
}

string line_cast(vector<int> data) {
    string ans;
    for (int i = 0; i < data.size(); i++) {
        int x = data[i];
        char c = (char) x;
        ans += c;
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    string message;
    cin >> message;
    string iv;
    cin >> iv;
    vector<int> byte_iv = decode(iv);
    int old = byte_iv[2];
    byte_iv[2] = 0;
    string try_iv = encode(byte_iv);
    cout << "NO" << endl;
    cout << message << endl;
    cout << try_iv << endl;
    string ans;
    cin >> ans;
    if (ans != "Ok") {
        cout << "YES" << endl;
        cout << "No" << endl;
    } else {
        byte_iv[2] = old;
        byte_iv[2] ^= 's' ^ 0x0e;
        for (int i = 3; i < 16; i++)
            byte_iv[i] ^= 0x0d ^ 0x0e;
        try_iv = encode(byte_iv);
        cout << "NO" << endl;
        cout << message << endl;
        cout << try_iv << endl;
        cin >> ans;
        if (ans == "Ok") {
            cout << "YES" << endl;
            cout << "Yes" << endl;
        } else {
            cout << "YES" << endl;
            cout << "N/A" << endl;
        }
    }
}