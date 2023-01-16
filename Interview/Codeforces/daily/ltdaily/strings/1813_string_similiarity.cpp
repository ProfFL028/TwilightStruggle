// https://leetcode.cn/problems/sentence-similarity-iii/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        vector<string_view> words1 = split(sentence1, ' ');
        vector<string_view> words2 = split(sentence2, ' ');
        int i = 0, j = 0;
        while (i < words1.size() && i < words2.size() && words1[i] == words2[i])
            i++;
        while (j < words1.size() - i && j < words2.size() - i && words1[words1.size() - j - 1] == words2[words2.size() - j - 1])
            j++;

        return i + j == min(words1.size(), words2.size());
    }

    vector<string_view> split(const string& str, char target) {
        vector<string_view> result;
        string_view strView(str);
        int strSize = str.size();
        int pos = 0;
        while (pos < strSize) {
            while (pos <strSize && strView[pos] == target)
                pos++;
            int start = pos;
            while (pos <strSize && strView[pos] != target)
                pos++;
            if (pos > start) {
                result.emplace_back(strView.substr(start, pos - start));
            }
        }

        return result;
    }
};

int main() {
    Solution solution;
    cout << solution.areSentencesSimilar("Hello world", "Hello your world") << endl;
}
