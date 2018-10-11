#include <iostream>
#include <string>
#include <fstream>
#include "main.h"
#include "fileRead.h"

using namespace std;

int readFile(char* fileName)
{
	string line;

	int i=0; 
	int j=0;
	//fileName.append() = "14c.txt";
	// const char* fileName1 = fileName.c_str();
	ifstream ipFile(fileName);

	
	if(ipFile.is_open())
  	{
  		cout<<"input file name - "<<fileName<<"	\n";
	    while (getline(ipFile, line) )
	    {
	    	std::string::iterator it;
	    	for(it = line.begin(); it != line.end(); it++)
	      	{
	      		if(*it>=48 && *it <= 57 )
	      		{
	      			ip[i][j] =  (*it)-48;
	      			j++;
	      			if(j == 9)
	      			{
	      				j = 0;	      				 
	      				i++;
	      				if(i==9)
	      				{
	      					cout<<"considering only first 81 inputs\n";
						    ipFile.close();
						    return 0;	      				
						}
	      			}
	      		}
	         }
	    }
	    ipFile.close();
	    return 0;
  	}			
  	cout<<"input file error\n";
  	return 1;
}
