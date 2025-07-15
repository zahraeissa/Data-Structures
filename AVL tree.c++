#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data{};
    int height{};
    Node *left{};
    Node *right{};

    Node(int val) :
        data(val), height(0), left(nullptr), right(nullptr) {};
};

class AVL_Tree {
    // private:
    //     Node *root = nullptr;

public:
    Node *root;
    AVL_Tree(int value) { root = new Node(value); }
    ~AVL_Tree() { clear_whole_tree(root); }
    void clear_whole_tree(Node *node) {
        if (!node)
            return;

        clear_whole_tree(node->left);
        clear_whole_tree(node->right);
        delete node;
        node = nullptr;
    }
    int height(Node *node) {
        if (!node)
            return -1;
        return node->height;
    }
    void update_height(Node *node) { node->height = 1 + max(height(node->left), height(node->right)); }
    int balance_factor(Node *node) { return height(node->left) - height(node->right); }
    // Rotations codes

    Node *right_rotation(Node *node) {
        Node *SubLeft = node->left;  // p=q->left
        node->left = SubLeft->right;  // q->left=p->right
        SubLeft->right = node;  // p->right=q

        update_height(node);
        update_height(SubLeft);

        return SubLeft;  // new root
    }

    Node *left_rotation(Node *node) {
        Node *SubRight = node->right;
        node->right = SubRight->left;
        SubRight->left = node;

        update_height(node);
        update_height(SubRight);

        return SubRight;
    }
    Node *balancing(Node *node) {
        if (balance_factor(node) == -2) {
            if (balance_factor(node->right) == 1)
                node->right = right_rotation(node->right);  // relinking because it is restructuring
            node = left_rotation(node);
        } else if (balance_factor(node) == 2) {
            if (balance_factor(node->left) == -1)
                node->left = left_rotation(node->left);
            node = right_rotation(node);
        }
        return node;
    }
    Node *insert(int value, Node *node)  // log(n) bec of the height = log(n)
    {
        if (value < node->data) {
            if (!node->left) {
                node->left = new Node(value);
            } else
                node->left = insert(value, node->left);  // relinking bec of restructuring

        } else {
            if (!node->right) {
                node->right = new Node(value);
            } else
                node->right = insert(value, node->right);
        }

        update_height(node);
        return balancing(node);
    }

    void insertion(int value) {
        if (!root)
            Node *root = new Node(value);

        root = insert(value, root);
    }
    Node *min_node(Node *node) {
        if (!node->left)
            return node;

        min_node(node->left);
    }
    Node *delete_node(int value, Node *node) {
        if (!node)
            return nullptr;

        if (value < node->data) {
            node->left = delete_node(value, node->left);

        } else if (value > node->data) {
            node->right = delete_node(value, node->right);
        } else {
            Node *temp = node;

            if (!node->left && !node->right)
                node = nullptr;

            else if (!node->left) {
                node = node->right;
            } else if (!node->right) {
                node = node->left;
            } else {
                Node *successor = min_node(node->right);
                node->data = successor->data;
                node->right = delete_node(successor->data, node->right);
                temp = nullptr;
            }
            if (temp)
                delete temp;
        }

        if (node) {
            update_height(node);
            node = balancing(node);
        }
        return node;
    }
    void deletion(int value) {
        if (!root)
            return;
        root = delete_node(value, root);
    }

    Node *lower_bound(int value, Node *node) {
        // Node *temp = node;
        if (!node)
            return nullptr;

        else if (value <= node->data) {
            Node *ans = lower_bound(value, node->left);

            if (ans)
                return ans;

            else
                return node;

        } else {
            return lower_bound(value, node->right);
        }
    }
    pair<bool, int> get_lowerBound(int value, Node *node)  // log n operation
    {
        if (!root) {
            return make_pair(false, -1);
        }
        Node *ans = lower_bound(value, node);

        if (ans)
            return make_pair(true, value);

        return make_pair(false, -1);
    }

    Node *upper_bound(int value, Node *node) {
        if (!node) {
            return nullptr;
        }

        if (value < node->data) {
            Node *ans = upper_bound(value, node->left);
            if (ans) {
                return ans;
            }
            return node;
        }
        return upper_bound(value, node->right);
    }
    pair<bool, int> get_upperBound(int value, Node *node) {
        if (!root)
            return make_pair(false, -1);

        Node *ans = upper_bound(value, node);

        if (ans) {
            return make_pair(true, value);
        }
        return make_pair(false, -1);
    }
    int count_inversions(vector<int> &vec) {
        int sum = 0;

        for (int i = 0; i < vec.size(); i++) {
            insertion(vec[i]);
            sum += get_upperBound(vec[i], root).second;
        }
        return sum;
    }
};
/////////////////////////////// priority queue based on avl tree/////////////////////////

struct PQNode {
    vector<int> id{};
    int key{};
    int height{};
    PQNode *left{};
    PQNode *right{};

    PQNode(int value, int prio) :
        key(prio), height(0), left(nullptr), right(nullptr) {
        id.push_back(value);
    };
};


class PQ {
    // private:
    //     PQNode *root = nullptr;

public:
    PQNode *root;
    PQ(int val, int prio) {
        root = new PQNode(val, prio);
    }
    ~PQ() {
        clear_whole_tree(root);
    }
    void clear_whole_tree(PQNode *node) {
        if (!node)
            return;

        clear_whole_tree(node->left);
        clear_whole_tree(node->right);
        delete node;
        node = nullptr;
    }
    int height(PQNode *node) {
        if (!node)
            return -1;
        return node->height;
    }
    void update_height(PQNode *node) { node->height = 1 + max(height(node->left), height(node->right)); }
    int balance_factor(PQNode *node) { return height(node->left) - height(node->right); }
    // Rotations codes

    PQNode *right_rotation(PQNode *node) {
        PQNode *SubLeft = node->left;  // p=q->left
        node->left = SubLeft->right;  // q->left=p->right
        SubLeft->right = node;  // p->right=q

        update_height(node);
        update_height(SubLeft);

        return SubLeft;  // new root
    }

    PQNode *left_rotation(PQNode *node) {
        PQNode *SubRight = node->right;
        node->right = SubRight->left;
        SubRight->left = node;

        update_height(node);
        update_height(SubRight);

        return SubRight;
    }
    PQNode *balancing(PQNode *node) {
        if (balance_factor(node) == -2) {
            if (balance_factor(node->right) == 1)
                node->right = right_rotation(node->right);  // relinking because it is restructuring
            node = left_rotation(node);
        } else if (balance_factor(node) == 2) {
            if (balance_factor(node->left) == -1)
                node->left = left_rotation(node->left);
            node = right_rotation(node);
        }
        return node;
    }
    PQNode *insert(int id, int prio, PQNode *node)  // log(n) bec of the height = log(n)
    {
        if (prio < node->key) {
            if (!node->left) {
                node->left = new PQNode(id, prio);
            } else
                node->left = insert(id, prio, node->left);  // relinking bec of restructuring

        } else if (prio > node->key) {
            if (!node->right) {
                node->right = new PQNode(id, prio);
            } else
                node->right = insert(id, prio, node->right);
        } else
            node->id.push_back(id);

        update_height(node);
        return balancing(node);
    }

    void insertion(int id_task, int priority) {
        if (!root)
            PQNode *root = new PQNode(id_task, priority);

        root = insert(id_task, priority, root);
    }
    void print(PQNode *node) {
        if (!node)
            return;
        print(node->left);
        while (!node->id.empty()) {
            cout << node->id.back() << " ";
            node->id.pop_back();
        }
        print(node->right);
    }


    PQNode *min_node(PQNode *node) {
        if (!node->left)
            return nullptr;
        return min_node(node->left);
    }

    PQNode *max_node(PQNode *node) {
        if (!node->right)
            return nullptr;
        return max_node(node->right);
    }

    PQNode *delete_node(int prio, PQNode *node)  // log(n) bec of the height = log(n)
    {
        PQNode *temp = node;
        if (prio < node->key) {
            node->left = delete_node(prio, node->left);

        } else if (prio > node->key) {
            node->right = delete_node(prio, node->right);
        } else {
            if (!node->left && !node->right) {
                return nullptr;
            }
            if (!node->left) {
                node = node->right;
            }
            if (!node->right) {
                node = node->left;
            } else {
                PQNode *successor = min_node(node->right);
                node->key = successor->key;
                node->right = delete_node(prio, node->right);
                temp = nullptr;
            }
        }
        if (temp)
            delete temp;


        update_height(node);
        return balancing(node);
    }

    void dequeue() {
        PQNode *maxx = max_node(root);

        if (maxx->id.size() > 0) {
            cout << maxx->id.back() << " \n";
            maxx->id.pop_back();
        } else if (maxx->id.size() == 0) {
            root = delete_node(maxx->key, maxx);
        }
    }
};

// get min num of nodes of avl tree given the height
//  formula ==> 1+f(h-1)+f(h-2)

int numOfNodes(int h)  // recursive approach
{
    if (h == 0)
        return 1;
    if (h == 1)
        return 2;
    return 1 + numOfNodes(h - 1) + numOfNodes(h - 2);
}

int num_of_nodes(int h)  // iterative approach
{
    if (h == 0)
        return 1;
    if (h == 1)
        return 2;
    int a = 1, b = 2, c;

    h--;
    while (h--)  // based on that each element in the seq = 1 + sum of last 2 elements
                 //  (from height = 0): 1, 2, 4, 7, 12, 20,33, 54
    {
        c = a + b + 1;
        a = b;
        b = c;
    }
    return c;
}

// Design an AVL tree of words that can help us know if a word or a prefix exists in our data or not.

struct SNode {
    string data{};
    int height{};
    SNode *left{};
    SNode *right{};

    SNode(string val) :
        data(val), height(0), left(nullptr), right(nullptr) {};
};

class AvlTree 
{
private:
    SNode *root = nullptr ;

public:

    //SNode *root;

    AvlTree() {}

   
    int height(SNode *node) 
    {
        if (!node)
            return -1;
        return node->height;
    }
    void update_height(SNode *node) { node->height = 1 + max(height(node->left), height(node->right)); }
    int balance_factor(SNode *node) { return height(node->left) - height(node->right); }
    // Rotations codes

    SNode *right_rotation(SNode *node) {
        SNode *SubLeft = node->left;  // p=q->left
        node->left = SubLeft->right;  // q->left=p->right
        SubLeft->right = node;  // p->right=q

        update_height(node);
        update_height(SubLeft);

        return SubLeft;  // new root
    }

    SNode *left_rotation(SNode *node) {
        SNode *SubRight = node->right;
        node->right = SubRight->left;
        SubRight->left = node;

        update_height(node);
        update_height(SubRight);

        return SubRight;
    }
    SNode *balancing(SNode *node) {
        if (balance_factor(node) == -2) {
            if (balance_factor(node->right) == 1)
                node->right = right_rotation(node->right);  // relinking because it is restructuring
            node = left_rotation(node);
        } else if (balance_factor(node) == 2) {
            if (balance_factor(node->left) == -1)
                node->left = left_rotation(node->left);
            node = right_rotation(node);
        }
        return node;
    }
    SNode *insert(string ss, SNode *node) {
        if (ss < node->data) 
        {
            if (!node->left)
                node->left = new SNode(ss);
            else
                node->left = insert(ss, node->left);
        } else if (ss > node->data) 
        {
            if (!node->right)
                node->right = new SNode(ss);
            else
                node->right = insert(ss, node->right);
        }
        update_height(node);
        return balancing(node);
    }
    void insert_string(string ss) {
        if (!root)
            root = new SNode(ss);

        root = insert(ss, root);
    }

    bool word_exist(string word, SNode *node)  // o(L*(log (n))
    {
        if (word == node->data)
            return true;

        if (word < node->data) {

            return word_exist(word, node->left);
        } else if (word > node->data) 
        {

            return word_exist(word, node->right);
        }
        return false;
    }

    bool is_word_exist(string word)
    {
        return word_exist(word,root);
    }

    bool prefix_exist(string pre, SNode *node) 
    {

        if(!node)
        {
            return false;
        }
        // linear solution o(n):

        // if(node->data.length() > pre.length())
        // {
        //     string res = node->data.substr(0, pre.size());

        //     if(res== pre)
        //         return true;

        // }
        //  return prefix_exist(pre, node->left) || prefix_exist(pre, node->right);
        //=======================================================================//

        //o(nlog(n)):

        if(pre == node->data.substr(0,pre.size()))
            return true;
        if (pre < node->data.substr(0, pre.size()))
        {
            return prefix_exist(pre, node->left);
        }
        else if (pre > node->data.substr(0, pre.size()))
        {
            return prefix_exist(pre, node->right);
        }
        return false;
    }
    bool is_prefix_exist(string prefix)
    {
        return prefix_exist(prefix,root);
    }
};


int main() 
  {
    // PQ test(1131, 1);
    // test.insertion(3111, 3);
    // test.insertion(2111, 2);
    // test.insertion(3641, 3);
    // test.print(test.root);

    // cout << num_of_nodes(4) << "\n";
    // cout << num_of_nodes(5) << "\n";
    // cout << numOfNodes(4) << "\n";
    // cout << numOfNodes(5);

    AvlTree tree;
    tree.insert_string("abcd");
    tree.insert_string("abc");
    tree.insert_string("xyz");

    cout << tree.is_word_exist("xyz") <<"\n";
    cout << tree.is_prefix_exist("xy") << "\n";
    cout << tree.is_prefix_exist("xyk") << "\n";
    cout << tree.is_prefix_exist("zy");


    cout << "\nNO RTE\n";
}
