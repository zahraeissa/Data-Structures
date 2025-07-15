#include <bits/stdc++.h>
using namespace std;

// class Stack
// {
// private:
//     int size{};
//     int added_ele{};
//     int *arr{};

// public:
//     Stack(int size) : size(size), added_ele(0)
//     {
//         arr = new int[size];
//     }
//     ~Stack()
//     {
//         delete[] arr;
//     }
//     bool is_empty()
//     {
//         if (added_ele == 0)
//             return true;
//         return false;
//     }
//     bool is_full()
//     {
//         if (added_ele == size)
//             return true;
//         return false;
//     }

//     void push(int value)
//     {
//         if (is_full())
//             return;

//         ++added_ele;
//         for (int i = added_ele - 1; i >= 0; i--)
//         {
//             arr[i + 1] = arr[i];
//         }
//         arr[0] = value;
//     }
//     void pop()
//     {
//         if (is_empty())
//             return;

//         for (int i = 0; i < added_ele - 1; i++)
//         {
//             arr[i] = arr[i + 1];
//         }
//         --added_ele;
//     }

//     void print()
//     {
//         for (int i = 0; i < added_ele; i++)
//         {
//             cout << arr[i] << " ";
//         }
//         cout << "\n";
//     }
//};

template <typename T>
class Stack
{
private:
    int size{};
    int top{};
    T *arr{};

public:
    Stack(int size) : size(size), top(-1)
    {

        arr = new T[size];
    }
    bool is_empty()
    {
        if (top == -1)
            return true;
        return false;
    }
    bool is_full()
    {
        if (top == size)
            return true;
        return false;
    }

    void push(T value)
    {
        assert(!is_full());
        arr[++top] = value;
    }
    void pop()
    {
        assert(!is_empty());
        top--;
    }
    T get_peek()
    {
        assert(!is_empty());
        return arr[top];
    }
    void print()
    {
        for (int i = top; i >= 0; i--)
        {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }

    string reverse_number(string line, Stack &st)
    {
        string res = "";

        for (int i = 0; i <= line.size(); i++)
        {
            if (line[i] != ' ')
            {
                st.push(line[i]);
            }
            else
            {
                while (!st.is_empty())
                {
                    res += st.get_peek();
                    st.pop();
                }
                res += ' ';
            }
        }

        for (int i = top; i >= 0; i--)
        {
            res += st.get_peek();
            st.pop();
        }
        return res;
    }

    //=================================================//

    int reverse_number(int num, Stack &st)
    {
        while (num != 0)
        {
            int temp = num % 10; // 4
            st.push(temp);       // 4321
            num = num / 10;      //
        }
        int tens = 1;
        while (!st.is_empty())
        {
            num = tens * st.get_peek() + num;
            st.pop();
            tens *= 10;
        }
        return num;
    }
    char matching(char c)
    {
        if (c == ')')
            return '(';

        if (c == ']')
            return '[';

        return '{';
    }
    bool valid_parentheses(string ss, Stack &st)
    {
        for (int i = 0; i < ss.size(); i++)
        {
            if (ss[i] == '(' || ss[i] == '[' || ss[i] == '{')
            {
                st.push(ss[i]);
            }
            else
            {
                if (!st.is_empty())
                {
                    if (st.get_peek() != matching(ss[i]))
                    {
                        return false;
                    }
                    else
                    {
                        st.pop();
                    }
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
    }
};

int main()
{
    Stack<char> st(100);
    cout << st.valid_parentheses("{()}", st);

    cout << "\nNO RTE\n";
}