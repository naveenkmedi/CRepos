vector<int> shrinkVrow(vector<int> vRow);
void updateRowElements(int row, vector<int> vRow, int *mergElements);
void checkVe(int row, int col);
int shrinkedSize(vector<int> vRow);
void reinitvRow(vector<int> *vRow, int *mergElements);
void updateVRow(int row, vector<int> (*vRow), int mergeCount, int *mergElements);
int unsolved(int row);
int rowSolve(int row);



int unsolved(int row)
{
	int empty = 0;
	for(int col = 0; col < 9; col++)
	{
		if(ip[row][col] == 0)
			empty++;
	}
}

int rowSolve(int row)
{
	int empty = unsolved(row);
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
				//cout<<"reached 281\n";	
				mergElements[mergeCount] = col;
				mergeCount++;										
				vRow.insert(vRow.end(), ve[row][col].begin(), ve[row][col].end());

				for(int cCol = col; cCol < 9; cCol++)
				{
					if(ip[row][cCol] == 0)
					{	
						cout<<"reached 290\n";		
						mergElements[mergeCount] = cCol;
						mergeCount++;
						vRow.insert(vRow.end(), ve[row][cCol].begin(), ve[row][cCol].end());
						if(mergeCount == toBeMerged)
						{
							cout<<"reached \n 296";	
							if(shrinkedSize(vRow) == toBeMerged)
							{					
								cout<<"reached 299\n";				
								updateVRow(row, &vRow, mergeCount, &mergElements[0]);	
							}							
						}
					}
				}
			}				
			reinitvRow(&vRow, &mergElements[0]);				
		}
		reinitvRow(&vRow, &mergElements[0]);	
	}
}

vector<int> shrinkVrow(vector<int> vRow)
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
	return vRow;
}

void updateRowElements(int row, vector<int> vRow, int *mergElements)
{
	vector<int> shrinkedVector = shrinkVrow(vRow);
	
	for(int col = 0; col < 9; col++)
	{
		if(ip[row][col] == 0)
		{
			int columnCheck = 0;
			for(int count = 0; count < 9; count++)//9 may not be the correct number
			{
				if(col == mergElements[count])
				{
					columnCheck++; break;	//check next element
				}
			}
			if(columnCheck == 0)
			{
				for(vector<int>::iterator num = shrinkedVector.begin(); num != shrinkedVector.end(); num++)
				{
					ve[row][col].erase(std::find(ve[row][col].begin(), ve[row][col].end(), *num));
					checkVe(row, col);
				}
			}
		}
	}
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

void reinitvRow(vector<int> *vRow, int *mergElements)
{
	while(vRow->size() != 0)
		vRow->pop_back();
	for(int count = 0; count < 8; count++)
	{
		mergElements[count] = -1;
	}
}

//remove the last merged element
void updateVRow(int row, vector<int> (*vRow), int mergeCount, int *mergElements)
{
	int col = mergElements[mergeCount];
	vector<int> element = ve[row][col];
	for(int count = element.size(); count > 0; count--)
	{
		vRow->pop_back();		
	}	
	mergElements[mergeCount] = -1;
	mergeCount--;
}
