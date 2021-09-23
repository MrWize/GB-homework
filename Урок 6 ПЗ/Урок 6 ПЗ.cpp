#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

//функция к заданию 1
void task1(int size)
{
	int* array = new int[size];
	int a = 1;
	for (int i = 0; i < size; ++i)
	{
		array[i] = a;
		cout << array[i] << " ";
		a *= 2;
	}
	delete[] array;
}

//функция к заданию 2
void task2()
{
	int** array = new int* [4];
	for (int i = 0; i < 4; ++i)		//объявляем двумерный динамический массив
		array[i] = new int[4];

	for (int i1 = 0; i1 < 4; ++i1)	//заполняем рандомными числами и выводим
	{
		for (int i2 = 0; i2 < 4; ++i2)
		{
			array[i1][i2] = rand() % 100;
			cout << array[i1][i2] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < 4; ++i)		//удаляем массив
		delete[] array[i];
}

//функция к заданию 4
void task4(string n1, string n2, string n3)
{
	ofstream f3(n3);

	ifstream fi1(n1);
	string read1;
	getline(fi1, read1);

	ifstream fi2(n2);
	string read2;
	getline(fi2, read2);

	f3 << read1 + read2;			//помещаем в файл 3 содержимое 1 и 2
	cout << "файл 3 создан!\n\n";
	f3.close();
}

//функция к заданию 5
void task5(string name, string word)
{
	ifstream file(name);
	string fcopy;
	getline(file, fcopy);

	if (fcopy.find(word) != string::npos)
		cout << "слово найдено!\n";
	else
		cout << "слово не найдено(\n";
}



int main()
{
	setlocale(0, "");				//подключаем российский язык
	
	//задание 1
	int n1;
	cout << "введите размер массива: ";
	cin >> n1;
	task1(n1);
	cout << endl << endl;
	
	//задание 2
	task2();
	cout << endl << endl;
	
	//задание 3
	cout << "введите имя файла 1: ";
	string name1;
	cin.ignore(10000, '\n');		//удаляем символ новой строки, захваченный cin
	getline(cin, name1);
	string txt = ".txt";
	name1 += txt;					//дописываем расширение
	ofstream f1(name1);
	f1 << "Prince Vasili's daughter, the beautiful Helene, came to take her father to the ambassador's entertainment. ";
	cout << "файл 1 создан!\n";
	f1.close();

	cout << "введите имя файла 2: ";
	string name2;
	getline(cin, name2);
	name2 += txt;					//дописываем расширение
	ofstream f2(name2);
	f2 << "She wore a ball dress and her badge as maid of honor.";
	cout << "файл 2 создан!\n\n";
	f2.close();
	
	
	//задание 4
	cout << "введите имя файла 3, в который будут помещены ф.1 и ф.2: ";
	string name3;
	getline(cin, name3);
	name3 += ".txt";				//дописываем расширение
	task4(name1,name2,name3);

	//задание 5
	cout << "укажите файл, в котором будем искать слово (1, 2, 3): ";
	int number;
restart:

	cin >> number;
	if ((number != 1) && (number != 2) && (number != 3))
	{
		cout << "выберите 1, 2 или 3: ";
		goto restart;
	}

	string word;
	cout << "введите слово, которое будем искать: ";
	cin.ignore(10000, '\n');		//удаляем символ новой строки, захваченный cin
	getline(cin, word);

	switch (number)
	{
	case 1:
		task5(name1, word);
		break;
	case 2:
		task5(name2, word);
		break;
	case 3:
		task5(name3, word);
		break;
	}
	
	return 0;
}
