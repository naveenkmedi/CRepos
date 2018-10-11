#include "column.h"

void mergeSolveColumn(vector <int> *vc)
{
	int isSingle = 0;
	for(int col = 0; col < 9; col++)
	{
		for(int i = 1; i < 10; i++)
		{
			isSingle = 0;
			isSingle = count(vc[col].begin(),vc[col].end(), i);
			if(isSingle == 1)
			{
				for(int row = 0; row < 9; row++)
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

void mergeColumn()
{
	vector<int> vc[9];
	for(int col = 0; col < 9; col++)
	{
		vc[col].clear();
		for(int row = 0; row < 9; row++)
		{
			vc[col].insert(vc[col].end(), ve[row][col].begin(), ve[row][col].end());
		}
	}
	mergeSolveColumn(&vc[0]);
}