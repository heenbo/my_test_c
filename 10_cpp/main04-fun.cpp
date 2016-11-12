#include <iostream>
#include <string>
using namespace std;

void aaa(int a, char b)
{
	cout << "aaa" << endl;
}

void aaa(char a, int b)
{
	cout << "bbb" << endl;
}

int main(void)
{
	enum DIRECT{UP, DOWN, LEFT, RIGHT};
	
	//DIRECT d = 66;
	DIRECT d = UP;

	cout << "d = " << d << endl;

	aaa('c', 22);

	aaa(22, 'c');
	
	return 0;
}
