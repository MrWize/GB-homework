#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

//задание 1

template<typename T>
void insert_sorted(vector<T>& vec, const T& new_num)
{
    vec.insert(lower_bound(vec.begin(), vec.end(), new_num), new_num);
}

template<typename T>
void print(const vector<T>& vec)
{
    for_each(vec.begin(), vec.end(), [](T i) { cout << i << " "; });

    cout << endl;
}

//задание 2

void task2()
{
    vector<double> a(100);

    auto randomize = [](double &s)
    {
        return 50 * sin(rand() % 100);
    };

    transform(a.begin(), a.end(), a.begin(), randomize);

    print(a);
    cout << endl;

    static double errorSum = 0;

    vector<double> b(100);

    auto roundVec = [](double& s)
    {
        errorSum += pow((s - round(s)), 2);     //считаем ошибку по формуле
        return round(s); 
    };

    transform(a.begin(), a.end(), b.begin(), roundVec);

    print(b);

    cout << "\nОшибка цифрового сигнала: " << errorSum << endl;
}



int main()
{
    setlocale(0, "");

    //задание 1

    vector<int> v1{ 1,2,3,4,6,7 };
    print(v1);
    insert_sorted(v1, 5);
    print(v1);
    cout << endl;

    vector<double> v2{ 1.1,2.5,3.7,4.2};
    print(v2);
    insert_sorted(v2, 3.9);
    print(v2);
    cout << endl;

    //задание 2

    task2();
}
