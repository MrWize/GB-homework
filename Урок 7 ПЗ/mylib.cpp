#include <iostream>

	namespace Arr
	{
		float array[10] = { -1,-3.5,-8,5,8,7.3,-9.2,1,0,-4 };

		void print()
		{
			for (int i = 0; i < 10; ++i)
				std::cout << array[i]<<" ";
		}

		void calc()
		{
			setlocale(0, "");
			int a=0, b=0;
			for (int i = 0; i < 10; ++i)
			{
				if (array[i] < 0)
					++a;
				else if (array[i] > 0)
					++b;
			}
			std::cout << "в массиве " << a << " отрицательных и " << b << " положительных чисел";
		}
	}
