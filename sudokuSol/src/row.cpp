#include "row.h"


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
						ip[row][col] = i; 
						reinitVector(&ve[row][col]);
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
	}
	mergeSolveRow(&v2[0]);
}
