#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct node
{
    string ticker;
    double price;
    node *left, *right;

    node(string t, double p) : ticker(t), price(p), left(nullptr), right(nullptr) {}
};

class binary_tree
{
private:
    node *root;

    node *insertRecursively(node *root, string t, double p)
    {
        if (!root)
        {
            return new node(t, p);
        }
        if (t < root->ticker)
        {
            root->left = insertRecursively(root->left, t, p);
        }
        else if (t > root->ticker)
        {
            root->right = insertRecursively(root->right, t, p);
        }
        else
        {
            cout << "Ticker already exists" << endl;
        }
        return root;
    }

    node *searchRecursively(node *root, string s)
    {
        if (root == nullptr || root->ticker == s)
        {
            return root;
        }
        return (s < root->ticker) ? searchRecursively(root->left, s) : searchRecursively(root->right, s);
    }

    node *find_minRecursively(node *root)
    {
        if (root == nullptr || root->left == nullptr)
        {
            return root;
        }
        return find_minRecursively(root->left);
    }

    node *find_maxRecursively(node *root)
    {
        if (root == nullptr || root->right == nullptr)
        {
            return root;
        }
        return find_maxRecursively(root->right);
    }

    node *removeRecursively(node *root, string s)
    {
        if (root == nullptr)
        {
            return root;
        }
        if (s < root->ticker)
        {
            return removeRecursively(root->left, s);
        }
        else if (s > root->ticker)
        {
            return removeRecursively(root->right, s);
        }
        else
        {
            //  only one child or no child
            if (root->left == nullptr)
            {
                node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                node *temp = root->left;
                delete root;
                return temp;
            }
            // two children
            node *temp = find_minRecursively(root->right); // inorder successor
            root->ticker = temp->ticker;
            root->price = temp->price;
            root->right = removeRecursively(root->right, temp->ticker);
        }
        return root;
    }

    void inorderrecursive(node *Node)
    {
        if (Node != nullptr)
        {
            inorderrecursive(Node->left);
            cout << Node->ticker << " ";
            inorderrecursive(Node->right);
        }
    }

public:
    binary_tree() : root(nullptr) {}

    void insert(string t, double p)
    {
        root = insertRecursively(root, t, p);
    }

    double search(string s)
    {
        node *temp = searchRecursively(root, s);
        return (temp != nullptr) ? temp->price : -1.0;
    }

    string find_min()
    {
        node *temp = find_minRecursively(root);
        return (temp != nullptr) ? temp->ticker : "";
    }

    string find_max()
    {
        node *temp = find_maxRecursively(root);
        return (temp != nullptr) ? temp->ticker : "";
    }

    void remove(string s)
    {
        root = removeRecursively(root, s);
    }

    void inorder()
    {
        inorderrecursive(root);
        cout << endl;
    }

    void bfs()
    {
        if (root == nullptr)
        {
            return;
        }
        queue<node *> q;
        q.push(root);
        while (!q.empty())
        {
            node *curr = q.front();
            q.pop();
            cout << curr->ticker << " : " << curr->price << endl;
            if (curr->left != nullptr)
            {
                q.push(curr->left);
            }
            if (curr->right != nullptr)
            {
                q.push(curr->right);
            }
        }
    }
};

int main()
{
    binary_tree tree;

    // Insert some tickers
    tree.insert("AAPL", 175.00);
    tree.insert("MSFT", 330.00);
    tree.insert("GOOG", 2800.00);
    tree.insert("AMZN", 150.00);
    tree.insert("TSLA", 250.00);
    tree.insert("FB", 200.00);

    // Inorder traversal (alphabetical order)
    cout << "Inorder Traversal: ";
    tree.inorder();

    // Level order traversal
    cout << "Level Order Traversal: ";
    tree.bfs();

    // Search for a ticker
    cout << "Price of AAPL: " << tree.search("AAPL") << endl;
    cout << "Price of XYZ: " << tree.search("XYZ") << endl;

    // Find min and max
    cout << "Min Ticker: " << tree.find_min() << endl;
    cout << "Max Ticker: " << tree.find_max() << endl;

    // Remove a ticker
    tree.remove("MSFT");

    // Inorder traversal after removal
    cout << "Inorder Traversal after removing MSFT: ";
    tree.inorder();

    cout << "Level order traversal after removing MSFT:" << endl;
    tree.bfs();

    return 0;
}
