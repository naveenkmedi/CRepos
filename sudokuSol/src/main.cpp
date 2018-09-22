#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

#include "main.h"
#include "fileRead.h"


using namespace std;

int ip[9][9];
vector<int>  v[9][9];
vector<int>  ve[9][9];

void reinitVector(int row, int col);
void mergeColumn();
void mergeSovleColumn(vector<int> *v2);
void printVector(vector <int> *pv);
void updateVe(int row, int col, int num);
void populateVe(int row, int col);
void populateMaps();
void updateDependents(int row, int col);
void solve(int row, int column);
void printOutput();
void mergeSolveRow(vector <int> *v2);
void mergeRow();
void populatePoss();


void populateVe(int row, int col)
{
	for(int i = 1; i < 10; i++)
	{
		if(ip[row][col] != 0) continue;
		int iCount = count(v[row][col].begin(), v[row][col].end(), i);
		if(iCount == 0)
		{
			int rep = count(ve[row][col].begin(), ve[row][col].end(), i);
			if(rep != 0) continue;
			
			ve[row][col].push_back(i);
		}
	}

if(ip[row][col] != 0)
{
	for(int num = 1; num < 10; num++)
	{
		ve[row][col].push(num);
	}

	for(int num = 1; num < 10; num++)
	{
		//check if present in row
		for(int cCol = 0; cCol < 9; cCol++)
		{
			if(ip[row][cCol] != 0)
		//check row wise
			for(int cCol = 0; cCol < 9; cCol++)
			{
				if(cCol != col)
					if(0 != ip[row][cCol])
						if(0 == count(v[row][col].begin(), v[row][col].end(), ip[row][cCol]))
							v[row][col].push_back(ip[row][cCol]);
			}

}
	}
}

void populateMaps()
{
	for(int row = 0; row < 9; row++)
	{
		for(int col = 0; col < 9; col++)
		{
		//check row wise
			for(int cCol = 0; cCol < 9; cCol++)
			{
				if(cCol != col)
					if(0 != ip[row][cCol])
						if(0 == count(v[row][col].begin(), v[row][col].end(), ip[row][cCol]))
							v[row][col].push_back(ip[row][cCol]);
			}

			//column wise		
			for(int cRow = 0; cRow < 9; cRow++)
			{	if(cRow != row)
					if(0 != ip[cRow][col])
						if(0 == count(v[row][col].begin(), v[row][col].end(), ip[cRow][col]))
							v[row][col].push_back(ip[cRow][col]);
			}
			//block wise
			for(int i = 3*(row/3); i < 3*(row/3) + 3; i++)
			{
				if(i%3 != row%3) 
				{
					for(int j = 3*(col/3); j < 3*(col/3) + 3; j++)
					{
						if(j%3 != col % 3) 
						{
							if(0 != ip[i][j])
								if(0 == count(v[row][col].begin(), v[row][col].end(), ip[i][j]))
									v[row][col].push_back(ip[i][j]);
						}
					}
				}
			}
		}
	}
}

void reinitVector(int row, int col)
{	
	while(ve[row][col].size() != 0)
		ve[row][col].pop_back();
}

void updateVe(int row, int col, int num)
{
	if(ip[row][col] == 0)
	{
		//pop back 
		int tempCount = count(ve[row][col].begin(), ve[row][col].end(), num);
		if(tempCount == 1)
		{
			ve[row][col].erase(std::find(ve[row][col].begin(), ve[row][col].end(),num));
		}
	}
}

void updateDependents(int row, int col)
{
	//row 1+ 8
	int	num = ip[row][col]; //find this element and remove from 
	for(int cCol = 0; cCol < 9; cCol++) 
	{	
		if(cCol == col) 
		{
			reinitVector(row, cCol);
		}

		else
		{
			updateVe(row, cCol, num);	
		}
	}

	for(int cRow = 0; cRow < 9; cRow++)
	{
		if(cRow != row)
		{
			updateVe(cRow, col, num);
		}
	}
	
	for(int i = 3*(row/3); i < 3*(row/3)+ 3; i++)
	{
		if(i%3 != row%3) 
		{
			for(int j = 3*(col/3); j < 3*(col/3) + 3; j++)
			{
				if(j%3 != col % 3) 
				{
					updateVe(i, j, num);
				}
			}
		}
	}
}

void solve(int row, int column)
{
	for(int count1 = 0; count1 < 9; count1++)
	{
		for(int count2 = 0; count2 < 9; count2++)
		{
			if(ip[count1][count2] == 0)
			{	
				if(ve[count1][count2].size() == 1)
				{
					vector<int>::iterator it = ve[count1][count2].begin();
					ip[count1][count2] = *it;
					reinitVector(count1, count2);
					updateDependents(count1, count2);
				}
			}
		}
	}
}

void printOutput()
{
	for(int count = 0; count < 9; count++)
	{
		for(int count2 = 0; count2 < 9; count2++)
		{
			cout<<ip[count][count2]<<" ";
			if(count2 % 3 == 2) cout<<" ";
		}
		cout<<"\n";
		if(count % 3 == 2) cout<<endl;
	}
}

void printVector(vector <int> *pv)
{
	vector<int>::iterator itNum = pv->begin();
	for(itNum; itNum != pv->end(); itNum++)
	{
		cout<<*itNum<<"\t";
	}
	cout<<endl;
}

void mergeSolveRow(vector <int> *v2)
{
	for(int row = 0; row < 9; row++)
	{
		for(int i = 1; i < 10; i++)
		{
			if(1 == count(v2[row].begin(),v2[row].end(), i))
			{
				//find which one has it
				for(int col = 0; col < 9; col++)
				{
					int possible = count(ve[row][col].begin(),ve[row][col].end(), i);
					if(1 == possible)
					{
						//found
						ip[row][col] = i; 
						reinitVector(row,col);
						updateDependents(row, col);
					}
				}
			}
		}	
	}
}

void mergeRow()
{
	vector<int> v2[9];
	for(int row = 0; row < 9; row++)
	{
		v2[row].clear();
		for(int col = 0; col < 9; col++)
		{
			v2[row].insert(v2[row].end(), ve[row][col].begin(), ve[row][col].end());
		}
		//rowSolve(row);
	}
	mergeSolveRow(&v2[0]);
}

void populatePoss()
{
	for(int row = 0; row < 9; row++)
	{
		for(int col = 0; col < 9; col++)
		{
			populateVe(row, col);
		}
	}
}


int main()
{	
	if(0 == readFile())
	{
		populateMaps();
		populatePoss();

		for(int i = 0; i < 5; i++)
		{
			solve(1,1);
			mergeRow();
		}
		printOutput();
	}
}