#include <iostream>
using namespace std;
extern int a;
extern int b;
extern int c;
extern int d;

int main()
{
	//задание 4(+1)
	cout << "a * (b + (c / d)) = "<< a * (b + ((float)c / d))<<endl;

	//задание 2
	int number;
	cout << "enter an integer: ";
	cin >> number;
	(number <= 21) ? (cout << "21 - " << number << " = " << 21 - number << endl)
		: (cout << "(" << number << " - 21) * 2 = " << (number - 21) * 2 << endl);

	//задание 3
	int kub[3][3][3];
	for (int k1 = 0; k1 < 3; ++k1)
	{
		for (int k2 = 0; k2 < 3; ++k2)
		{
			for (int k3 = 0; k3 < 3; ++k3)
			{
				//делаем массив из "случайных" чисел от 0 до 100
				kub[k1][k2][k3] = rand() % 100;
			}
		}
	}
	int* p;
	p = &kub[0][0][0];

	/* центр куба - ячейка kub[1][1][1], она 14-я по порядку,
	значит, к адресу первой ячейки нужно прибавить 13 */
	cout <<"center = " << *(p + 13) << endl;

	// проверка
	cout <<"center = " << kub[1][1][1];

	return 0;
}

