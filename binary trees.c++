#include <bits/stdc++.h>
using namespace std;

// template <typename T>
struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {};
};

class binary_tree
{
private:
    int data;
    binary_tree *left;
    binary_tree *right;
   
    public:
    Node *root{};
    binary_tree(int value)
    {
        root = new Node(value);
    };
    ~binary_tree()
    {
        
        clear_whole_tree(root);
        delete root;
    }

    void add(vector<int> values, vector<char> directions)
    {
        Node *current = root;
        for (int i = 0; i < values.size(); i++)
        {
            if (directions[i] == 'L')
            {
                if (!current->left)
                    current->left = new Node(values[i]);

                else
                    assert(current->left->data == values[i]);
                current = current->left;
            }

            else if (directions[i] == 'R')
            {
                if (!current->right)
                    current->right = new Node(values[i]);

                else
                    assert(current->right->data == values[i]);
                current = current->right;
            }
        }
    }
    int tree_max(Node *node)
    {

        if (!node)
            return INT_MIN;

        return max(node->data, max(tree_max(node->left), tree_max(node->right)));
    }

    int tree_height(Node *node)
    {
        if (!node)
            return -1;

        return 1 + max(tree_height(node->left), tree_height(node->right));
    }

    int total_nodes(Node *node)
    {
        int res = 1;
        if (!node)
            return 0;

        return res += total_nodes(node->left) + total_nodes(node->right);
    }
    int leaves(Node *node)
    {
        int res = 0;
        if (!node)
            return 0;

        if (!node->left && !node->right)
            return res += 1;
        if (node->left && node->right)
            return leaves(node->left) + leaves(node->right);

        return res;
    }
    bool is_existed(Node *node, int value)
    {

        if (!node)
            return false;

        if (node->data == value)
            return true;

        return is_existed(node->left, value) || is_existed(node->right, value);
    }

    // bool is_perfect_tree(Node *node)
    // {
    //     int levels = tree_height(node) + 1;
    //     int nodes = total_nodes(node);
    //     if ((pow(2, levels)) - 1 == nodes)
    //         return true;
    //     return false;
    // }

    bool is_perfect_tree(Node *node)
    {
        int levels = tree_height(node) + 1;
        int nodes = total_nodes(node);

        if (!node)
            return 0;

        if ((pow(2, levels)) - 1 == nodes)
            return true;

        return is_perfect_tree(node->left) || is_perfect_tree(node->right);
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

    // vector<int> inorder_traversal(Node *cur)
    // {
    //     vector<int> result;
    //     stack<Node *> st;
    //     while (true)
    //     {
    //         if (cur)
    //         {
    //             st.push(cur);
    //             cur = cur->left;
    //         }
    //         else
    //         {
    //             if (st.empty())
    //                 break;
    //             cur = st.top();
    //             st.pop();
    //             result.push_back(cur->data);
    //             cur = cur->right;
    //         }
    //     }
    //     return result;
    // }
    
    void left_boundry(Node *node)
    {
        cout << node->data << " ";

        if (!node)
            return;

        if (node->left)
            left_boundry(node->left);

        else if (node->right)
            left_boundry(node->right);
    }
    int BT_diameter(Node *node)
    {

        if (!node)
            return 0;

        int Diameter = tree_height(node->left) + tree_height(node->right) + 2;
        return max(Diameter, max(BT_diameter(node->left), BT_diameter(node->right)));
    }

    bool is_operator(char c)
    {
        if (c == '+' || c == '-' || c == '*' || c == '/')
            return true;
        return false;
    }

    // struct Node
    // {
    //     char data;
    //     Node *left;
    //     Node *right;

    //     Node(char value) : data(value), left(nullptr), right(nullptr) {};
    // };

    // void build(string postfix) // constructor builds tree from postfix notation
    // {
    //     stack<Node *> st;

    //     for (int i = 0; i < postfix.size(); i++)
    //     {
    //         Node *cur = new Node(postfix[i]);
    //         if (!is_operator(postfix[i]))
    //         {
    //             st.push(cur);
    //         }
    //         else
    //         {
    //             cur->left = st.top();
    //             st.pop();
    //             cur->right = st.top();
    //             st.pop();
    //             st.push(cur);
    //         }
    //         Node *root = st.top();
    //         // root->data = this->data;
    //         // root->left = this->left;
    //         // root->right = this->right;
    //     }
    // }
    // void print_post_order(Node *node)
    // {
    //     if (!node)
    //         return;

    //     print_post_order(node->left);
    //     print_post_order(node->right);
    //     cout << node->data << " ";
    // }

    void level_traversal(Node *node) // breadth first algorithm : visit tree level by level
    {
        queue<Node *> q;
        q.push(node);

        while (!q.empty())
        {
            Node *cur = q.front();
            cout << cur->data << " ";
            q.pop();

            if (cur->left)
                q.push(cur->left);

            if (cur->right)
                q.push(cur->right);
        }
    }

    // void recursive_level_traversal(Node *node)
    // {
    //     if (!node)
    //         return;

    //     if (node->left && node->right)
    //     {
    //         if (tree_height(node->left) == tree_height(node->right))
    //         {
    //             cout << node->left->data << " " << node->right->data << " ";
    //             recursive_level_traversal(node->left, node->right);
    //         }
    //     }
    //     if()

    //     if (!node)
    //         return;
    // }

    binary_tree(deque<int> &pre, deque<int> &in, int start = 0, int end = -1)
    {
        if (end == -1)
            end = in.size() - 1;

        int root = pre[0];
        pre.pop_front();

        for (int i = start; i < in.size(); i++)
        {
            if (in[i] == root)
            {
                if (start < i)
                    left = new binary_tree(pre, in, start, i - 1);
                if (end > i)
                    right = new binary_tree(pre, in, i + 1, end);
                break;
            }
        }
    }

    Node *tree_from_inorder_preorder(deque<int> &pre, deque<int> &in, int s = 0, int end = -1)
    {
        //pre: 1 2 4 7 8 5 9 3 6 10
        //in:  7 4 8 2 5 9 1 3 10 6

        if (end == -1)
            end = in.size() - 1;

        if (s > end)
            return nullptr;

        Node *root = new Node(pre[0]);
        pre.pop_front();

        for (int i = 0; i < in.size(); i++)
        {
            if (in[i] == root->data)
            {
                if (s < i)
                    root->left = tree_from_inorder_preorder(pre, in, s, i - 1);
                if (end > i)
                    root->right = tree_from_inorder_preorder(pre, in, i + 1, end);
                break;
            }
        }
        return root;
    }
    binary_tree(deque<pair<int, int>> &preorder)
    {
        pair<int, int> data = preorder[0];
        cout << data.first << " ";
        preorder.pop_front();

        if (data.second == 0)
        {
            left = new binary_tree(preorder);
            right = new binary_tree(preorder);
        }
    }
    void print_preorder_BT(Node *node) // you can generate BT from only one preorder notation in this way
    {

        // ex: 1 2 -1 -1 3 -1 -1
        if (!node)
            return;
        cout << node->data << " ";
        if (node->left)
            print_preorder_BT(node->left);
        else
            cout << -1 << " ";
        if (node->right)
            print_preorder_BT(node->right);
        else
            cout << -1 << " ";
    }
    void print_serialized_form(Node *node) // based on preorder traversing
    {
        cout << '(';
        if (!node)
        {
            cout << ')';
            return;
        }

        cout << node->data;

        if (node->left)
        {
            cout << '(';
            print_serialized_form(node->left);
        }
        else
            cout << "()";

        if (node->right)
        {

            print_serialized_form(node->right);
            cout << ')';
        }
        else
            cout << "()";

        cout << ')';
    }
    bool is_mirror(Node *first, Node *second) // tree is symmetric when it is mirror
    {
        if (!first && !second) // base case
            return true;

        if (first->data == second->data)
            return is_mirror(first->left, second->right) && is_mirror(first->right, second->left);

        return false;
    }
    bool is_symmetric(Node *node) // main root
    {
        return is_mirror(node->left, node->right);
    }
    string parenthesize(Node *node, bool f = true) // including remirroring
    {
        string repr = "(";
        repr += to_string(node->data);

        if (f)
        {
            if (node->left)
            {
                // repr += "(";
                parenthesize(node->left, true);
            }
            else
                repr += "()";

            if (node->right)
            {
                parenthesize(node->right, true);
                // repr += "(";
            }
            else
                repr += "()";
        }
        else // re-mirroring
        {
            if (node->right)
            {
                parenthesize(node->right, false);
                // repr += ")";
            }
            else
                repr += "()";

            if (node->left)
            {
                // repr += "(";
                parenthesize(node->left, false);
            }
            else
                repr += "()";
        }

        repr += ")";
        return repr;
    }
    bool is_symmetric_2(Node *node)
    {
        if (!node->left && !node->right)
            return true;

        if ((!node->left && node->right) || (node->left && !node->right))
            return false;

        return parenthesize(node->left) == parenthesize(node->right, false);
    }

    string parenthesize_canonical(Node *root)
    {
        if (!root)
            return "()";

        string repr = "(" + to_string(root->data);

        vector<string> v;

        if (root->left)
            v.push_back(parenthesize_canonical(root->left));
        else
            v.push_back("()");

        if (root->right)
            v.push_back(parenthesize_canonical(root->right));
        else
            v.push_back("()");

        sort(v.begin(), v.end());
        for (int i = 0; i < (int)v.size(); ++i)
            repr += v[i];

        repr += ")";

        return repr;
    }
    string parenthesize_duplicates(Node *root, vector<string> &all_repr)
    {

        string repr = "(" + to_string(root->data);

        if (root->left)
            repr += parenthesize_duplicates(root->left, all_repr);
        else
            repr += "()";

        if (root->right)
            repr += parenthesize_duplicates(root->right, all_repr);
        else
            repr += "()";

        repr += ")";

        if (root->left || root->right)
            all_repr.push_back(repr);

        return repr;
    }
};

int main()
{

    cout << "\nno rte";

    return 0;
}