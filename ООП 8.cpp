#include <iostream>
#include <thread>

using namespace std;

template <typename T1, typename T2>

//задание 1

void Div(T1 a, T2 b)
{
    try
    {
        if (b == 0)
            throw - 1;

        cout << (a / b) << endl;
    }
    catch (int)
    {
        cout << "Деление на ноль!\n\n";
    }
}

//задание 2

class Ex
{
    double x;
public:
    Ex(double num) : x(num) {};
};

class Bar
{
    double y;
public:
    Bar() : y(0) {}
    Bar(double num) : y(num) {};
    void set(double a)
    {
        try
        {
            if (y + a > 100)
                throw Ex(a * y);
            else
                y = a;
        }
        catch (Ex)
        {
            cout << "Ошибка: " << y << " + " << a << " > 100\n";
        }
    }
};

//задание 3

class Robot
{
    int x;
    int y;
public:
    Robot() :x(4), y(5) {};

    void move(int x1, int y1)       //двигаем робота
    {
        try
        {
            if (x+x1 <= 0 || x+x1 > 10 || y+y1 <= 0 || y+y1 > 10)
                throw -1;
            else
            {
                x += x1;
                y += y1;
            }
        }
        catch (int)
        {
            cout << "Ошибка: робот вышел за пределы поля!\n";
            this_thread::sleep_for(2000ms);
        }
    }

    void print()        //рисуем поле
    {
        system("cls");
        cout << "(для выхода введите 0, 0)\n";
        for (int i = 1; i <= 10; ++i)
        {
            for (int j = 1; j <= 10; ++j)
            {
                if (j == y && i == x)
                    cout << " X ";
                else
                    cout << " _ ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void play()     //запускаем игру
    {
        double x1;
        double y1;      //предотвращаем введение нецелых чисел

        print();

        do
        {
            cout << "Введите смещение по вертикали (-1,0,1): ";
            cin >> x1;

            cout << "Введите смещение по горизонтали (-1,0,1): ";
            cin >> y1;

            x1 = static_cast<int>(x1);
            y1 = static_cast<int>(y1);

            try
            {
                if (!((x1 == 1 || x1 == -1 || x1 == 0) && (y1 == 1 || y1 == -1 || y1 == 0)))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    throw - 1;
                }
                else
                    move(x1, y1);
            }
            catch (int)
            {
                cout << "Неверный ввод!\n";
                this_thread::sleep_for(2000ms);
            }
            print();

            cin.ignore(1000, '\n');
            cin.clear();
            
        } while (!(x1 == 0 && y1 == 0));
    }
};

int main()
{
    setlocale(0, "");
    //задание 1
    
    Div(16.4, 3);
    Div(7, 0);

    //задание 2

    Bar bar;
    int n;
    while (true)
    {
        try
        {
            cout << "Введите число: ";
            cin >> n;
            bar.set(n);
            if (n == 0)
                throw - 1;
        }
        catch (int)
        {
            cout << "Вы ввели ноль\n";
            break;
        }
    };
    cout << "\nДля перехода к заданию 3 введите что-нибудь\n";
    cin >> n;
    system("cls");

    //задание 3

    Robot R;
    R.play();

    return 0;
}

