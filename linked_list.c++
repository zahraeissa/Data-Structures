#include <bits/stdc++.h>
using namespace std;


struct Node
{
    int data;
    Node *next;
    // Constructor to initialize the node
    Node(int val) : data(val), next(nullptr) {};
};

void is_valid(int length, Node *head, Node *tail)
{
    if (length == 0)
    {
        assert(head == nullptr);
        assert(tail == nullptr);
    }

    else
    {
        assert(head != nullptr);
        assert(tail != nullptr);

        if (length == 1)
        {
            assert(head == tail);
        }
        else
        {
            assert(head != tail);
        }
        assert(!tail->next);
    }
    int len = 0;
    for (Node *cur = head; cur->next != NULL; cur = cur->next)
    {
        len++;
        assert(len < 10000);
    }
    assert(len == length);
}

class linked_list
{
private:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    ~linked_list()
    {
        Node *temp;
        while (head != nullptr)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void print()
    {
        if (head == NULL && tail == NULL)
        {
            cout << "list is empty!\n";
            return;
        }
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    void insert_front(int value)
    {
        Node *new_node = new Node(value);
        new_node->next = head;
        head = new_node;
    }
    void delete_front()
    {
        Node *temp;
        temp = head;
        head = head->next;
        delete temp;
    }
    void get_nth_back(int pos)
    {
        int len = 0;
        for (Node *cur = head; cur != NULL; cur = cur->next)
        {
            len++;
        }

        // cout << len << ".";
        pos = len - (pos - 1); // 6 - 0 = 6

        int ll = 0;
        for (Node *cur = head; cur != NULL; cur = cur->next)
        {
            ll++;
            if (ll == pos)
            {
                cout << cur->data << "\n";
                break;
            }
        }
    }
    int length()
    {
        int len = 0;
        for (Node *cur = head; cur != NULL; cur = cur->next)
        {
            len++;
        }
        return len;
    }
    bool is_same(linked_list &list)
    {
        Node *other_head = list.head;
        for (Node *cur = head; cur != NULL; cur = cur->next)
        {
            if (cur->data == other_head->data)
            {
                continue;
            }
            else
            {
                return 0;
            }
        }
        return 1;
    }
    void deletion_first_node()
    {
        if (head == tail)
        {

            delete head;
            head = NULL;
            tail = NULL;
            return;
        }
        Node *temp = head;
        head = head->next;
        delete temp;
        return;
    }
    void deletion_nth_node(int pos)
    {
        Node *temp = NULL;
        int len = 0;
        for (Node *cur = head; cur != NULL; temp = cur, cur = cur->next)
        {
            if (len == pos)
            {
                temp->next = cur->next;
                delete cur;
                break;
            }
            len++;
        }
    }
    void delete_last_node()
    {
        if (head == nullptr)
        {
            return;
        }
        if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node *prev = nullptr;
        Node *cur = head;
        for (; cur->next != nullptr; prev = cur, cur = cur->next);

        delete cur;
        tail = prev;
        tail->next = nullptr;
        
        
    }
};

// class linked_list_2
// {
// private:
//     Node *head;

// public:
//     ~linked_list_2()
//     {
//         while (head != nullptr)
//         {
//             Node *temp = head;
//             head = head->next;
//             delete temp;
//         }
//     }
//     void print()
//     {

//         for (Node *cur = head; cur != nullptr; cur = cur->next)
//         {
//             cout << cur->data << " ";
//         }
//         cout << "\n";
//     }

//     void add_element(int value)
//     {
//         Node *temp = new Node(value);
//         temp->next = head;
//         head = temp;
//     }
//     int length()
//     {
//         int len = 0;
//         for (Node *cur = head; cur != NULL; cur = cur->next)
//         {
//             len++;
//         }
//         return len;
//     }
//     void get_tail()
//     {
//         if (head == NULL)
//             return;

//         Node *cur = head;
//         while (cur->next != NULL)
//         {
//             cur = cur->next;
//         }
//         cout << cur->data;
//     }
// };

int main()
{
    linked_list list;
    linked_list lol;
    list.insert_front(6);
    list.insert_front(5);
    list.insert_front(4);
    list.insert_front(3);
    lol.insert_front(3);
    // list.print();
    cout << "\n";
    // list.deletion_first_node();
    // list.deletion_nth_node(3);
    // list.delete_last_node();
    list.print();
    list.delete_last_node();
    cout << "\n";
    list.print();
    // list.print();
    cout << "\n";
    cout << "\nNO RTE\n";
}
