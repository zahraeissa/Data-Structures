#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {};
};
class BST
{

public:
    Node *root = nullptr;
    BST(int value)
    {
        root = new Node(value);
    }
    ~BST()
    {
        clear_whole_tree(root);
        // delete root; ==> This line is not needed as clear_whole_tree already deletes all nodes
    }
    void clear_whole_tree(Node *node)
    {
        if (!node)
            return;

        clear_whole_tree(node->left);
        clear_whole_tree(node->right);
        delete node;
        node = nullptr;
    }

    void add(int value, Node *node)
    {
        if (value < node->data)
        {
            if (!node->left)
            {
                node->left = new Node(value);
            }
            else if (node->left)
            {
                add(value, node->left);
            }
        }
        if (value > node->data)
        {
            if (!node->right)
            {
                node->right = new Node(value);
            }
            else if (node->right)
            {
                add(value, node->right);
            }
        }
    }
    bool search(int value, Node *root)
    {
        if (root->data == value)
            return true;

        else if (value < root->data)
        {
            return root->left && search(value, root->left);
        }

        else if (value > root->data)
        {
            return root->right && search(value, root->right);
        }
        return false;
    }
    bool search_iterative(int value, Node *node)
    {
        Node *cur = node;

        if (value == cur->data)
            return true;

        else if (value < cur->data)
        {
            while (cur->left)
            {
                if (cur->left->data == value)
                    return true;
                else
                    cur = cur->left;
            }
        }

        else if (value > cur->data)
        {
            while (cur->right)
            {
                if (cur->right->data == value)
                    return true;
                else
                    cur = cur->right;
            }
        }
        return false;
    }
    bool is_BST(Node *node)
    {

        if (node->left)
        {
            if (node->left->data < node->data)
                return is_BST(node->left);
            else
                return false;
        }

        if (node->right)
        {
            if (node->right->data > node->data)
                return is_BST(node->right);
            else
                return false;
        }

        return true;
    }
    // implement 2 cases of getting successor
    //  case 1 if node has right subtree so the successor of this node is the min of its right subtree
    //  case 2 if node doesnot have right subtreee so we keep going up to find the first node that greater than current node and it is the successor
    bool find_chain(Node *root, int value, vector<Node *> &ancestors)
    {

        ancestors.push_back(root);
        if (value == root->data)
        {

            return true;
        }
        else if (value < root->data)
        {

            return root->left && find_chain(root->left, value, ancestors);
        }
        else
        {

            return root->right && find_chain(root->right, value, ancestors);
        }
        return false;
    }
    int min_value(Node *node)
    {
        // if (!node->left && !node->right)
        //     return INT_MAX;

        // return min(min_value(node->left),min_value(node->right));

        if (!node->left)
            return node->data;

        return min_value(node->left);
    }

    Node *get_next(vector<Node *> &ancestors)
    {
        if (ancestors.size() == 0)
            return nullptr;
        Node *temp = ancestors.back();
        ancestors.pop_back();
        return temp;
    }

    pair<bool, signed int> get_successor(Node *node, int value)
    {
        vector<Node *> ancestors;

        if (!find_chain(node, value, ancestors))
            return make_pair(false, -1);

        Node *child = get_next(ancestors); // this is the value that i want to get its successor

        // first case if there is right
        if (child->right)
        {
            return make_pair(true, min_value(child->right));
        }

        // 2nd case there is no right
        Node *parent = get_next(ancestors);

        while (parent && parent->right == child)
        {
            child = parent;
            parent = get_next(ancestors);
        }

        if (parent)
        {
            return make_pair(true, parent->data);
        }
        return make_pair(false, -1);
    }
    vector<int> inorder_traversal(Node *node, vector<int> &in)
    {

        if (!node)
        {
            return in;
        }

        inorder_traversal(node->left, in);
        in.push_back(node->data);
        inorder_traversal(node->right, in);

        return in;
    }
    void find_successor(Node *root, deque<int> &ancestors)
    {
        vector<int> inorder;
        while (!ancestors.empty())
        {
            int target = ancestors.front();
            ancestors.pop_front();

            for (int i = 0; i < inorder_traversal(root, inorder).size(); i++)
            {

                if ((inorder_traversal(root, inorder))[i] == target)
                {
                    cout << (inorder_traversal(root, inorder))[i + 1] << " ";
                    break;
                }
            }
        }
    }
    bool is_degenerated(vector<int> &preorder)
    {
        int mn = 0;
        int mx = 1000;

        for (int i = 0; i < preorder.size() - 1; i++)
        {
            if (preorder[i] < mn || preorder[i] > mx)
                return false;

            if (preorder[i + 1] < preorder[i])
            {
                mx = preorder[i + 1] - 1;
            }
            else if (preorder[i + 1] > preorder[i])
            {
                mn = preorder[i] + 1;
            }
        }
        return true;
    }
    Node *min_node(Node *node)
    {
        if (!node->left)
            return node;
        min_node(node->left);
    }

    Node *delete_node(int target, Node *node) // delete function here is updating tree,left and right subtrees in each return so its return is a subtree that is updated
    {
        Node *temp;

        if (!node->left && !node->right)
            return nullptr;
        else if (target < node->data)
            node->left = delete_node(target, node->left);

        else if (target > node->data)
            node->right = delete_node(target, node->right);

        else if (target == node->data) // 3 cases ==> leaf node or has one child(L or R) or has left and right.
        {
            temp = node;

            if (!node->left && !node->right) // leaf node
                node = nullptr;

            else if (!node->left) // it has only right
                node = node->right;

            else if (!node->right) // it has only left
                node = node->left;

            else // it has left and right
            {
                Node *successor = min_node(node->right);
                node->data = successor->data;
                node->right = delete_node(successor->data, node->right); // update right subtree and return it after deleting the target node
                temp = nullptr;
            }
        }
        if (temp)
            delete temp;

        return node;
    }
    Node *max_node(Node *node)
    {
        if (!node->right)
            return node;
        max_node(node->right);
    }

    Node *delete_node_using_predeccessor(int target, Node *node) // delet function here is updating tree,left and right subtrees in each return so its return is a subtree that is updated
    {
        Node *temp;

        if (!node->left && !node->right)
            return nullptr;

        else if (target < node->data)
            node->left = delete_node(target, node->left);

        else if (target > node->data)
            node->right = delete_node(target, node->right);

        else if (target == node->data) // 3 cases ==> leaf node or has one child(L or R) or has left and right.
        {
            temp = node;

            if (!node->left && !node->right) // leaf node
                node = nullptr;

            else if (!node->left) // it has only right
                node = node->right;

            else if (!node->right) // it has only left
                node = node->left;

            else // it has left and right
            {
                Node *predeccessor = max_node(node->left);
                node->data = predeccessor->data;
                node->left = delete_node(predeccessor->data, node->left); // update left subtree and return it after deleting the target node
                temp = nullptr;
            }
        }
        if (temp)
            delete temp;

        return node;
    }
    Node *search2(int value, Node *node)
    {

        if (node->data == value) // root
            return node;

        else if (value < node->data)
        {

            if (node->left)
                search(value, node->left);
        }

        else if (value > node->data)
        {
            if (node->right)
                search(value, node->right);
        }
        return nullptr;
    }
    void delete_without_recursion(int target, Node *node)
    {

        Node *found = search2(target, node);
        if (found == nullptr)
            return;

        if (!found->left && !found->right)
        {
            found = nullptr;
            delete found;
            return;
        }

        if (found->left && !found->right)
        {
            Node *temp = found;
            found->data = found->left->data;
            found->left = nullptr;
            delete found->left;
        }

        else if (found->right && !found->left)
        {
            Node *temp = found;
            found->data = found->right->data;
            found->right = nullptr;
            delete found->right;
        }

        else if (found->right && found->left)
        {
            Node *succ = min_node(found->right);
            found->data = succ->data;
            succ = nullptr;
            delete succ;
        }
    }
};

int main()
{
    BST tree(50);
    // Node *ll=new Node(90);
    // tree.root->left=ll;
    tree.add(90, tree.root);
    tree.add(15, tree.root);
    tree.add(35, tree.root);
    tree.add(45, tree.root);
    tree.add(70, tree.root);
    tree.add(60, tree.root);
    tree.add(73, tree.root);

    // cout<< tree.search(73,tree.root);
    // cout<< tree.search_iterative(3,tree.root);
    // cout << tree.is_BST(tree.root);

    // pair<bool, int> res = tree.get_successor(tree.root, 90);
    // cout << res.first << " " << res.second;

    // tree.inorder_traversal(tree.root, v);
    // cout << v[0] << v[1] << v[2];

    deque<int> dq = {15, 70, 73};

    tree.find_successor(tree.root, dq);

    cout
        << "\nNO RTE \n";
}