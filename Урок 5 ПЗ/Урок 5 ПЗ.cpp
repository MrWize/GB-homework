#include <iostream>
using namespace std;

//функция к заданию 1
void task1 (double *array, int size)
{
    for (int i = 0; i < size; ++i)
        cout << array[i]<<" ";    
}

//функция к заданию 2
void task2(int *array, int size)
{
    for (int i = 0; i < size; ++i)
        (array[i] == 0) ? (array[i] = 1) : (array[i] = 0);
}

//функция к заданию 3
void task3(int *array, int size)
{
    int n = 1;
    for (int i = 0; i < size; ++i)
    {
        array[i]=n;
        cout << array[i]<<" ";
        n += 3;
    }
}

//функция к заданию 4*
void task4(int* array, int sdvig)
{
    int arraycopy[10];
    for (int i = 0; i < 10; ++i)
        arraycopy[i] = array[i];    //делаем копию, чтобы не потерять

    int *p1;    

    if (sdvig < 0)                  //сдвиг влево
    {
        sdvig = -sdvig;
        p1 = &arraycopy[0];
        for (int i = 0; i < (10-sdvig); ++i)
        {
            array[i] = *(p1 + sdvig);
            ++p1;
            cout << array[i]<<" ";
        }
        p1 = &arraycopy[0];
        for (int i = (10-sdvig); i < 10; ++i)
        {
            array[i] = *(p1);
            ++p1;
            cout << array[i] << " ";
        }
    }

    else                            //сдвиг вправо
    {
        p1 = &arraycopy[0];
        for (int i = 0; i < sdvig; ++i)
        {
            array[i] = *(p1 + 10 - sdvig);
            ++p1;
            cout << array[i] << " ";
        }
        p1 = &arraycopy[0];
        for (int i = sdvig; i < 10; ++i)
        {
            array[i] = *(p1);
            ++p1;
            cout << array[i] << " ";
        }
    }
    //наверное, это можно было сделать проще...
}

//функция к заданию 5***
void task5(int *array, int size)
{

    for (int i = 0; i < size; ++i)
    {
        int a = 0, b = 0;                    
        for (int j1 = 0; j1 < i; ++j1)             //сумма слева
            a = a + array[j1];

        for (int j2 = i; j2 < size; ++j2)          //сумма справа
            b = b + array[j2];

        if (a == b)                                //делаем красивый вывод
        {
            for (int t1 = 0; t1 < i; ++t1)
                cout << array[t1] << " ";

            cout<<"|| ";                            //абстрактная граница

            for (int t2 = i; t2 < size; ++t2)
                cout << array[t2] << " ";

            cout <<" -true"<< endl;
            return;
        }
        
    }
    for (int t = 0; t < size; ++t)
        cout << array[t] << " ";

    cout << "    -false" << endl;
}

int main()
{   
    //задание 1
    double arr1[3] = { 1.1, 2.2, 3.3 };
    task1(arr1, 3);
    cout << endl << endl;

    //задание 2
    int arr2[10] = { 1,0,1,0,1,0,1,1,1,1 };
    for (int i = 0; i < 10; ++i)
        cout << arr2[i] << " ";     //до
    cout << endl;
    task2(arr2, 10);
    for (int i = 0; i < 10; ++i)
        cout << arr2[i] << " ";     //после
    cout << endl << endl;

    //задание 3
    int arr3[8];
    task3(arr3, 8);
    cout << endl << endl;

    //задание 4*
    setlocale(0, "");
    int arr4[10] = {1,2,3,4,5,6,7,8,9,10};
    cout << "исходный массив:\n";
    for (int i = 0; i < 10; ++i)
        cout << arr4[i] << " ";
    int n;
    cout << endl;
    zeropoint:
    cout << "введите сдвиг массива (n<0 - влево, n>0 - вправо): ";
    cin >> n;
    if ((n == 0)||(n<-10)||(n>10))
    {
        cout << "попробуйте ещё раз\n";
        goto zeropoint;
    }
    task4(arr4,n);
    cout << endl << endl; 

    //задание 5***
    int arr5_1[10], arr5_2[10], arr5_3[10], arr5_4[10], arr5_5[10], arr5_6[10], arr5_7[10], arr5_8[10], arr5_9[10], arr5_10[10];

    //делаем 10 рандомных массивов из единиц и двоек, чтобы проверить программу
    for (int i = 0; i < 10; i++)                                  
    {
        arr5_1[i] = rand() % 2 + 1;
        arr5_2[i] = rand() % 2 + 1;
        arr5_3[i] = rand() % 2 + 1;
        arr5_4[i] = rand() % 2 + 1;
        arr5_5[i] = rand() % 2 + 1;
        arr5_6[i] = rand() % 2 + 1;
        arr5_7[i] = rand() % 2 + 1;
        arr5_8[i] = rand() % 2 + 1;
        arr5_9[i] = rand() % 2 + 1;
        arr5_10[i] = rand() % 2 + 1;
    }
    task5(arr5_1, 10);
    task5(arr5_2, 10);
    task5(arr5_3, 10);
    task5(arr5_4, 10);
    task5(arr5_5, 10);
    task5(arr5_6, 10);
    task5(arr5_7, 10);
    task5(arr5_8, 10);
    task5(arr5_9, 10);
    task5(arr5_10, 10);

    return 0;
}