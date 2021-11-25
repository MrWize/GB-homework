#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

//задание 1

double average(vector <double>& vect)
{
    double sum = 0;
    for (double& n : vect)
        sum += n;
    vect.push_back(sum/vect.size());
    return vect.back();
}

//задание 2
class Matrix
{
    double a[3][3];
public:
    Matrix(double a00, double a01, double a02, 
           double a10, double a11, double a12, 
           double a20, double a21, double a22)
    {
        a[0][0] = a00; a[0][1] = a01; a[0][2] = a02;
        a[1][0] = a10; a[1][1] = a11; a[1][2] = a12;
        a[2][0] = a20; a[2][1] = a21; a[2][2] = a22;
    }

    double det()
    {
        return (a[0][0] * a[1][1] * a[2][2] + a[0][1] * a[1][2] * a[2][0] + a[0][2] * a[1][0] * a[2][1]
            - a[0][2] * a[1][1] * a[2][0] - a[0][0] * a[1][2] * a[2][1] - a[0][1] * a[1][0] * a[2][2]);     //определитель матрицы 3*3
    }

    void print()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
                cout << a[i][j] << "  ";
            cout << endl;
        }
        cout << "определитель матрицы: " << det() << endl << endl;
    }
};

//задание 3

template <typename T>
class ArrayIt
{
    T* array;
    int num;
public:
    class Iterator
    {
        T* it;
    public:
        Iterator(T* iterator) : it(iterator) {}

        T& operator + (int n) { return *(it + n); }
        T& operator - (int n) { return *(it - n); }
        T& operator ++ (int) { return *it++; }
        T& operator -- (int) { return *it--; }
        T& operator ++ () { return *++it; }
        T& operator -- () { return *--it; }
        bool operator != (const Iterator& iter) { return it != iter.it; }
        bool operator == (const Iterator& iter) { return it == iter.it; }
        T& operator* () { return *it; }
    };

    ArrayIt(int n = 1) : num(n)
    {
        array = new T[n];
    }

    T& operator[] (const int& n)
    {
        if (n > 0 && n < num)
            return array[n];
        return array[0];
    }

    Iterator begin() { return array; }
    Iterator end() { return array + num; }

    friend ostream& operator<< (ostream& out, const ArrayIt<T>& i);
};

template <typename T>
ostream& operator << (ostream& out, const ArrayIt<T>& i)
{
    out << ArrayIt<T>::array[i];
    return out;
}

int main()
{
    setlocale(0, "");

    //задание 1

    vector<double> v{ 1.2,2.3,4.5,6.7,8.9,10.11 };
    for (double n : v)
        cout << n << "  ";
    cout << endl << "среднее: " << average(v) << endl << endl;

    //задание 2
    
    Matrix matrix(5.2, 7, 1.5, 1.6, 4.8, 6, 2, 1.1, 3.9);
    matrix.print();

    //задание 3

    ArrayIt<int> array(10);

    for (int i = 0; i < 10; ++i)
    {
        array[i] = rand() % 100;
        cout << array[i] << " ";
    }

    auto it = ArrayIt<int>::Iterator(array.begin());
    cout<<"\nшестой элемент: " << it + 5;
}

