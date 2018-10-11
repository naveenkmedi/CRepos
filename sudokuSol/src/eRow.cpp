#include "eRow.h"

int unsolvedCountRow(int row)
{
	int empty = 0;
	for(int col = 0; col < 9; col++)
	{
		if(ip[row][col] == 0)
			empty++;
	}
	return empty;
}

int rowSolve(int row)
{
	int empty = unsolvedCountRow(row);
	if(empty < 3)
		return 0;
	//start with 2 at a time
	int merged = 0;
	vector<int> vRow;
	int mergeCount = 0;
	int mergElements[8] = {-1};

	for(int toBeMerged = 2; toBeMerged < empty; toBeMerged++)
	{
		for(int col = 0; col < 8; col++)
		{ 
			if(ip[row][col] == 0)
			{
				mergElements[mergeCount] = col;
				mergeCount++;										
				vRow.insert(vRow.end(), ve[row][col].begin(), ve[row][col].end());

				for(int cCol = col+1; cCol < 9; cCol++)
				{
					if(ip[row][cCol] == 0)
					{	
						mergElements[mergeCount] = cCol;
						mergeCount++;
						vRow.insert(vRow.end(), ve[row][cCol].begin(), ve[row][cCol].end());
						if(mergeCount == toBeMerged)
						{
							vector<int> shrinkedVector = shrinkVector(vRow);
							cout<<"row - "<<row<<" elements - ";
							for(int k = 0; k < mergeCount; k++)
							{
								cout<<mergElements[k]<<"\t";
							}
							cout<<"\nshrinkedVector  ";
							printVector(&shrinkedVector);

							if(shrinkedSize(vRow) == toBeMerged)
							{			
								cout<<"found single in row = "<<row<<"\nelements \t";		
								
								updateRowElements(row, vRow, &mergeCount, &mergElements[0]);
								// updateVRow(row, &vRow, &mergeCount, &mergElements[0]);	
							}							
							updateVRow(row, &vRow, &mergeCount, &mergElements[0]);
						}
					}
				}
			}				
			reinitvRow(&vRow, &mergeCount, &mergElements[0]);				
		}
		reinitvRow(&vRow, &mergeCount, &mergElements[0]);	
	}
}



void updateRowElements(int row, vector<int> vRow, int* mergeCount, int *mergElements)
{
	vector<int> shrinkedVector = shrinkVector(vRow);
	
	for(int col = 0; col < 9; col++)
	{
		if(ip[row][col] == 0)
		{
			int columnCheck = 0;
			for(int count1 = 0; count1 < *mergeCount; count1++)//9 may not be the correct number
			{
				if(col == mergElements[count1])
				{
					columnCheck++; break;	//check next element
				}
			}
			if(columnCheck == 0)
			{
				for(vector<int>::iterator num = shrinkedVector.begin(); num != shrinkedVector.end(); num++)
				{
					if(0 < count(ve[row][col].begin(), ve[row][col].end(), *num))		
					{									
						ve[row][col].erase(std::find(ve[row][col].begin(), ve[row][col].end(), *num));
						checkVe(row, col);
					}
				}
			}
		}
	}
}

void reinitvRow(vector<int> *vRow, int *mergeCount, int *mergElements)
{
	while(vRow->size() != 0)
		vRow->pop_back();
	for(int count = 0; count < 8; count++)
	{
		mergElements[count] = -1;
	}
	*mergeCount = 0;
}

//remove the last merged element
void updateVRow(int row, vector<int> (*vRow), int *mergeCount, int *mergElements)
{
	int col = mergElements[(*mergeCount)-1];
	cout<<"col = "<<col<<endl; 
	vector<int> element = ve[row][col];
	for(int count = element.size(); count > 0; count--)
	{
		vRow->pop_back();		
	}	
	mergElements[(*mergeCount) -1] = -1;
	(*mergeCount)--;
}