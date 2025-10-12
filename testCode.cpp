#include <queue> 
#include <string>
#include <vector>
#include <iostream>

using namespace std;



class TrieNode {
private:
    // R links to node children
    TrieNode* links[26];
    bool isEnd;
    int count;

public:
    TrieNode() {
        // Initialize all links to null
        for (int i = 0; i < 26; i++) {
            links[i] = nullptr;
        }
        isEnd = false;
    }

    bool containsKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    TrieNode* get(char ch) {
        return links[ch - 'a'];
    }

    void put(char ch, TrieNode* node) {
        links[ch - 'a'] = node;
    }

    void setEnd() {
        isEnd = true;
    }

    bool isEndOfWord() {
        return isEnd;
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(const std::string& word) {
        TrieNode* node = root;
        for (int i = 0; i < word.length(); i++) {
            char currentChar = word[i];
            if (!node->containsKey(currentChar)) {
                node->put(currentChar, new TrieNode());
            }
            node = node->get(currentChar);
            node->count++;
        }
        node->setEnd();
    }

    // Search a prefix or whole key in trie and
    // returns the node where search ends
    TrieNode* searchPrefix(const std::string& word) {
        TrieNode* node = root;
        for (int i = 0; i < word.length(); i++) {
            char curLetter = word[i];
            if (node->containsKey(curLetter)) {
                node = node->get(curLetter);
            } else {
                return nullptr;
            }
        }
        return node;
    }

    int countPrefix(const string& word)
    {
        Node* curr = root;
            for (char c : pref) {
                if (curr->links[c - 'a'] == nullptr) {
                    return 0;  // Prefix not found
                }
                curr = curr->links[c - 'a'];
            }
            return curr->count;  // Return count at last node

    }
    // Returns if the word is in the trie.
    bool search(const std::string& word) {
        TrieNode* node = searchPrefix(word);
        return node != nullptr && node->isEndOfWord();
    }

    // Destructor to free memory (optional, but good practice)
    ~Trie() {
        delete root; // Note: You may want to implement a proper delete method for complete cleanup
    }
};

int main()
{

    vector<string> myWords {"wall", "wallpaper", "pencil", "pen", "book"};
    //vector<Trie*> myTrie;
    //Trie myTrie;
    for (auto& word : myWords)
    {
        // Trie* trie = new Trie();    
        // trie->insert(word);
        // myTrie.push_back(trie);

        //myTrie->insert(word);

    }
    for (int ii = 0; ii < myWords.size(); ++ii)
    {
        //cout << 
        // for (int jj = 0; jj < myTrie.size(); ++jj)
        // {
        //     if (ii != jj && (*myTrie[jj]).countPrefix(myWords[ii]) != nullptr)
        //     {
        //         cout << myWords[ii] <<" is a prefix in " << myWords[jj] << endl;
        //     }
        // }
        for (int jj = 0; jj < myWords.size(); ++jj)
        {
            if (ii != jj && myWords[jj].find(myWords[ii]) != string::npos)
            {
                 cout << myWords[ii] <<" is a prefix in " << myWords[jj] << endl;
            }
        }
    }    
    return 0;
}