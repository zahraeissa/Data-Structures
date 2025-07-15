#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {};
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
    void insert_back(int value)
    {
        Node *new_node = new Node(value);
        if (head == nullptr)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }
    }
    void delete_front()
    {
        Node *temp;
        temp = head;
        head = head->next;
        delete temp;
    }
    Node *get_nth(int pos)
    {
        int len = 1;
        for (Node *cur = head; cur != NULL; cur = cur->next)
        {
            if (len == pos)
            {
                return cur;
            }
            len++;
        }
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
        for (Node *cur = head; cur != nullptr; cur = cur->next)
        {
            len++;
        }
        return len;
    }
    void deletion_first_node()
    {
       
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
      
        Node *prev = nullptr;
        Node *cur = head;
        for (; cur->next != nullptr; prev = cur, cur = cur->next)
            ;

        delete cur;
        tail = prev;
        tail->next = nullptr;
    }

    void delete_node_with_key(int value)
    {
        Node *prev = nullptr;
        for (Node *cur = head; cur != nullptr; prev = cur, cur = cur->next)
        {
            if (cur->data == value)
            {
                if (cur->data == head->data)
                {
                    deletion_first_node();
                    return;
                }
                else if (cur->data == tail->data)
                {
                    delete_last_node();
                    return;
                }
                else
                {
                    prev->next = cur->next;
                    delete cur;
                    return;
                }
            }
        }
    }
    void swap_pairs()
    {
        if (head == nullptr || head->next == nullptr)
        {
            return;
        }

        Node *prev = head;
        Node *cur = head->next;

        while (prev != nullptr && cur != nullptr)
        {
            swap(prev->data, cur->data);
            prev = cur->next;
            if (prev != nullptr)
            {
                cur = prev->next;
            }
            else
            {
                cur = nullptr;
            }
        }
    }
    void reverse(linked_list &list)
    {
        for (Node *cur = head; cur != nullptr; cur = cur->next)
        {
            list.insert_front(cur->data);
        }
        list.print();
    }
    void delete_even_positions()
    {
        int pos = 1;
        Node *prev = nullptr;
        Node *temp = nullptr;
        for (Node *cur = head; cur != nullptr;)
        {
            temp = cur;
            if (pos % 2 == 0)
            {
                if (cur == tail)
                {
                    cur = cur->next;
                    delete temp;
                    tail = prev;
                    tail->next = nullptr;
                }
                else
                {

                    prev->next = cur->next;
                    cur = cur->next;
                    delete temp;
                }
            }
            else
            {
                prev = cur;
                cur = cur->next;
            }
            pos++;
        }
    }
    void insert_sorted(int value)
    {
        Node *new_node = new Node(value);
        if (head == nullptr && tail == nullptr)
        {
            head = new_node;
            tail = new_node;
            return;
        }
        else if (head->next == nullptr)
        {
            if (head->data <= new_node->data)
            {
                insert_back(new_node->data);
            }
            else
            {
                insert_front(new_node->data);
            }
            return;
        }
        else if (new_node->data > tail->data)
        {
            insert_back(new_node->data);
            return;
        }
        else
        {
            if (head->data >= new_node->data)
            {
                insert_front(new_node->data);
                return;
            }
            else
            {
                for (Node *cur = head; cur->next != nullptr; cur = cur->next)
                {

                    if (cur->next->data >= new_node->data)
                    {
                        new_node->next = cur->next;

                        cur->next = new_node;
                        return;
                    }
                }
            }
        }
    }
    void swap_head_tail()
    {
        Node *prevT;
        Node *cur = head;
        for (; cur->next != nullptr; prevT = cur, cur = cur->next)
            ;

        prevT->next = head;
        tail->next = head->next;
        head->next = nullptr;
        swap(head, tail);
    }
    void left_rotate(long long k)
    {
        if (head == tail || head == nullptr || k % length() == 0)
        {
            return;
        }
        Node *temp = get_nth(k);
        tail->next = head;
        tail = temp;
        head = temp->next;
        tail->next = nullptr;
    }
    void remove_duplicates()
    {
        vector<int> frq(1000001);
        Node *prev;
        for (Node *cur = head; cur != nullptr;)
        {
            Node *temp = cur;
            frq[cur->data]++;
            if (frq[cur->data] > 1)
            {
                prev->next = cur->next;
                cur = cur->next;
                delete temp;
            }
            else
            {
                prev = cur;
                cur = cur->next;
            }
        }
    }
    void remove_last_occurance(int key)
    {
        vector<int> frq(1000001);
        for (Node *cur = head; cur != nullptr; cur = cur->next)
        {
            frq[cur->data]++;
        }
        int cnt = 0;
        Node *prev;
        for (Node *cur = head; cur != nullptr; prev = cur, cur = cur->next)
        {
            if (frq[key] == 0)
            {
                return;
            }
            if (cur->data == key)
            {
                cnt++;
                if (frq[key] == cnt)
                {
                    if (cur == head)
                    {
                        delete_front();
                        return;
                    }
                    else if (cur == tail)
                    {
                        delete_last_node();
                        return;
                    }
                    else
                    {
                        prev->next = cur->next;
                        delete cur;
                        return;
                    }
                }
            }
        }
    }
    Node *move_last(Node *cur, Node *prev)
    {
        Node *next = cur->next;
        tail->next = cur;
        if (cur == head)
        {
            head = cur->next;
        }
        else if (cur == tail)
        {
            return cur;
        }
        else // if (prev)
        {
            prev->next = cur->next;
        }

        tail = cur;
        tail->next = nullptr;
        return next;
    }

    void move_to_back(int key)
    {
        int len = length();
        if (len <= 1)
        {
            return;
        }
        Node *prev = nullptr;

        for (Node *cur = head; len--;) // o(len)
        {
            if (cur->data == key)
            {
                cur = move_last(cur, prev);
            }
            else
            {
                prev = cur;
                cur = cur->next;
            }
        }
    }
    int recurcive_max(Node *head = nullptr, bool firstCall = true)
    {
        if (firstCall)
        {
            return recurcive_max(this->head, false);
        }
        if (head->next == nullptr)
        {
            return head->data;
        }

        
        return max(recurcive_max(head->next,false),head->data);
    }
};
int main()
{
    linked_list list;
    list.insert_back(2);
    list.insert_back(1);
    list.insert_back(1);
    list.insert_back(3);
    list.insert_back(2);
    list.insert_back(4);
    list.insert_back(3);
    list.insert_back(5);
    list.insert_back(2);

    list.print();
    cout << "\n";

    // cout << list.recurcive_max() << "\n";
    cout<<list.recurcive_max()<<" ";

    //list.print();
    cout << "\nNO RTE\n";
}
