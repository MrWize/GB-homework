#include <iostream>
using namespace std;

void vis()  //функция к заданию 5
{
    cout << "этот год високосный!";
};

void novis()  //функция к заданию 5
{
    cout << "этот год не високосный!";
};

int main()
{                 
    setlocale(0, "");   //русский язык

    //задание 1
        cout << "введите первое число: ";
        double a1;
        cin >> a1;

        cout << "введите второе число: ";
        double b1;
        cin >> b1;

        if ((a1 + b1 >= 10) && (a1 + b1 <= 20))
        {
            cout << "true" << endl;
        }
        else
        {
            cout << "false" << endl;
        }

    //задание 2
        cout << "введите первое целое число: ";
        int a2;
        cin >> a2;

        cout << "введите второе целое число: ";
        int b2;
        cin >> b2;

        if ((a2==10 && b2==10) || (a2+b2==10))
        {
            cout << "true" << endl;
        }
        else
        {
            cout << "false" << endl;
        }

    //задание 3
        int a3 =1;
        cout << "ряд нечётных чисел: ";
        while (a3 <= 50)
        {
            if (a3 % 2 == 1)
            {
                cout << a3 << " ";
            }
            ++a3;
        }
        cout << endl;       
        
    //задание 4
        cout << "введите целое положительное число: ";
        int a4;
        cin >> a4;

        if (a4== 1)
        {
            cout << "ваше число простое!" << endl;
        }

        for (int i = 2; i < a4; ++i)
        {
            if (a4 % i == 0)
            {
                cout << "ваше число делится на "<<i << endl;
                break;
            }
            if (a4 - i == 1)
            {
                cout << "ваше число простое!" << endl;
                break;
            }
        }
        
    //задание 5
        cout << "введите год (от 1 до 3000): ";
        int a5;
        vvod:   //точка возврата
        cin >> a5;
        if ((a5 < 1) || (a5 > 3000))
        {
            cout << "прочтите ещё раз условие =)" << endl;
            goto vvod;
        }

        if (a5 % 4 == 0)
        {
            if (a5 % 100 == 0)
            {
                if (a5 % 400 == 0)
                {
                    vis();
                }
                else
                {
                    novis();
                }
            }
            else
            {
                vis();
            }
        }
        else
        {
            novis();
        }

    return 0;
}
