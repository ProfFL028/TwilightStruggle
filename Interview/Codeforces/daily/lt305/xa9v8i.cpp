#include <vector>
#include <iostream>

using namespace  std;

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        n = s.size();
        vector<string> path;
        dfs(s, 0, wordDict, path);
        return ans;
    }

    void dfs(const string &s, int position, const vector<string>&  wordDict, vector<string>& path) {
        if (position == n) {
            string a = "";
            for (int i = 0; i < path.size(); i++) {
                a += path[i];
                if (i < path.size() - 1) {
                    a += "";
                }
            }

            this->ans.push_back(a);
            return ;
        }
        for (auto& word : wordDict) {
            if (position + word.size() <= n && s.substr(position, word.size()) == word) {
                path.push_back(word);
                dfs(s, position + word.size(), wordDict, path);
                path.pop_back();
            }
        }
    }

    int n;
    vector<string> ans;
};

int main() {
    string s = "catsanddog";
    vector<string> wordDict {"cat","cats","and","sand","dog"};
    Solution solution;
    solution.wordBreak(s, wordDict);

    return 0;
}