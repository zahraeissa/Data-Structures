#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node *prev;

    // Constructor to initialize the node
    // Node(int val) : data(val), next(nullptr) {};

    Node(int val)
    {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

class linked_list
{
private:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    ~linked_list()
    {
        Node *temp;
        while (head)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void link(Node *first, Node *second)
    {
        if (first)
        {
            first->next = second;
        }
        if (second)
        {
            second->prev = first;
        }
    }
    void insert_end(int value)
    {
        Node *new_node = new Node(value);
        // assume always there is tail pointer with the linked list

        if (!head)
        {
            head = new_node;
            tail = head;
            return;
        }
        link(tail, new_node);
        tail = new_node;
    }
    void insert_front(int value)
    {
        Node *new_node = new Node(value);
        if (!head)
        {
            head = new_node;
            tail = head;
        }
        link(new_node, head);
        head = new_node;
    }

    void insert_middle(Node *before, int value)
    {
        Node *middle = new Node(value);

        link(before, middle);
        link(middle, before->next);
    }

    void insert_sorted(int value)
    {
        Node *new_node = new Node(value);
        int len = length();

        if (len == 0)
        {
            insert_front(value);
        }

        if (value <= head->data)
        {
            insert_front(value);
        }
        else if (value >= tail->data)
        {
            insert_end(value);
        }
        else
        {
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (cur->data >= value)
                {
                    insert_middle(cur->prev, value);
                    break;
                }
            }
        }
    }

    int length()
    {
        if (!head)
        {
            return 0;
        }
        int len = 0;
        for (Node *cur = head; cur; cur = cur->next)
        {
            len++;
        }
        return len;
    }

    void print()
    {
        if (!head)
        {
            cout << "list is empty\n";
            return;
        }
        for (Node *cur = head; cur; cur = cur->next)
        {
            // cout << cur->prev->data << "\t=>" << cur->data << "\t=>" << cur->next->data << "\n ";
            cout << cur->data << " ";
        }
    }

    void delete_front()
    {
        if (!head)
        {
            return;
        }
        // else if (head == tail)
        // {
        //     delete head;
        //     head = tail = nullptr;
        //     return;
        // }
        Node *temp = head;
        head = head->next;
        delete temp;
        if (head)
            head->prev = nullptr;
        else if (!head)
            tail = nullptr;
    }
    void delete_end()
    {
        if (!head)
        {
            return;
        }
        Node *temp = tail;
        tail = tail->prev;
        delete temp;
        if (tail)
            tail->next = nullptr;
        else if (!tail)
            head = nullptr;
    }
    Node *delete_and_link(Node *cur)
    {
        Node *before = cur->prev;
        Node *after = cur->next;
        link(before, after);
        delete cur;
        return before;
    }
    void delete_node(int value)
    {
        if (!head)
        {
            return;
        }

        if (head->data == value)
        {
            delete_front();
        }
        else if (tail->data == value)
        {
            delete_end();
        }

        for (Node *cur = head; cur; cur = cur->next)
        {

            if (cur->data == value)
            {
                cur = delete_and_link(cur);
                break;
            }
        }
    }
    void delete_node_with_key(int value)
    {
        if (!head)
        {
            return;
        }

        for (Node *cur = head; cur;) // cur = cur->next)
        {

            if (head->data == value)
            {
                delete_front();
                cur = cur->next;
            }
            else if (tail->data == value)
            {
                delete_end();
                cur = cur->next;
            }
            else if (cur->data == value)
            {
                cur = delete_and_link(cur);
                // break;
            }
            else
                cur = cur->next;
        }
    }
    void delete_even_positions()
    {
        int pos = 1;

        for (Node *cur = head; cur; cur = cur->next)
        {
            if (pos % 2 == 0)
            {
                cur = delete_and_link(cur);
            }

            pos++;
        }
    }
    void delete_odd_positions()
    {
        if (!head)
        {
            return;
        }
        delete_front();
        int pos = 2;

        for (Node *cur = head; cur; cur = cur->next)
        {
            if (pos % 2 != 0)
            {
                cur = delete_and_link(cur);
            }
            pos++;
        }
    }

    // utilize delete even position function to delete odd positions:
    void delete_odd_positions_2()
    {
        insert_front(-1); // dummy_node
        delete_even_positions();
        delete_front(); // to delete dummy node
    }

    bool is_palindrome()
    {
        if (!head || head == tail)
        {
            return true;
        }
        // vector<int> vec1;
        // vector<int> vec2;
        // for (Node *cur = head; cur; cur = cur->next)
        // {
        //     vec1.push_back(cur->data);
        // }
        // for (Node *cur = tail; cur; cur = cur->prev)
        // {
        //     vec2.push_back(cur->data);
        // }
        // if (vec1 == vec2)
        // {
        //     return true;
        // }
        // return false;

        // another approach to code is palindrome function (more efficient):

        Node *start = head;
        Node *end = tail;
        int len = length() / 2;
        while (len--)
        {
            if (start->data != end->data)
                return false;
            start = start->next;
            end = end->prev;
        }
        return true;
    }
};

int main()
{
    linked_list list;
    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(2);
    list.insert_end(1);
    // list.insert_end(5);
    // list.insert_end(4);
    // list.insert_end(4);

    list.print();
    cout << "\n";
    if (list.is_palindrome())
        cout << "true";
    else
        cout << "false";
    // list.print();
    cout << "\nNo RTE\n";
}