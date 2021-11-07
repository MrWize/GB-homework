#include <iostream>

using namespace std;
//задание 1 

void task1()
{
	int n;

	cout << "Введите целочисленное значение: ";

	while (true)
	{
		cin >> n;

		if (cin.peek() == '\n')
		{
			cin.ignore(1000, '\n');
			break;
		}
		cin.clear();
		cout << "Введите целочисленное значение: ";
		cin.ignore(1000, '\n');
	}

	cout << "Ваше число: " << n << endl;
}

//задание 2

template<typename T1, typename T2>

inline basic_ostream<T1, T2>&

endll(basic_ostream<T1, T2>& os)
{
	return flush((os.put(os.widen('\n'))).put(os.widen('\n')));
}

void task2()
{
	cout << "строка 1" << endll;
	cout << "строка 2" << endll;
}

int main()
{
	setlocale(0, "");

	task1();

	task2();

	return 0;
}