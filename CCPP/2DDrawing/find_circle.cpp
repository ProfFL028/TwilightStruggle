#include <bits/stdc++.h>

using namespace std;

bool isCyclic(map<string, vector<string>> &graph, unordered_set<string> &visited, const string &u, const string &parent) {
    visited.insert(u);
    for (auto &nxt: graph[u]) {
        if (visited.find(nxt) == visited.end()) {
            if (isCyclic(graph, visited, nxt, "")) {
                cout << nxt << "   contains cyclic" << endl;
                return true;
            }
        } else if (nxt != parent) {
            return true;
        }
    }

    return false;
}

void checkGraph(map<string, vector<string>> &graph) {
    unordered_set<string> visited;
    for (const auto &item: graph) {
        if (visited.find(item.first) == visited.end()) {
            isCyclic(graph, visited, item.first, "");
        }
    }
}

void addToGraph(map<string, vector<string>> &graph, const string &line) {
    string guarantor;
    int idx = 0;
    int i = 0;
    while (i < line.size() && line[i] == ' ') {
        i++;
    }
    idx = i;
    while (i < line.size() && line[i] != ' ' && line[i] != ',') {
        i++;
    }
    guarantor = line.substr(idx, i);
    while (i < line.size() && line[i] == ' ' || line[i] == ',') {
        i++;
    }
    idx = i;
    while (i < line.size()) {
        if (line[i] == ' ' || line[i] == '|') {
            if (i - idx > 5)
                graph[guarantor].push_back(line.substr(idx, i - idx));
            idx = i + 1;
        }
        i++;
    }
    if (i - idx > 5) {
        graph[guarantor].push_back(line.substr(idx, i - idx));
    }
}

void printCircle(map<string, vector<string>> &graph, string node) {
    unordered_set<string> visited;
    cout << node;
    stack<string> nxt;
    for(auto n : graph[node])
        nxt.push(n);

    while (!nxt.empty()) {
        string n = nxt.top();
        nxt.pop();
        cout << "->" << n;
        for (auto nn : graph[n]) {
            if (nn == node)
                cout << endl;
            else {
                nxt.push(nn);
            }
        }
    }
}

int main() {
    ifstream inStream;
    string fileName = "danbao.csv";
    inStream.open(fileName, ios::in);
    if (inStream.is_open()) {
        cout << fileName << " open successfully" << endl;

        string line;
        int lineCount = 0;
        map<string, vector<string>> graph;
        while (getline(inStream, line)) {
            // cout << line << endl;
            if (lineCount > 0) {
                addToGraph(graph, line);
            }
            lineCount++;
        }

        checkGraph(graph);
    } else {
        cout << fileName << " cannot be opened" << endl;
    }


    return 0;
}
