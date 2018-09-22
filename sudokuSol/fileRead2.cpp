#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	int a = 0;
	for (int i = 0; i < argc; ++i) 
        cout << argv[i] << "\t"; 
    cout<<argc<<" - arguments\n";
  

	string line;
	//ifstream myfile("/home/vinn-naveen/Desktop/nav.txt");//myfile.txt");
	ifstream myfile("myfile.txt");

	if(myfile.is_open())
	{
		while(getline(myfile, line))
		{
	    std::string::iterator it; 
	    for(it = line.begin(); it != line.end(); it++)
	    {
	    	if(*it >= 48 && *it <=57)
	    	{ 
	    		a = *it;
	    		cout<<*it;
	    	}
		}
		cout<<endl;
	}
	}
    cout<<endl;
	return 0;
}