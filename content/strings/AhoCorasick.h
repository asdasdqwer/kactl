/**
 * Author: Efe Demirler
 * License: MIT
 * Description: Aho-Corasick automaton for multiple pattern matching.
 * Initialize with Corasick ac(patterns); root is node 0. After construction,
 * vec[v].go[c] is the full automaton transition (never -1), vec[v].link is the
 * suffix link (longest proper suffix of v's string that is also a trie node),
 * and vec[v].labels lists the patterns ending exactly at v (duplicates allowed;
 * empty patterns are not). A pattern also matches at state v if it ends at any
 * node on v's suffix-link chain. Suffix links form a tree rooted at 0; order holds
 * non-root nodes in BFS order (increasing depth), so iterating it backwards
 * processes every node before its link (e.g. cnt[link[v]] += cnt[v] gives the
 * number of occurrences of each node's string in the text). For DP over the
 * automaton, states are node indices and transitions are go[][]; mark a node bad
 * if it or any node on its link chain has labels (propagate in BFS order).
 * Time: construction O(26N), N = sum of pattern lengths; walking a text O(|text|).
 * Status: stress-tested
 */
#pragma once
const int ALPH = 26;
const char BEGA = 'a';
struct Corasick {
struct Node {
    vector<int> labels;
    int link = -1;
    int go[ALPH];
    Node() { fill(begin(go), end(go), -1);}
};
    vector<Node> vec; 
    vector<int> order; // BFS order (root excluded) 
    void insert(const string& s, int label) {
        int ind = 0;
        for(auto& c : s) {
           if(vec[ind].go[c - BEGA] == -1) {
                vec.push_back(Node());
                vec[ind].go[c - BEGA] = vec.size() - 1;
           } 
           ind = vec[ind].go[c - BEGA];
        }
        vec[ind].labels.push_back(label);
    }
    Corasick(const vector<string>& pat) {
        vec.push_back(Node());
        for(int i = 0; i < (int)pat.size(); i++) {
            insert(pat[i], i);
        }
        vec[0].link = 0;
        queue<int> que;
        for(int i = 0; i < ALPH; i++) {
            if(vec[0].go[i] == -1) vec[0].go[i] = 0;
            else {
                que.push(vec[0].go[i]);
                vec[ vec[0].go[i] ].link = 0;
            }
        }
        while(!que.empty()) {
            auto cur = que.front();
            order.push_back(cur);
            que.pop();
            for(int c = 0; c < ALPH; c++) {
                if(vec[cur].go[c] == -1) {
                    vec[cur].go[c] = vec[ vec[cur].link ].go[c];
                }
                else {
                    que.push(vec[cur].go[c]);
                    vec[ vec[cur].go[c] ].link = vec[ vec[cur].link ].go[c];
                }
            }
        }
    }
};