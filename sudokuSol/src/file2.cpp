#include "file2.h"

void printVector(vector <int> *pv)
{
	if(pv->size() == 0)
		cout<<"empty";
	else
	{
	vector<int>::iterator itNum = pv->begin();
	for(itNum; itNum != pv->end(); itNum++)
	{
		cout<<*itNum<<"  ";
	}
}
	cout<<endl;
}

void reinitVector(vector <int> *pv)
{	
	while(pv->size() != 0)
		pv->pop_back();
}

void printOutput()
{
	int zeroes = 0;
	for(int count = 0; count < 9; count++)
	{
		for(int count2 = 0; count2 < 9; count2++)
		{
			cout<<ip[count][count2]<<" ";
			if(0 == ip[count][count2])
				{zeroes++;}
			if(count2 % 3 == 2) cout<<" ";
		}
		cout<<"\n";
		if(count % 3 == 2) cout<<endl;
	}

	cout<<"unsolved = "<<zeroes<<endl;
}
