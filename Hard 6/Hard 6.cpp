#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>
#include <vector>
#include <windows.h>    //для очистки экрана
#include <string>
#include <sstream>

using namespace std;

//задание 1

class Pcout : public ostringstream
{
private:
    static mutex mpcout;
public:
    Pcout() = default;

    ~Pcout()
    {
        lock_guard<mutex> guard(mpcout);
        cout << this->str();
    }
};

mutex Pcout::mpcout{};

void printPcout1()
{
    for (int i = 0; i < 10; ++i)
        Pcout{} << "11111" << " 111" << " 11111\n";
}

void printPcout2()
{
    for (int i = 0; i < 10; ++i)
        Pcout{} << "  2222" << " 2" << " 2222\n";
}

//задание 2

void print(int& progress, int simplenum, int &num)
{
    system("cls");
    while (progress < simplenum)
    {
        this_thread::sleep_for(100ms);      //решение проблемы, когда компилятор не досчитывает до конца несколько значений (99996 из 100000)

        //system("cls");
        HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);    //устраняем мерцание при system("cls") по инструкции с интернета
        COORD cd;
        cd.X = 0;
        cd.Y = 0;
        SetConsoleCursorPosition(hd, cd);
            
        cout << "Прогресс: " << progress << " / " << simplenum << "\nПростое число: " << num;
    };
}

void simple(int& progress, int simplenum,int &num)
{
    bool check;

    while (progress < simplenum)
    {
        check = false;
        ++num;
        if (num % 2 != 0)   //проверка на простое число
        {
            for (int k = 3; k <= (int)sqrt(num); k += 2)
            {
                if (num % k == 0)
                    check = true;
            }
        }
        else if (num != 2 && num % 2 == 0)
            check = true;

        if (check == false) 
            ++progress;
    };

};

//задание 3

void add(vector<int>& vec)
{
    for (int i = 0; i < 10; ++i)
    {
        int r = rand() % 30 + 1;

        vec.push_back(r);
        cout << "Хозяин принёс: " << r << endl;

        this_thread::sleep_for(1000ms);
    }
};

void steal(vector<int>& vec)
{
    for (int i = 0; i < 9; ++i)
    {
        this_thread::sleep_for(1500ms);

        int max = 0;
        vector<int>::iterator itmax;
        if (vec.size() > 0)
        {
            for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
                if (max < *it)
                {
                    max = *it;
                    itmax = it;
                };

            *itmax = 0;
            cout << "Вор украл: " << max << endl;
        }
    }
};

int main()
{
    setlocale(0, "");

    //задание 1

    thread t1(printPcout1);
    thread t2(printPcout2);
    t1.join();
    t2.join();
    
    //задание 2

    cout << "\nДля перехода к заданию 2 нажмите Enter";
    if (cin.get() == '\n')
        system("cls");

    int simplenum;
    cout << "Введите номер простого числа: ";
    cin >> simplenum;

    int progress = 0;
    int num=1;

    thread th2{ simple, ref(progress), simplenum ,ref(num) };
    th2.detach();
    thread th1{ print, ref(progress), simplenum ,ref(num) };
    th1.join();

    //задание 3

    cout << "\n\nДля перехода к заданию 3 нажмите Enter";
    char enter;
    enter = cin.get();
    if (cin.get() == '\n') 
        system("cls");

    vector<int> goods;
    thread thr1(add, ref(goods));
    thread thr2(steal, ref(goods));
    thr1.join();
    thr2.join();
}
