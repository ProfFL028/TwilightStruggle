#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;
struct Trie
{
    Trie* child[26];
    string word = "";
    Trie() {
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;
    }
};
class Solution {
public:
    vector<string> res;
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie* t = new Trie();
        //创建前缀树，将words中所有单词加入前缀树
        for (int i = 0; i < words.size(); i++)
        {
            Trie* cur = t;
            for (int j = 0; j < words[i].size(); j++)
            {
                if (cur->child[words[i][j] - 'a'] == nullptr)
                    cur->child[words[i][j] - 'a'] = new Trie();
                cur = cur->child[words[i][j] - 'a'];
            }
            cur->word = words[i];
        }
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                dfs(board, t, i, j);
            }
        }
        return res;
    }
    void dfs(vector<vector<char>>& board, Trie* t,int i ,int j)
    {
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size())
            return;
        char c = board[i][j];
        if (c == '*' || t->child[c-'a']==nullptr)
            return;
        t = t->child[c - 'a'];
        if (t->word != "")
        {
            res.push_back(t->word);
            t->word = "";
        }
        board[i][j] = '*';
        dfs(board, t, i + 1, j);
        dfs(board, t, i - 1, j);
        dfs(board, t, i, j + 1);
        dfs(board, t, i, j - 1);
        board[i][j] = c;
        return;
    }
};

int main() {
    Solution solution;

    vector<vector<char>> board{{'a','b','c'},{'a','e','d'},{'a','f','g'}};
    vector<string> word{"abcdefg","gfedcbaaa","eaabcdgfa","befa","dgc","ade"};

    solution.findWords(board, word);
}