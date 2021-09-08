#include <iostream>
using namespace std;
int main()
{
    // задание 1
    short int q1 = 20000;
    int q2 = 1;
    long long q3 = 123'456'789'101'112;
    char q4 = 'w';
    bool q5 = true;
    float q6 = 3.14f;
    double q7 = 2.7e10;

    // задание 2 
    enum Game
    {
        CROSS = 'x',
        CIRCLE = 'o',
        EMPTY = '.'
    };

    // задание 3
    char mygame[3][3];
    for (int a = 0; a <= 2; a++)    // немного заморочился, чтобы вышло красиво =)
    {
        for (int b = 0; b <= 2; b++)
        {
            int r = rand() % 2;     // кидаем монетку и получаем значение для матрицы
            if (r == 0)
                mygame[a][b] = CROSS;
            else mygame[a][b] = CIRCLE;
            cout << mygame[a][b] << " ";
        };
        cout << endl;   // делаем три строки
    };

    // задание 4
    struct TTT
    {
        char line1[3];
        char line2[3];
        char line3[3];
    };
         
    return 0;
}
