#include <iostream>
#include <cassert> 
#include <cstdlib>
#include <vector>

using namespace std;

//задание 1

int sort1(const void* a, const void* b)     //функция для сортировки
{
    return (*(int*)a - *(int*)b);
}

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt() : m_length(0), m_data(nullptr)
    { }

    ArrayInt(int length) :
        m_length(length)
    {
        assert(length >= 0);

        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int getLength() { return m_length; }

    void pop_back()     //удаляем последний элемент
    {
        assert(m_length > 0);

        int* data = new int[m_length - 1];

        for (int i = 0; i < (m_length-1); ++i)
            data[i] = m_data[i];

        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void pop_front()     //удаляем первый элемент
    {
        assert(m_length > 0);

        int* data = new int[m_length - 1];

        for (int i = 0; i < (m_length - 1); ++i)
            data[i] = m_data[i+1];

        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void print()        //выводим "вектор" на экран
    {
        for (int i = 0; i < getLength(); ++i)
            cout << m_data[i] << " ";
        cout << endl;
    }

    void sort()         //сортируем
    {
        assert(m_length > 0);

        int* data = new int[m_length];

        for (int i = 0; i < (m_length); ++i)
            data[i] = m_data[i];

        qsort(data, m_length, sizeof(int), sort1);

        delete[] m_data;
        m_data = data;
    }

    ~ArrayInt()
    {
        delete[] m_data;
    }
};

//задание 2 

int find(int find, vector<int>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (find == v[i]) return -1;
        else if (find < v[i]) return i;
    }
    return v.size();
};

void different(vector<int>& v)
{
    setlocale(0, "");
    cout << "ваш вектор: ";
    vector<int> check;
    int num;

    for (int i = 0; i < v.size(); i++) 
    {
        cout << v[i] << " ";
        if ((num = find(v[i], check)) != -1)  
            check.insert(check.begin() + num, v[i]);
    }
    cout <<"\nв данном векторе "<< check.size()<<" различных чисел\n";
}

int main()
{
    //задание 1

    ArrayInt arr(10);
    for (int i = 0; i < 10; ++i)
        arr[i] = rand() % 10;

    arr.print();

    arr.sort();
    arr.print();

    arr.pop_back();
    arr.print(); 
    
    arr.pop_front();
    arr.print();
    cout << endl;

    //задание 2
    vector<int> vect{ 1,1,2,3,4,5,5,6,7,6,6,7,7,8,2,2,9,10 };
    different(vect);
    

    return 0;
}