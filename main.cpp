#include "src/大数类.h"

int main()
{

	BigInteger x, y, z;
	int k = 0;
	cout << "Please input two nonegative integers, separated by space, then press enter\n";
	while (cin >> x >> y)
	{
		cout << "Case " << k++ << " :\n";
		z = x + y;
		cout << "和: " << z << endl;
		z = x - y;
		cout << "差: " << z << endl;
		z = x * y;
		cout << "积: " << z << endl;
		cout << "> : " << (x > y) << endl;
		cout << "< : " << (x < y) << endl;
		cout << ">= : " << (x >= y) << endl;
		cout << "<= : " << (x <= y) << endl;
		cout << "!= : " << (x != y) << endl;
	}
	return 0;
}

