#include "eBlock.h"

int unsolvedCountBlock(int i, int j)
{
	int empty = 0;

	for(int row = 3*(i); row < 3*(i)+3 ; row++)
	{
		for(int col = 3*(j); col < 3*(j) +3; col++)
		{
			if(ip[row][col] == 0)
				empty++;
		}
	}
	return empty;
}



// void mergeSolveBlock(vector <int> *vb, int row, int col)
// {
// 	for(int i = 1; i < 10; i++)
// 	{
// 		if(1 == count(vb->begin(),vb->end(), i))
// 		{
// 			//find which one has it
// 			for(int cRow = 3*(row); cRow < 3*(row)+ 3; cRow++)
// 			{
// 				for(int cCol = 3*(col); cCol < 3*(col) + 3; cCol++)
// 				{		
// 					int possible = count(ve[cRow][cCol].begin(), ve[cRow][cCol].end(), i);
// 					if(1 == possible)
// 					{
// 						ip[cRow][cCol] = i; 
// 						reinitVector(&ve[cRow][cCol]);
// 						updateDependents(cRow, cCol);
// 					}
// 				}
// 			}
// 		}
// 	}	
// }


// void mergeBlock()
// {
// 	vector<int> vb[3][3];
// 	for(int row = 0; row < 9; row++)
// 	{
// 		for(int col = 0; col < 9; col++)
// 		{
// 			vb[(row/3)][(col/3)].clear();
// 		}
// 	}

// 	for(int row = 0; row < 9; row++)
// 	{
// 		for(int col = 0; col < 9; col++)
// 		{
// 			vb[(row/3)][(col/3)].insert(vb[(row/3)][(col/3)].end(), ve[row][col].begin(), ve[row][col].end());
// 		}
// 	}

// 	for(int row = 0; row < 3; row++)
// 	{
// 		for(int col = 0; col < 3; col++)
// 		{		
// 			mergeSolveBlock(&vb[row][col], row, col);
// 		}
// 	}
// }

int blockSolve(int i, int j)
{
	// cout<<"line74\n";
	int empty = unsolvedCountBlock(i, j);
	if(empty < 3)
		return 0;
	//start with 2 at a time
	int merged = 0;
	vector<int> vBlock;
	int mergeCount = 0;
	int mergElements[8][2] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};							
	int mergeFlag = 0;

	for(int toBeMerged = 2; toBeMerged < empty; toBeMerged++)
	{
		for(int row = 3*(i); row < 3*(i)+3 ; row++)
		{
			for(int col = 3*(j); col < 3*(j) +3; col++)
			{ 
					// cout<<"line92\n";

				if(ip[row][col] == 0)
				{
						// cout<<"line96\n";

					mergElements[mergeCount][0] = row;
					mergElements[mergeCount][1] = col;
					mergeCount++;										
					vBlock.insert(vBlock.end(), ve[row][col].begin(), ve[row][col].end());

					int cCol = col + 1;
					int cRow = row +1;
					if((cCol % 3) == 0)
					{;
						if((cRow % 3) == 0)
							return -1;
						else 
							cCol = cCol - 3;
					}

					for(cRow; cRow < 3*(i)+3 ; cRow++)
					{
						for(cCol; cCol < 3*(j) +3; cCol++)
						{ 
							if(ip[cRow][cCol] == 0)
							{
								mergeFlag = 0;
								for(int m = 0; m< mergeCount; m++)
								{
									if((mergElements[m][0] == cRow) && (mergElements[m][1] == cCol))
									{
										// cout<<"repeat "<<mergElements[m][0]<<mergElements[m][1]<<endl;
										mergeFlag++;
										break;
									}
								}

								if(mergeFlag == 0)
								{
									mergElements[mergeCount][0] = cRow;
									mergElements[mergeCount][1] = cCol;
									mergeCount++;
									vBlock.insert(vBlock.end(), ve[cRow][cCol].begin(), ve[cRow][cCol].end());

									if(mergeCount == toBeMerged)
									{
											cout<<"elements  ";
											vector<int> shrinkedVector = shrinkVector(vBlock);
										for(int k = 0; k < mergeCount; k++)
										{
											cout<<mergElements[k][0]<<mergElements[k][1]<<"\t";
										}
										cout<<"\nshrinkedVector  ";
										printVector(&shrinkedVector);

										if(shrinkedSize(vBlock) == toBeMerged)
										{			
											cout<<"found single blockSolve\n";		
											cout<<"line 127 mergeCount  = "<<mergeCount<<endl;
											for(int k = 0; k<mergeCount; k++)
											{
												cout<<mergElements[k][0]<<mergElements[k][1]<<"\t";
											}
											cout<<endl;
											updateBlockElements(row, col, vBlock, &mergeCount, mergElements);
											cout<<"line 134 \n    ";
											updateVBlock(row, col, &vBlock, &mergeCount,mergElements);
											cout<<"line 136 \n    ";
										}							
									}
								}
							}
						}
						//cCol = 3* i;
						//reset cCol
					}
				}
			}				
			reinitvBlock(&vBlock, &mergeCount, mergElements);				
		}
		reinitvBlock(&vBlock, &mergeCount, mergElements);				
	}
}



void updateBlockElements(int row, int col, vector<int> vBlock, int* mergeCount, int mergElements[][2])
{
		cout<<"line173\n";
	vector<int> shrinkedVector = shrinkVector(vBlock);
	
	for(int cRow = 3*(row/3); cRow < 3*(row/3) + 3; cRow++) 
	for(int cCol = 3*(col/3); col < 3*(col/3) + 3; cCol++)
	{
		if(ip[cRow][cCol] == 0)
		{
			int elementFlag = 0;
			for(int count1 = 0; count1 < *mergeCount; count1++)//9 may not be the correct number
			{
				if((cRow == mergElements[count1][0])	&& (cCol == mergElements[count1][1]))
				{
					elementFlag++; break;	//check next element
				}
			}
			if(elementFlag == 0)
			{
				for(vector<int>::iterator num = shrinkedVector.begin(); num != shrinkedVector.end(); num++)
				{
					if(0 < count(ve[cRow][cCol].begin(), ve[cRow][cCol].end(), *num))		
					{									
						ve[cRow][cCol].erase(std::find(ve[cRow][cCol].begin(), ve[cRow][cCol].end(), *num));
						checkVe(row, col);
					}
				}
			}
		}
	}
}

void reinitvBlock(vector<int> *vBlock, int *mergeCount, int mergElements[][2])
{
	// cout<<"line 207\n";
	if(vBlock->size()!=0)
	{
	while(vBlock->size() != 0)
		vBlock->pop_back();
	for(int count = 0; count < 8; count++)
	{
		mergElements[count][0] = -1;
		mergElements[count][1] = -1;
	}
	*mergeCount = 0;
	// cout<<"line 215\n";
	}
}

//remove(pop) the last merged element
void updateVBlock(int row, int col, vector<int> (*vBlock), int *mergeCount, int mergElements[][2])
{
	int cRow = mergElements[*mergeCount-1][0];

	int cCol = mergElements[*mergeCount-1][1];
	vector<int> element = ve[cRow][cCol];
	for(int count = element.size(); count > 0; count--)
	{
		vBlock->pop_back();		
	}	
	mergElements[*mergeCount-1][0] = -1;
	mergElements[*mergeCount-1][1] = -1;
	*mergeCount--;
}