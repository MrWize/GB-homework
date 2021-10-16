#include <iostream>
#include <cmath>
#include <cstdint>

using namespace std;

//задание 1

class Power
{
private:
    double a;
    double b;
public:
    Power(): a(3), b(2) {}
    void set(double a1, double b1)
    {
        a = a1;
        b = b1;
        cout << "a = " << a << ", b = " << b << endl;
    }
    void calculate()
    {
        cout << "a^b = " << pow(a, b) << endl << endl;
    }
};

//задание 2

void enter(string color, int &e)       //проверка ввода
{
    int e1;
 restart:                              //точка возврата
    setlocale(0, "");
    cout << "enter " << color << ": ";
    cin >> e1;
    if (!(e1 >= 0 && e1 <= 255))
    {
        cout << "число должно находиться в диапазоне от 0 до 255" << endl;
        goto restart;
    }
    e = e1;
}

void getvalues(int& r, int& g, int& b, int& a)      //перенёс функцию ввода из main, чтобы упростить код
{
    int r1, g1, b1, a1;
    enter("red", r1);
    r = r1;
    enter("green", g1);
    g = g1;
    enter("blue", b1);
    b = b1;
    enter("alpha", a1);
    a = a1;
}

class RGBA
{
private:
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;
public:
    RGBA() 
    {
        m_red = 0; m_green = 0; m_blue = 0; m_alpha = 255;
    }
    RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        m_red = r;
        m_green = g;
        m_blue = b;
        m_alpha = a;
    }
    void print()
    {
        cout << "red = " << (int)m_red <<
            ", green = " << (int)m_green <<
            ", blue = " << (int)m_blue <<
            ", alpha = " << (int)m_alpha << endl << endl;
    }
};

//задание 3

class Stack
{
private:
    int intarr[10];
    int length;
public:
    void reset()        //обнуляем
    {
        length = 0;
        for (int i = 0; i < 10; ++i)    
            intarr[i] = 0;
    }
    bool push(int n)    //добавляем
    {
        if (length == 9)
            return false;

        intarr[length] = n;
        ++length;
        return true;
    }
    void pop()          //удаляем
    {
        if (length == 0)
        {
            cout << "stack is empty!\n";
            return;
        }
        --length;
        intarr[length] = 0;
    }
    void print()        //выводим
    {
        cout << "( ";
        for (int i : intarr)    //используем цикл foreach
        {
            if (i != 0)
                cout << i << " ";
        }
        cout << ")"<<endl;
    }
};

int main()
{
    //задание 1
    
    Power power;
    power.set(5.2, 4.7);
    power.calculate();
    
    //задание 2

    int r, g, b, a;
    getvalues(r, g, b, a);
    RGBA rgba(r,g,b,a);
    rgba.print();
    
    //задание 3

    Stack stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

    return 0;
}