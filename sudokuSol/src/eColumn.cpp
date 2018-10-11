#include "eColumn.h"

int columnSolve(int col)
{
	int empty = unsolvedCountColumn(col);
	if(empty < 3)
		return 0;

	int merged = 0;
	vector<int> vCol;
	int mergeCount = 0;
	int mergElements[8] = {-1};	//keeps track of merged elements

	for(int toBeMerged = 2; toBeMerged < empty; toBeMerged++)
	{
		for(int row = 0; row < 8; row++)
		{ 
			if(ip[row][col] == 0)
			{
				mergElements[mergeCount] = row;	
				mergeCount++;										
				vCol.insert(vCol.end(), ve[row][col].begin(), ve[row][col].end());

				for(int cRow = row+1; cRow < 9; cRow++)
				{
					if(ip[cRow][col] == 0)
					{	
						mergElements[mergeCount] = cRow;
						mergeCount++;
						vCol.insert(vCol.end(), ve[cRow][col].begin(), ve[cRow][col].end());
						// cout<<"column 31\n";
						if(mergeCount == toBeMerged)
						{							
							vector<int> shrinkedVector = shrinkVector(vCol);
							// printVector(&shrinkedVector);
							// cout<<"column 43\n";
								
							if(shrinkedSize(vCol) == toBeMerged)
							{			
								cout<<"found single in col = "<<col<<"\nelements \t";		
								vector<int> shrinkedVector = shrinkVector(vCol);
								for(int k = 0; k < mergeCount; k++)
								{
									cout<<mergElements[k]<<"\t";
								}
								cout<<"\nshrinkedVector  ";
								printVector(&shrinkedVector);

								updateColumnElements(col, vCol, &mergeCount, &mergElements[0]);
								updateVColumn(col, &vCol, &mergeCount, &mergElements[0]);	
							}						
							updateVColumn(col, &vCol, &mergeCount, &mergElements[0]);		
						}
					}
				}
			}				
			reinitvRow(&vCol, &mergeCount, &mergElements[0]);				
		}
		reinitvRow(&vCol, &mergeCount, &mergElements[0]);	
	}
}



// if(shrinkedSize(vRow) == toBeMerged)
// 							{			
// 								cout<<"found single in row = "<<row<<"\nelements \t";		
// 								vector<int> shrinkedVector = shrinkVector(vRow);
// 								for(int k = 0; k < mergeCount; k++)
// 								{
// 									cout<<mergElements[k]<<"\t";
// 								}
// 								cout<<"\nshrinkedVector  ";
// 								printVector(&shrinkedVector);
// 								updateRowElements(row, vRow, &mergeCount, &mergElements[0]);
// 								updateVRow(row, &vRow, &mergeCount, &mergElements[0]);	
// 							}	

void updateVColumn(int col, vector<int> (*vColumn), int *mergeCount, int *mergElements)
{
	int row = mergElements[(*mergeCount) -1];
	cout<<"\t row = "<< row<<"\n";
	cout<<"row = "<<row<<"\t";
	vector<int> element = ve[row][col];

	for(int count = element.size(); count > 0; count--)
	{
		vColumn->pop_back();		
	}	
	mergElements[(*mergeCount) -1] = -1;
	*mergeCount--;
	 cout<<"   line 156\n";
}


// //remove the last merged element
// void updateVRow(int row, vector<int> (*vRow), int *mergeCount, int *mergElements)
// {
// 	int col = mergElements[(*mergeCount)-1];
// 	cout<<"col = "<<col<<endl; 
// 	vector<int> element = ve[row][col];
// 	for(int count = element.size(); count > 0; count--)
// 	{
// 		vRow->pop_back();		
// 	}	
// 	mergElements[(*mergeCount) -1] = -1;
// 	(*mergeCount)--;
// }




int unsolvedCountColumn(int col)
{
	int empty = 0;
	for(int row = 0; row < 9; row++)
	{
		if(ip[row][col] == 0)
			empty++;
	}
	return empty;
}

void updateColumnElements(int col, vector<int> vColumn, int* mergeCount, int *mergElements)
{
	vector<int> shrinkedVector = shrinkVector(vColumn);
	
	for(int row = 0; row < 9; row++)
	{
		if(ip[row][col] == 0)
		{
			int rowCheck = 0;
			for(int count1 = 0; count1 < *mergeCount; count1++)//9 may not be the correct number
			{
				if(row == mergElements[count1])
				{
					rowCheck++; break;	//check next element
				}
			}
			if(rowCheck == 0)
			{
				// cout<<row<<col<<"  reached 124\n";
				for(vector<int>::iterator num = shrinkedVector.begin(); num != shrinkedVector.end(); num++)
				{
					// cout<<row<<col<<"  reached 128    ";
					// printVector(&shrinkedVector);
					if(0 < count(ve[row][col].begin(), ve[row][col].end(), *num))		
					{									
						// cout<<row<<col<<"  reached 130\n";
						ve[row][col].erase(std::find(ve[row][col].begin(), ve[row][col].end(), *num));
						checkVe(row, col);
												// cout<<row<<col<<"  reached 135\n";

					}
				}
			}
		}
	}
}



void reinitvColumn(vector<int> *vColumn, int *mergeCount, int *mergElements)
{
	while(vColumn->size() != 0)
		vColumn->pop_back();
	for(int count = 0; count < 8; count++)
	{
		mergElements[count] = -1;
	}
	*mergeCount = 0;
}
