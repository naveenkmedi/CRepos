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
							// cout<<"Merge count = "<<mergeCount<<"    \t";		
							// for(int k = 0; k<mergeCount; k++)
							// {
							// 		cout<<mergElements[k]<<"\t";
							// }
							// cout<<endl;								
							
							vector<int> shrinkedVector = shrinkVector(vCol);
							// printVector(&shrinkedVector);
							// cout<<"column 43\n";
								
							if(shrinkedSize(vCol) == toBeMerged)
							{			
								cout<<"found singel\n";		
								updateColumnElements(col, vCol, &mergeCount, &mergElements[0]);
								cout<<"line 82 mergeCount = "<<mergeCount<<endl;
								cout<<endl;
								updateVColumn(col, &vCol, &mergeCount, &mergElements[0]);	
								cout<<"column 52\n";
							}							
						}
					}
				}
			}				
			reinitvRow(&vCol, &mergeCount, &mergElements[0]);				
		}
		reinitvRow(&vCol, &mergeCount, &mergElements[0]);	
	}
}


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

void updateVColumn(int col, vector<int> (*vColumn), int *mergeCount, int *mergElements)
{
	for(int i = 0; i <= *mergeCount; i++)
		cout<<" element = "<<mergElements[i];

	cout<<"line 147   mergeCount = "<<*mergeCount<<endl;
	int row = mergElements[(*mergeCount) -1];
	// cout<<"line 149\t row = "<< row<<"\t";
	// cout<<"size = "<<ve[row][col].size()<<"\t";
	cout<<"row = "<<row<<"\t";
	vector<int> element = ve[row][col];
	cout<<"ve ---  "; printVector(&ve[row][col]);
	cout<<"vColumn ---- "; printVector(vColumn);
	for(int count = element.size(); count > 0; count--)
	{
		vColumn->pop_back();		
	}	
	mergElements[*mergeCount] = -1;
	*mergeCount--;
	 cout<<"   line 156\n";
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
