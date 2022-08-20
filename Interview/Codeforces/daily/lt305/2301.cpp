
#include <iostream>
#include <vector>
#include <bitset>
using namespace  std;
bitset<5000> ans;
bitset<5000> old[128];
bitset<5000> _new[128];

class Solution {
public:
    bool matchReplacement(string s, string sub, vector<vector<char>> &mappings) {
        for (int i = 0; i < 128; i++)
            _new[i].reset();
        for (int i = 0; i < s.size(); i++)
            _new[s[i]].set(i);
        for (int i = 0; i < 128; i++)
            old[i] = _new[i];
        for (auto &map : mappings)
            old[map[0]] |= _new[map[1]];
        ans.set();
        for (int i = 0; i < sub.size(); i++)
            ans &= old[sub[i]] >> i;
        return ans.count();
    }
};

int main() {
    char c = 'a' - 1;
    if (c < 'a') {
        c += 26;
    } else if (c >'z') {
        c -= 26;
    }
    cout << c << endl;
}