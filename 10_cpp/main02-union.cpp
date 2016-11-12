#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	union
	{
		int num;
		char buf[4];
	};

	num = 0x12345678;
	
	for(int i = 0; i <4; i ++)
	{
		cout << "buf[" << i << "] = " << buf[i] << ' ';
	}	

	cout << endl;
	return 0;
}
