#include <iostream>
#include "mylib.h"
#include <string>
#include <fstream>
//к заданию 2
#define task2(a,b)	\
if (((0 <= a) && (a < b)) || ((b < a) && (a <= 0)) || ((a == 0) && (b == 0)))	\
	cout << a << " находится между 0 и " << b << " (true)";		\
else cout << a << " НЕ находится между 0 и " << b << " (false)";

//к заданию 3
#define SIZE 10
#define SwapInt(a,b) {int c;c=a;a=b;b=c;}

void qsort(int *arr, int left, int right)		//быстрая сортировка
{
	int l = left;
	int r = right;
	int mid = arr[(l+r)/2];		//выбираем опорное значение
	do
	{
		while ((arr[l] < mid)&&(l<right))	
			++l;
		while ((arr[r] > mid)&&(r>left))
			--r;
		if (l <= r)
		{
			SwapInt(arr[l], arr[r]);
			++l;
			--r;
		}
	} while (l <= r);

	if (left < r)		//вызываем рекурсию
		qsort(arr, left, r);
	if (l < right)
		qsort(arr, l, right);
}



using namespace std;
int main()
{
	setlocale(0, "");
	
	//задание 5*(1)
	Arr::print();
	cout << endl;

	Arr::calc();
	cout << endl << endl;
	
	int a1, b1;
	cout << "введите ваше число: ";
	cin >> a1;
	cout << "введите диапазон: ";
	cin >>b1;

	//задание 2
	task2(a1,b1);
	cout << endl << endl;
	
	//задание 3
	int array[SIZE];
	cout << "введите " << SIZE << " целочисленных значений: " << endl;
	for (int i = 0; i < SIZE; ++i)
		cin >> array[i];

	qsort(array,0,SIZE-1);
	cout << "(отсортировано) ";

	for (int i = 0; i < SIZE; ++i)
		cout << array[i]<<" ";
		cout<<endl<<endl;

	//задание 4
#pragma pack(push,1)
		struct Employee
		{
			string name;
			int age;
			double heght;
			char blood;
			bool gender;

		};
#pragma pack(pop)

	auto *Daniil = new Employee;
	*Daniil = { "Daniil", 21, 172.5,'A',1 };
	string txt="HW7.txt";
	ofstream file(txt);
	file << Daniil->name << endl << Daniil->age << endl << Daniil->heght << endl << Daniil->blood << endl << Daniil->gender;
	cout << Daniil->name << endl << Daniil->age << endl << Daniil->heght << endl << Daniil->blood << endl << Daniil->gender<<endl;
	cout << "размер структуры: " << sizeof(Employee) << endl;

	file.close();
	delete Daniil;

	return 0;
}
