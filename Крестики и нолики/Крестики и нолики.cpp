#include <iostream>
#include <random>
#include <thread>

using namespace std;         

enum Cell:char
{
    CROSS= 'X',
    ZERO='O',
    EMP=' '
};

enum Progress:short int
{
    IN_GAME,
    WON_PLAYER,
    WON_PC,
    DRAW
};

struct Coord
{
    //я два часа не мог понять, почему компьютер читерит и иногда заменяет мой символ на свой. Оказалось, перепутал координаты
    short int y=0;
    short int x=0;
};

#pragma pack(push,1)
struct Game
{
    Cell** field = nullptr;
    const int SIZE=3;
    short int turn = 0;
    Cell player;
    Cell pc;
    Progress progress = IN_GAME;
};
#pragma pack(pop)

inline void clear()
{
    system("cls");
};

unsigned int getRandom()
{
    //используем вихрь Мерсенна
    random_device rd;
    mt19937 random(rd());
    return random();
};

void __fastcall initGame(Game& g)
{
    g.field = new Cell * [g.SIZE];
    for (int i = 0; i < g.SIZE; ++i)
        g.field[i] = new Cell[g.SIZE];

    for (int y = 0; y < g.SIZE; ++y)
        for (int x = 0; x < g.SIZE; ++x)
            g.field[y][x] = EMP;

    if (getRandom() % 1000 > 500)
    {
        g.player = CROSS;
        g.pc = ZERO;
        g.turn = 0;
    }
    else
    {
        g.player = ZERO;
        g.pc = CROSS;
        g.turn = 1;
    }
};

void __fastcall deinitGame(Game& g)
{
    for (int i = 0; i < g.SIZE; ++i)
        delete[] g.field[i];
    delete[] g.field;
    g.field = nullptr;
}

Coord getPlayerCoord(Game& g)
{
    setlocale(0, "");
    Coord c;
    do
    {
        cout << "Введите столбец: ";
        cin >> c.x;
        cout << "Введите строку: ";
        cin >> c.y;
    } while (c.x <= 0 || c.x > 3 || c.y <= 0 || c.y > 3 || g.field[c.y - 1][c.x - 1] != EMP);
    
    --c.y;
    --c.x;
    return c;
};



Progress getWon(const Game& g)
{
    for (int y = 0; y < g.SIZE; ++y)    //анализ строк
    {
        if (g.field[y][0] == g.field[y][1] && g.field[y][1] == g.field[y][2])
        {
            if(g.field[y][0]==g.player)
                return WON_PLAYER;

            if (g.field[y][0] == g.pc)
                return WON_PC;
        }
    }

    for (int x = 0; x < g.SIZE; ++x)    //анализ столбцов
    {
        if (g.field[0][x] == g.field[1][x] && g.field[1][x] == g.field[2][x])
        {
            if (g.field[0][x] == g.player)
                return WON_PLAYER;

            if (g.field[0][x] == g.pc)
                return WON_PC;
        }
    }

    //диагонали
    if (g.field[0][0] == g.field[1][1] && g.field[1][1] == g.field[2][2])
    {
        if (g.field[0][0] == g.player)
            return WON_PLAYER;

        if (g.field[0][0] == g.pc)
            return WON_PC;
    }

    if (g.field[0][2] == g.field[1][1] && g.field[1][1] == g.field[2][0])
    {
        if (g.field[1][1] == g.player)
            return WON_PLAYER;

        if (g.field[1][1] == g.pc)
            return WON_PC;
    }

    //проверка на ничью
    int number = 0;
    for (int y = 0; y < g.SIZE; ++y)
        for (int x = 0; x < g.SIZE; ++x)
            if(g.field[y][x] == EMP)
                ++number;
    if (number == 0)
        return DRAW;

    return IN_GAME;
};

Coord getPCCoord(const Game& g)
{
    //проверка на выигрышное положение обоих сторон
    for (short int y = 0; y < g.SIZE; ++y)
    {

        for (short int x = 0; x < g.SIZE; ++x)
        {
            if (g.field[y][x] == EMP)
            {
                g.field[y][x] = g.player;       //комп подсматривает в будущее
                if (getWon(g) == WON_PLAYER)
                {
                    g.field[y][x] = EMP;        
                    return { y, x };
                }
                g.field[y][x] = g.pc;           //комп тихо делает ход, 
                if (getWon(g) == WON_PC)        //смотрит на свою ситуацию
                {
                    g.field[y][x] = EMP;
                    return { y, x };            //и радостно возвращает победную ячейку, либо вздыхает и продолжает искать свободную ячейку 
                }
                g.field[y][x] = EMP;            //чтобы никто не понял, что комп жульничает
            }
        }
    }

    if (g.field[1][1] == EMP)       //центр
        return { 1,1 };

    Coord arr[8];
    int num = 0;

    if (g.field[0][0] == EMP)       //углы
    {
        arr[num] = { 0,0 };
        ++num;
    }
    if (g.field[2][2] == EMP)
    {
        arr[num] = { 2,2 };
        ++num;
    }
    if (g.field[0][2] == EMP)
    {
        arr[num] = { 0,2 };
        ++num;
    }
    if (g.field[2][0] == EMP)
    {
        arr[num] = { 2,0 };
        ++num;
    }

    if (num > 0)
    {
        const int index = getRandom() % num;
        return arr[index];
    }


    if (g.field[0][1] == EMP)       //не углы
    {
        arr[num] = { 0,1 };
        ++num;
    }
    if (g.field[1][0] == EMP)
    {
        arr[num] = { 1,0 };
        ++num;
    }
    if (g.field[1][2] == EMP)
    {
        arr[num] = { 1,2 };
        ++num;
    }
    if (g.field[2][1] == EMP)
    {
        arr[num] = { 2,1 };
        ++num;
    }

    if (num > 0)
    {
        const int index = getRandom() % num;
        return arr[index];
    }
    return {};
};

void __fastcall printGame(const Game& g)
{
    setlocale(0, "");
    cout << "    ";
    for (int x = 0; x < g.SIZE; ++x)
        cout << x + 1 << "   ";
    cout << endl;

    for (int y = 0; y < g.SIZE; ++y)
    {
        cout << y + 1 << " | ";
        for (int x = 0; x < g.SIZE; ++x)
            cout << g.field[y][x] << " | ";
        cout << endl;
    }
    cout << endl << "Вы играете: " << g.player << endl << "Компьютер: " << g.pc<<endl<<endl;
};

void noWin(Game& g)
{
    setlocale(0, "");
    clear();
    std::this_thread::sleep_for(1000ms);
    cout << "    ";
    for (int x = 0; x < g.SIZE; ++x)
        cout << x + 1 << "   ";
    cout << endl;

    for (int y = 0; y < g.SIZE; ++y)
    {
        cout << y + 1 << " | ";
        for (int x = 0; x < g.SIZE; ++x)
            cout << g.pc << " | ";
        cout << endl;
    }
    cout << endl << "ты не выиграешь, человек";
};

void congrats(Game &g)
{
    if (g.progress == WON_PLAYER)
        noWin(g);

    if (g.progress == WON_PC)
        cout << "Вы проиграли)";

    if (g.progress == DRAW)
        cout << "Ничья(";
};

int main()
{
start:
    Game g;
    initGame(g);
    clear();
    printGame(g);

    do
    {
        //ход игрока
        if (g.turn%2 == 0)   
        {
            Coord c = getPlayerCoord(g);
            g.field[c.y][c.x] = g.player;
        }
        //ход компьютера
        else
        {
            Coord c = getPCCoord(g);
            g.field[c.y][c.x] = g.pc;
            std::this_thread::sleep_for(1000ms);
        }
        clear();
        printGame(g);
        g.progress = getWon(g);
        ++g.turn;
    } while (g.progress == IN_GAME);

    congrats(g);

    short int again;
    do
    {
        cout << endl << endl << "ещё разок?)" << endl << "1 - да, 2 - нет: ";
        cin >> again;
    } while (again != 1 && again != 2);

    if (again == 1)
        goto start;

    deinitGame(g);
    return 0;
}
