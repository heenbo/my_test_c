#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	enum DIRECT{UP, DOWN, LEFT, RIGHT};
	
	//DIRECT d = 66;
	DIRECT d = UP;

	cout << "d = " << d << endl;
	
	return 0;
}
