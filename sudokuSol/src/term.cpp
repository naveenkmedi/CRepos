#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	cout<<"argc = "<<argc<<endl;

	for(int count = 0; count < argc; count++)
	{
		cout<<argv[count]<<endl;
	}

	return 0;
}