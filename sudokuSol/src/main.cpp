#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

#include "main.h"

using namespace std;

int ip[9][9];
vector<int> ve[9][9];


vector<int> shrinkVector(vector<int> v)
{
	for(int num = 1; num < 10; num++)
	{
		int tempCount = count(v.begin(), v.end(), num);
		while(tempCount > 1)
		{
			v.erase(std::find(v.begin(), v.end(),num));
			tempCount--;
		}
	}
	return v;
}


void checkVe(int row, int col)
{
	if(ve[row][col].size() == 1)
	{
		if(ip[row][col] == 0)
		{
			std::vector<int>::iterator it = ve[row][col].begin();
			ip[row][col] = *it;
			ve[row][col].pop_back();
			updateDependents(row, col);
		}
	}
}

int shrinkedSize(vector<int> vRow)
{
	for(int num = 1; num < 10; num++)
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


void populatePoss()
{
	for(int row =0; row<9; row++)
	{
		for(int col = 0; col < 9; col++)
		{
			if(ip[row][col] == 0)
			{
					//initiate with 1-9
				for(int num = 1; num < 10; num++)
				{
					ve[row][col].push_back(num);
				}
					//check if present in row
				for(int cCol = 0; cCol < 9; cCol++)
				{			
					if(ip[row][cCol] != 0)
					{
						if(cCol != col)
						{	
							if(0 < count(ve[row][col].begin(), ve[row][col].end(), ip[row][cCol]))		
							ve[row][col].erase(std::find(ve[row][col].begin(), ve[row][col].end(), ip[row][cCol]));
						}	
					}	
				}

				//check if present in column
				for(int rRow = 0; rRow < 9; rRow++)
				{
					if(ip[rRow][col] != 0)
					{
						if(rRow != row)
						{	
							if(0 < count(ve[row][col].begin(), ve[row][col].end(), ip[rRow][col]))
								ve[row][col].erase(std::find(ve[row][col].begin(), ve[row][col].end(), ip[rRow][col]));
						}	
					}	
				}

				//check if present in block
				for(int cCol = (col/3)*3; cCol < (col/3)*3+3; cCol++)
				{
					for(int rRow = (row/3)*3; rRow < (row/3)*3 +3; rRow++)
					{
						if(ip[rRow][cCol] != 0)
						{
							if((rRow != row%3) && (cCol != col%3))
							{
								if(0 < count(ve[row][col].begin(), ve[row][col].end(), ip[rRow][cCol]))
									ve[row][col].erase(std::find(ve[row][col].begin(), ve[row][col].end(), ip[rRow][cCol]));
							}	
						}	
					}
				}
			}
		}		
	}
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
			reinitVector(&ve[row][col]);
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
					reinitVector(&ve[count1][count2]);
					updateDependents(count1, count2);
				}
			}
		}
	}
}


int main(int argc, char* argv[])
{	
	if(0 == readFile(argv[1]))
	{
		populatePoss();
		printOutput();

		for(int i = 0; i < 2; i++)
		{
			for(int row = 0; row < 9; row++)
			{
				solve(1,1);
				mergeRow();
				mergeColumn();
				mergeBlock();
				//rowSolve(row); //not yet working
				//columnSolve(row);
			}
		}	

		cout<<"after solving\n";
		printOutput();

		int arg = atoi(argv[2]);

		if(arg >= 1)
		{
			for(int i = 0; i < 5; i++)
			{
				for(int row = 0; row < 9; row++)
				{
					solve(1,1);
					mergeRow();
					mergeColumn();
					mergeBlock();

					if(arg >= 2)
					{
						columnSolve(row);
					}

					// if(arg >= 2)
					// {
						rowSolve(row); //not yet working
					// }
				}
			}
			cout<<"after row and column solving\n";
			printOutput();
		}	

		if(arg >= 3)
		{
			for(int repeat = 0; repeat <1; repeat++)
			{
				for(int i = 0; i < 3; i++)
				{
					for(int j = 0; j < 3; j++)
					{
						blockSolve(i, j); //not yet working
					}
				}
			}

			cout<<"after solving block\n";
			printOutput();
		}
	}
}