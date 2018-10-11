#include "block.h"


void mergeSolveBlock(vector <int> *vb, int row, int col)
{
	for(int i = 1; i < 10; i++)
	{
		if(1 == count(vb->begin(),vb->end(), i))
		{
			//find which one has it
			for(int cRow = 3*(row); cRow < 3*(row)+ 3; cRow++)
			{
				for(int cCol = 3*(col); cCol < 3*(col) + 3; cCol++)
				{		
					int possible = count(ve[cRow][cCol].begin(), ve[cRow][cCol].end(), i);
					if(1 == possible)
					{
						ip[cRow][cCol] = i; 
						reinitVector(&ve[cRow][cCol]);
						updateDependents(cRow, cCol);
					}
				}
			}
		}
	}	
}


void mergeBlock()
{
	vector<int> vb[3][3];
	for(int row = 0; row < 9; row++)
	{
		for(int col = 0; col < 9; col++)
		{
			vb[(row/3)][(col/3)].clear();
		}
	}

	for(int row = 0; row < 9; row++)
	{
		for(int col = 0; col < 9; col++)
		{
			vb[(row/3)][(col/3)].insert(vb[(row/3)][(col/3)].end(), ve[row][col].begin(), ve[row][col].end());
		}
	}

	for(int row = 0; row < 3; row++)
	{
		for(int col = 0; col < 3; col++)
		{		
			mergeSolveBlock(&vb[row][col], row, col);
		}
	}
}
