#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void print(int* arr);

int shrinkedSize(vector<int> vRow)
{
	for(int num = 0; num < 9; num++)
	{
		int tempCount = count(vRow.begin(), vRow.end(), num);
		while(tempCount > 1)
		{
			vRow.erase(std::find(vRow.begin(), vRow.end(),num));
			tempCount--;
		}
	}
	return vRow.size();
}


int main()
{
// 	int arr[2][2] = {2,53,6,8};
// 	for(int j=0; j<2; j++)
// 		{
// 			print(&arr[j][0]);
// }

	std::vector<int> v;
	for(int i = 1; i< 9; i++)
	{
		v.push_back(i);
		v.push_back(i+1);				
	}


	cout<<shrinkedSize(v)<<endl;
// 	int pos = 0;
// 	for(int i = 0; i < 10; i++)
// 	{	
// 		pos = count(v.begin(), v.end(), i);
// 		cout<<"i = "<<i<<" pos = "<<pos<<"  ";
// 	}

// cout<<endl;
// 	for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
// 	{
// 		cout<<*it<"\t";
// 	}
// 	cout<<endl;

}



void print(int* arr)
{
	for(int i = 0; i < 2; i++)
	{
		{
			cout<<arr[i]<<"\t";			
		}
	}
			cout<<endl;

} 
