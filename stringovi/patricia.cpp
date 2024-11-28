#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node
{
public:
    string keypart;
    bool isendofword;
    vector<Node *> children;

    Node(const string &part = "")
        : keypart(part), isendofword(false), children(26, nullptr) {}
};

class PatriciaTrie
{
    Node *root;

    void deleteall(Node *n)
    {
        for (Node *child : n->children)
        {
            if (child)
            {
                deleteall(child);
            }
        }
        delete n;
    }

public:
    PatriciaTrie()
    {
        root = new Node();
    }

    ~PatriciaTrie()
    {
        deleteall(root);
    }

    void insert(const string &word)
    {
        Node *curr = root;
        string remaining = word;

        while (!remaining.empty())
        {
            char firstchar = remaining[0];
            int index = firstchar - 'a'; // Convert 'a' to 'z' to 0 to 25

            if (curr->children[index] == nullptr)
            {
                curr->children[index] = new Node(remaining);
                curr->children[index]->isendofword = true;
                return;
            }

            Node *child = curr->children[index];
            string &childkey = child->keypart;

            int length = 0;
            while (length < childkey.size() &&
                   length < remaining.size() &&
                   childkey[length] == remaining[length])
            {
                length++;
            }

            if (length == childkey.size())
            {
                remaining = remaining.substr(length);
                curr = child;
            }
            else
            {
                Node *splitnode = new Node(childkey.substr(0, length));
                curr->children[index] = splitnode;

                child->keypart = childkey.substr(length);
                splitnode->children[child->keypart[0] - 'a'] = child;

                if (remaining.size() > length)
                {
                    Node *newchild = new Node(remaining.substr(length));
                    newchild->isendofword = true;
                    splitnode->children[newchild->keypart[0] - 'a'] = newchild;
                }
                else
                {
                    splitnode->isendofword = true;
                }

                return;
            }
        }

        curr->isendofword = true;
    }

    bool search(const string &word)
    {
        Node *curr = root;
        string remaining = word;

        while (!remaining.empty())
        {
            char firstchar = remaining[0];
            int index = firstchar - 'a';

            if (curr->children[index] == nullptr)
            {
                return false;
            }

            Node *child = curr->children[index];
            string &childkey = child->keypart;

            if (remaining.substr(0, childkey.size()) == childkey)
            {
                remaining = remaining.substr(childkey.size());
                curr = child;
            }
            else
            {
                return false;
            }
        }

        return curr->isendofword;
    }
};

int main()
{
    PatriciaTrie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("ape");

    cout << "Search 'app': " << trie.search("app") << endl;
    cout << "Search 'apple': " << trie.search("apple") << endl;
    cout << "Search 'ape': " << trie.search("ape") << endl;
    cout << "Search 'ap': " << trie.search("ap") << endl;

    return 0;
}