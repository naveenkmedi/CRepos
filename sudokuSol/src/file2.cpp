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
		cout<<*itNum<<"\t";
	}
}
	cout<<endl;
}

void reinitVector(vector <int> *pv)
{	
	while(pv->size() != 0)
		pv->pop_back();
}
