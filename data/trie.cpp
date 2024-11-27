#include <iostream>
#include <vector>

using namespace std;

struct Trie {
    char val;
    vector<Trie *> next;
    bool isWord = false;
    Trie(char c) : val(c) {
        next.resize(26, nullptr);
    }
};

Trie *build(vector<string> &words) {
    Trie *root = new Trie(':');
    for (string &s : words) {
        Trie *node = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!node->next[idx])
                node->next[idx] = new Trie(c);
            node = node->next[idx];
        }
        node->isWord = true;
    }
    return root;
}

void print(Trie *root, string &curr) {
    if (!root)
        return;
    curr += root->val;
    if (root->isWord)
        cout << curr << "\n";
    for (Trie *next : root->next)
        print(next, curr);
    curr.pop_back();
}
