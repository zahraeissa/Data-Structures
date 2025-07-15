#include <bits/stdc++.h>
using namespace std;

// max heap
class MaxHeap {
private:
    int *array{};
    int size{};
    int capacity = 1000;

    int left(int index) {
        int L_child = 2 * index + 1;
        if (L_child > size)
            return -1;
        return L_child;
    }

    int right(int index) {
        int R_child = 2 * index + 2;
        if (R_child > size)
            return -1;
        return R_child;
    }

    int parent(int index) {
        if (index == 0)
            return -1;
        int par = (index - 1) / 2;
        return par;
    }

public:
    MaxHeap() {
        array = new int[100];
        size = 0;
        capacity = 1000;
    }

    ~MaxHeap() {
        delete[] array;
        array = nullptr;
    }

    void heapify_up(int index) // start from bottom towards up
    {
        int par_pos = parent(index);
        if (index == 0 || array[par_pos] > array[index])
            return;
        swap(array[index], array[par_pos]);
        heapify_up(par_pos);
    }

    void heapify_down(int index) // start from top towards bottom
    {
        int par_pos = index;
        int L = left(index);
        int R = right(index);
        if (L == -1 || array[par_pos] > R)
            return;
        if (R < L)
            swap(L, R);
        if (array[par_pos] < array[R])
            swap(array[par_pos], array[R]);
        heapify_down(R);
    }

    void insert(int value) {
        if (size >= capacity)
            return;

        array[size++] = value;
        heapify_up(size - 1);
    }

    void delete_max(int index) {
        if (size == 0)
            return;
        array[0] = array[size - 1];
        size--;
        heapify_down(0);
    }

    int top() {
        if (size == 0)
            return -1;
        return array[0];
    }

    void CreatHeap(vector<int> &values) // floyd algo to create heap(max_heap) in o(n) instead of nlogn
    {
        if (values.size() >= size)
            return;
        for (int i = 0; i < values.size(); i++) {
            array[i] = values[i];
        }
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify_down(i);
        }
    }
};


///////////////////////////////min heap///////////////////////////////////////////
class MinHeap 
{
private:
    int *array{};
    int size{};
    int capacity = 1000;

    int left(int index) {
        int L_child = 2 * index + 1;
        if (L_child > size)
            return -1;
        return L_child;
    }

    int right(int index) {
        int R_child = 2 * index + 2;
        if (R_child > size)
            return -1;
        return R_child;
    }

    int parent(int index) {
        if (index == 0)
            return -1;
        int par = (index - 1) / 2;
        return par;
    }

public:
    MinHeap() 
    {
        array = new int[100];
        size = 0;
        capacity = 1000;
    }

    ~MinHeap() 
    {
        delete[] array;
        array = nullptr;
    }

    void heapify_up(int index) // move toward top
    {
        int par_pos = parent(index);
        if (index == 0 || array[par_pos] > array[index])
            return;
        swap(array[index], array[par_pos]);
        heapify_up(par_pos);
    }

    void heapify_down(int index) // move towards bottom
    {
        int par_pos = index;
        int L = left(index);
        int R = right(index);
        if (L == -1 || array[par_pos] < array[L])
            return;
        if (R < L)
            swap(array[L], array[R]);
        if (array[par_pos] > array[L])
            swap(array[par_pos], array[L]);
        heapify_down(L);
    }

    void insert(int value) {
        if (size >= capacity)
            return;

        array[size++] = value;
        heapify_up(size - 1);
    }

    void delete_min() 
    {
        // pop
        if (size == 0)
            return;
        array[0] = array[size - 1];
        size--;
        heapify_down(0);
    }


    void heapify() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify_down(i);
        }
    }

    void create_heap(vector<int> &values) // floyd algo to create heap in o(n) instead of nlogn
    {
        if (values.size() >= capacity)
            return;

        for (int i = 0; i < values.size(); i++) {
            array[i] = values[i];
        }

        size = values.size();
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify_down(i);
        }
    }


    void traversing()
    {

        for (int i = 0; i < size ; i++)
        {
            cout << array[i] << " " ;
        }
    }

    bool is_heap(int par_pos) {
        if (array[par_pos] == -1)
            return true;
        int L = left(par_pos);
        int R = right(par_pos);

        if (L != -1 || array[L] < array[par_pos])
            return false;

        if (R != -1 || array[R] < array[par_pos])
            return false;

        return is_heap(L) && is_heap(R);
    }

    bool is_heap_array(int *p, int n) {
        // if `is_heap()` were public and used without the is heap array, it would still only work with the **heap's
        // internal array**, not external arrays.
        //- **What you want**: Check if `external_arr` is a valid heap
        // - **What `is_heap()` does**: Check if the heap's internal array is valid
        // - **Result**: You're checking the wrong data!


        int *temp_arr = array;
        int sz = size;

        array = p;
        size = n;

        bool res = is_heap(0);

        array = temp_arr;
        size = sz;
        return res;
    }

    void heap_sort(int arr[], int n) // ascending order
    {

        int *tempArr = array;
        int sz = size;

        array = arr;
        size = sz;

        while (size--) {
            swap(array[0], array[size - 1]);
            heapify_down(array[0]);
        }

        array = tempArr;
        size = sz;
    }
};



class PriorityQueue // based on max heap implementation
{
private:
    int *value{};
    int *key{};
    int size{};
    int capacity = 1000;

    int left(int index) {
        int L_child = 2 * index + 1;
        if (L_child > size)
            return -1;
        return L_child;
    }

    int right(int index) {
        int R_child = 2 * index + 2;
        if (R_child > size)
            return -1;
        return R_child;
    }

    int parent(int index) {
        if (index == 0)
            return -1;
        int par = (index - 1) / 2;
        return par;
    }

public:
    PriorityQueue() {
        value = new int[100];
        key = new int[100];
        size = 0;
        capacity = 1000;
    }

    ~PriorityQueue() {
        delete[] value;
        delete[] key;
        value = nullptr;
        key = nullptr;
    }

    void heapify_up(int index) // start from bottom towards up
    {
        int par_pos = parent(index);
        if (index == 0 || value[par_pos] > value[index])
            return;
        swap(value[index], value[par_pos]);
        swap(key[index], key[par_pos]);
        heapify_up(par_pos);
    }

    void heapify_down(int index) // start from top towards bottom
    {
        int par_pos = index;
        int L = left(index);
        int R = right(index);
        if (L == -1 || value[par_pos] > R)
            return;
        if (R < L)
            swap(L, R);

        if (value[par_pos] < value[R]) {
            swap(value[par_pos], value[R]);
            swap(key[par_pos], key[R]);
            heapify_down(R);
        }
    }

    void enqueue(int id, int prio_num) {
        if (size >= capacity)
            return;

        value[size] = id;
        key[size] = prio_num;
        size++;
        heapify_up(size - 1);
    }

    void dequeue(int id, int prio) {
        if (size == 0)
            return;
        value[0] = value[size - 1];
        key[0] = key[size - 1];
        size--;

        heapify_down(0);
    }

    
    pair<int, int> get_top() 
    {
        if (size == 0)
            return make_pair(-1, -1);
        return make_pair(value[0], key[0]);
    }

    void CreatHeap(vector<int> &values)  //floyd algo to create heap(max_heap) in o(n) instead of nlogn
    {
        if (values.size() >= capacity)
            return;

        for (int i = 0; i < values.size(); i++) 
        {
            value[i] = values[i];
        }

        size = values.size();

        for (int i = size / 2 - 1; i >= 0; i--) 
        {
            heapify_down(i);
        }
    }
};


int main() 
{

    cout << "\n NO RTE\n";
    vector<int> vv = {2, 5, 4, 7, 6, 8};
    MinHeap heap;
    heap.create_heap(vv);
    heap.traversing();

}
