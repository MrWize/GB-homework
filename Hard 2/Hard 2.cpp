#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

//задание 1

template <typename T1>
void SWAP (T1& n1, T1& n2) {
    T1 n =n1;
    n1 = n2;
    n2 = n;

}

//задание 2

template <typename T2>
void SortPointers(vector<T2*>& pointers)
{
    std::sort(pointers.begin(), pointers.end(), [](const T2* a, const T2* b) {return *a < *b; });
};

template <typename T2>
void print(vector<T2*>& pointers)
{
    for (int* n : pointers)
        cout << *n;
    cout << endl;
};

//задание 3

const string chars = "AEIOUYaeiouy";      //все гласные в англ. языке

void count1()
{
    ifstream file("Tolstoy.txt");

    auto s1 = chrono::high_resolution_clock::now();     //начало отсчёта

    long count = count_if(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), [=](char c) 
        {return chars.find(c) != string::npos; });

    auto s2 = chrono::high_resolution_clock::now();     //конец отсчёта
    auto s = chrono::duration_cast<chrono::milliseconds>(s2 - s1);

    cout << "найдено гласных: " << count << endl;
    cout << "count_if и find заняли " << s.count() << " миллисекунд.\n\n";

    file.close();
}

void count2()
{
    ifstream file("Tolstoy.txt");

    auto s1 = chrono::high_resolution_clock::now();

    long count = count_if(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), [=](char c) ->bool
        {for (auto n : chars)
        if (n == c) return true;
    return false; });

    auto s2 = chrono::high_resolution_clock::now();
    auto s = chrono::duration_cast<chrono::milliseconds>(s2 - s1);

    cout << "найдено гласных: " << count << endl;
    cout << "сount_if и for заняли " << s.count() << " миллисекунд.\n\n";

    file.close();
}

void count3()
{
    ifstream file("Tolstoy.txt");

    auto s1 = chrono::high_resolution_clock::now();

    long count = 0;
    for (auto i = istreambuf_iterator<char>(file); i != istreambuf_iterator<char>(); ++i)
        if (chars.find(*i) != string::npos) ++count;

    auto s2 = chrono::high_resolution_clock::now();
    auto s = chrono::duration_cast<chrono::milliseconds>(s2 - s1);

    cout << "найдено гласных: " << count << endl;
    cout << "for и find заняли " << s.count() << " миллисекунд.\n\n";

    file.close();
}

void count4()
{
    ifstream file("Tolstoy.txt");

    auto s1 = chrono::high_resolution_clock::now();

    long count = 0;
    for (auto i = istreambuf_iterator<char>(file); i != istreambuf_iterator<char>(); ++i)
    {
        for (auto n : chars)
            if (n == *i) ++count;
    };

    auto s2 = chrono::high_resolution_clock::now();
    auto s = chrono::duration_cast<chrono::milliseconds>(s2 - s1);

    cout << "найдено гласных: " << count << endl;
    cout << "2 цикла for заняли " << s.count() << " миллисекунд.\n\n";

    file.close();
}

int main()
{
    setlocale(0, "");       //русский язык в консоли
    //задание 1

    int a1 = 100;
    int b1 = 123;
    int* p1 = &a1;
    int* p2 = &b1;
    cout << *p1 << " " << *p2 << endl;
    SWAP (p1, p2);
    cout << *p1 << " " << *p2 << endl << endl;

    //задание 2

    int a2(1), b2(2), c2(3), d2(4);
    int* ptr1(&b2), * ptr2(&d2), * ptr3(&a2), * ptr4(&c2);

    vector<int*> pointers;      //тестовый вектор указателей
    pointers.push_back(ptr1);
    pointers.push_back(ptr2);
    pointers.push_back(ptr3);
    pointers.push_back(ptr4);

    print(pointers);
    SortPointers(pointers);
    print(pointers);

    cout << endl;

    //задание 3

    count1();    
    count2();
    count3();   
    count4();   //самый медленный цикл, остальные почти не отличаются по скорости
}
