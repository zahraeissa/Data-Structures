#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct Node
{
    T data;
    Node *next; 
    Node(T value) : data(value), next(nullptr) {};
};
template <typename T>
class Stack
{
private:
    Node<T> *head = nullptr;

public:
    ~Stack()
    {
        Node<T> *temp;
        while (head != nullptr)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool is_empty()
    {
        if (head == nullptr)
        {
            return true;
        }
        return false;
    }

    void push(T value)
    {
        Node<T> *new_node = new Node(value);
        new_node->next = head;
        head = new_node;
    }

    void pop()
    {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    T peek()
    {
        return head->data;
    }

    void print()
    {
        for (Node<T> *cur = head; cur; cur = cur->next)
        {
            cout << cur->data << " ";
        }
        cout << "\n";
    }
};

vector<int> getMaxElementIndexes(vector<int> a, vector<int> rotate)
{
    vector<int> res;
    int len_a = a.size();

    for (int i = 0; i < rotate.size(); i++)
    {
        vector<int> copy_a = a;
        int cycles = rotate[i] % len_a;
        while (cycles--)
        {
            int temp = copy_a[0];
            copy_a.push_back(temp);
            copy_a.erase(copy_a.begin());
        }
        int mx = *max_element(copy_a.begin(), copy_a.end());
        for (int j = 0; j < copy_a.size(); j++)
        {
            if (copy_a[j] == mx)
            {
                res.push_back(j);
                break;
            }
        }
    }
    return res;
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}
bool is_char(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '(' || ch == ')')
        return false;
    return true;
}

string infix_to_postfix(string expr)
{
    stack<char> operators;
    string postfix = "";

    for (int i = 0; i < expr.size(); i++)
    {
        if (is_char(expr[i]))
        {
            postfix += expr[i];
        }
        else if (expr[i] == '^')
        {
            operators.push(expr[i]);
        }
        else if (expr[i] == '(')
        {
            operators.push(expr[i]);
        }
        else if (expr[i] == ')')
        {
            while (operators.top() != '(' && !operators.empty())
            {

                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else
        {
            while ((!operators.empty()) && (precedence(expr[i]) <= precedence(operators.top())))
            {

                postfix += operators.top();
                operators.pop();
            }
            operators.push(expr[i]);
        }
    }
    while (!operators.empty())
    {
        if (operators.top() != '(' && operators.top() != ')')
        {
            postfix += operators.top();
            operators.pop();
        }
    }
    return postfix;
}

double operation(double &b, double &a, char &c)
{
    if (c == '*')
    {
        return a * b;
    }
    else if (c == '+')
    {
        return a + b;
    }
    else if (c == '-')
    {
        return a - b;
    }
    else if (c == '/')
    {
        return a / b;
    }

    return pow(a, b);
}

double postfix_evaluation(string expr)
{
    stack<double> process;
    double result;

    for (int i = 0; i < expr.size(); i++)
    {
        if (is_char(expr[i]))
        {
            process.push(double(expr[i] - '0'));
        }
        else
        {
            double b = process.top();
            process.pop();
            double a = process.top();
            process.pop();
            result = operation(b, a, expr[i]);
            process.push(result);
        }
    }
    return process.top();
}
string infix_to_postfix_1(string expr)
{
    stack<char> operators;
    string postfix = "";

    for (int i = 0; i < expr.size(); i++)
    {
        if (is_char(expr[i]))
        {
            postfix += expr[i];
        }
        else if (expr[i] == '^')
        {
            while (!operators.empty() && operators.top() == '^')
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(expr[i]);
        }
        else if (expr[i] == '(')
        {
            operators.push(expr[i]);
        }
        else if (expr[i] == ')')
        {
            while (operators.top() != '(' && !operators.empty())
            {

                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else
        {
            while ((!operators.empty()) && (precedence(expr[i]) > precedence(operators.top())))
            {

                postfix += operators.top();
                operators.pop();
            }
            operators.push(expr[i]);
        }
    }
    while (!operators.empty())
    {
        if (operators.top() != '(' && operators.top() != ')')
        {
            postfix += operators.top();
            operators.pop();
        }
    }
    return postfix;
}
string infix_to_prefix(string expr)
{

    string prefix = "";
    string reversed_expr = "";

    for (int i = expr.size() - 1; i >= 0; i--)
    {
        if (expr[i] == '(')
            reversed_expr += ')';

        else if (expr[i] == ')')
            reversed_expr += '(';

        else
            reversed_expr += expr[i];
    }
    string result = infix_to_postfix_1(reversed_expr);

    for (int i = result.size() - 1; i >= 0; i--)
    {
        prefix += result[i];
    }
    return prefix;
}
int main()
{

    cout << infix_to_prefix("4^3^2");
}
