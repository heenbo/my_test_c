//============================================================================
// Name        : cpp-test01.cpp
// Author      : heenbo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

using namespace std;

struct Person
{
		string name;
		int age;

		void show()
		{
			cout << "okokokokok" << endl;
		}
};

int main(void)
{
	struct Person p = {"贺恩波", 24};

	p.show();

	return 0;
}
