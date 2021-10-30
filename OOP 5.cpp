#include <iostream>
#include <string>
using namespace std;

//задание 1

template <class T> 

class Pair1
{
private:
    T m_first;
    T m_second;
public:
    Pair1(const T& a, const T& b) :m_first(a), m_second(b) {}

    const T& first() const
    {
        return m_first;
    }
    const T& second() const
    {
        return m_second;
    }
};

//задание 2

template <class T1, class T2>

class Pair
{
private:
    T1 m_first;
    T2 m_second;
public:
    Pair(const T1& a, const T2& b) :m_first(a), m_second(b) {}

    T1& first() 
    {
        return m_first;
    }
    const T1& first() const
    {
        return m_first;
    }
    T2& second() 
    {
        return m_second;
    }
    const T2& second() const
    {
        return m_second;
    }
};

//задание 3

template <class T3>

class StringValuePair :public Pair<string,T3>
{
public:
    StringValuePair(const string& a, const T3& b) :Pair<string,T3> (a,b) {}
};

int main()
{
    //задание 1
    {
        Pair1<int> p1(6, 9);
        cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

        const Pair1<double> p2(3.4, 7.8);
        cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
    }
    //задание 2
    {
        Pair<int, double> p1(6, 7.8);
        cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

        const Pair<double, int> p2(3.4, 5);
        cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
    }
    //задание 3
    {
        StringValuePair<int> svp("Amazing", 7);
        std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
        return 0;
    }

    return 0;
};