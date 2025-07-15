#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    int data;
    node *left, *right;

    node(int val)
    {
        data = val;
        left = right = NULL;
    }
};

class BST
{
public:
    node *root;
    BST()
    {
        root = NULL;
    }

    node *INSERT(node *r, int value)
    {
        if (r == NULL)
        {
            node *new_node = new node(value);
            r = new_node;
        }
        else if (value < r->data)
        {
            r->left = INSERT(r->left, value);
        }
        else
        {

            r->right = INSERT(r->right, value);
        }
        return r;
    }
    void insert(int value)
    {
        root = INSERT(root, value);
    }

    void preOrder(node *n) // root left right
    {
        if (n == NULL)
        {
            return;
        }
        cout << n->data << " ";
        preOrder(n->left);
        preOrder(n->right);
    }
    void inOrder(node *n) // left root right
    {
        if (n == NULL)
        {
            return;
        }
        inOrder(n->left);
        cout << n->data << " ";
        inOrder(n->right);
    }
    void postOrder(node *n) // left right root
    {
        if (n == NULL)
        {
            return;
        }

        postOrder(n->left);
        postOrder(n->right);
        cout << n->data << " ";
    }
    node *search(node *r, int key)
    {
        if (r == NULL)
        {
            return NULL;
        }
        else if (r->data == key)
        {

            return r;
        }
        else if (key < r->data)
        {
            return search(r->left, key);
        }
        else
        {
            return search(r->right, key);
        }
        return r;
    }
    bool Search(int key)
    {

        root = search(root, key);
        node *ans = root;
        if (ans != NULL)
        {
            return true;
        }
        return false;
    }
    node *minn(node *r)
    {
        if (r == NULL)
        {
            return NULL;
        }
        else if (r->left == NULL)
        {
            return r;
        }
        else
        {
            return minn(r->left);
        }
    }

    node *maxx(node *r)
    {
        if (r == NULL)
        {
            return NULL;
        }
        else if (r->right == NULL)
        {
            return r;
        }
        else
        {
            return maxx(r->right);
        }
    }
    node *Delete(node *r, int key)
    {
        if (r == NULL)
        {
            return NULL;
        }
        if (Search(key))
        {
            if (key < r->data)
            {
                r->left = Delete(r->left, key);
            }
            else if (key > r->data)
            {
                r->right = Delete(r->right, key);
            }
            else
            {
                if (r->left == NULL && r->right == NULL)
                {
                    r = NULL;
                }
                else if (r->left != NULL && r->right == NULL)
                {
                    r->data = r->left->data;
                    delete r->left;
                    r->left = NULL;
                }
                else if (r->left == NULL && r->right != NULL)
                {
                    r->data = r->right->data;
                    delete r->right;
                    r->right = NULL;
                }
                else if (r->left != NULL && r->right != NULL)
                {
                    r->data = minn(r->right)->data;
                    r->right = Delete(r->right, minn(r->right)->data);
                }
            }
            
        }
        return r;
    }
};

int main()
{
    BST tree;
    tree.insert(30);
    tree.insert(50);
    tree.insert(60);
    tree.insert(70);
    tree.insert(40);
    tree.insert(10);
    // tree.inOrder(tree.root);
    // cout<<endl;
    // if (tree.Search(10))
    // {
    //     cout << "existed\n";
    // }
    // else
    // {
    //     cout << "not existed\n";
    // }
    // node *ans = tree.minn(tree.root);
    // cout << ans->data << "\n";

    // node *ans2 = tree.maxx(tree.root);
    // cout << ans2->data << "\n";

    node *res = tree.Delete(tree.root, 40);
    tree.inOrder(res);
}
