#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

#include "main.h"
#include "fileRead.h"
#include "file2.h"

using namespace std;

int ip[9][9];
vector<int> ve[9][9];

void mergeColumn();
void updateVe(int row, int col, int num);
void updateDependents(int row, int col);
void solve(int row, int column);
void printOutput();
void mergeSolveRow(vector <int> *v2);
void mergeRow();
void populatePoss();
void mergeSolveColumn(vector <int> *vc);
void mergeColumn();
void mergeSolveBlock(vector <int> *vb, int row, int col);
void mergeBlock();


int unsolved(int row);
int rowSolve(int row);
vector<int> shrinkVrow(vector<int> vRow);
void updateRowElements(int row, vector<int> vRow, int* mergeCount, int *mergElements);
void checkVe(int row, int col);
int shrinkedSize(vector<int> vRow);
void reinitvRow(vector<int> *vRow, int *mergeCount, int *mergElements);
void updateVRow(int row, vector<int> (*vRow), int *mergeCount, int *mergElements);


int unsolved(int row)
{
	int empty = 0;
	for(int col = 0; col < 9; col++)
	{
		if(ip[row][col] == 0)
			empty++;
	}
	//cout<<"reached 46 empty = "<<empty<<"\n";	
	return empty;
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
				//cout<<"reached 65\n";	
				mergElements[mergeCount] = col;
				mergeCount++;										
				vRow.insert(vRow.end(), ve[row][col].begin(), ve[row][col].end());

				for(int cCol = col+1; cCol < 9; cCol++)
				{
					if(ip[row][cCol] == 0)
					{	
						//cout<<"reached 73\t"<<row<<cCol<<"\t";		
						mergElements[mergeCount] = cCol;
						mergeCount++;
						vRow.insert(vRow.end(), ve[row][cCol].begin(), ve[row][cCol].end());
						//cout<<"mergeCount = "<<mergeCount<<" -toBeMerged = "<<toBeMerged<<" empty = "<<empty<<"\t"<<endl;
						if(mergeCount == toBeMerged)
						{
							// cout<<"reached 80  row = "<<row<<" column = "<<cCol<<" toBeMerged = "<<toBeMerged<<"\t";
							// for(int i = 0; i< toBeMerged; i++)
							// {
							// 	cout<<"  element = "<<mergElements[i]<<"  ";
							// }
							// cout<<endl;
							vector<int> shrinkedVector = shrinkVrow(vRow);
							// cout<<"shrinked vector   ";
							//printVector(&shrinkedVector);				
							if(shrinkedSize(vRow) == toBeMerged)
							{					
								cout<<row<<cCol<<" merge = "<<toBeMerged<<" reached 84\t";
								for(int i = 0; i< toBeMerged; i++)
								{
									cout<<"element = "<<mergElements[i]<<"  ";
								}cout<<endl;
								printVector(&shrinkedVector);				
								updateRowElements(row, vRow, &mergeCount, &mergElements[0]);
								updateVRow(row, &vRow, &mergeCount, &mergElements[0]);	
							}							
						}
					}
				}
			}				
			reinitvRow(&vRow, &mergeCount, &mergElements[0]);				
		}
		reinitvRow(&vRow, &mergeCount, &mergElements[0]);	
	}
}

vector<int> shrinkVrow(vector<int> vRow)
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
	//printVector(&vRow);
	return vRow;
}

void updateRowElements(int row, vector<int> vRow, int* mergeCount, int *mergElements)
{
	vector<int> shrinkedVector = shrinkVrow(vRow);
	
	for(int col = 0; col < 9; col++)
	{
		if(ip[row][col] == 0)
		{
			int columnCheck = 0;
			//int count1 = 0;
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
					{									//cout<<row<<col<<"reached 140\n";
						ve[row][col].erase(std::find(ve[row][col].begin(), ve[row][col].end(), *num));
						checkVe(row, col);
					}
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
			//solve(1,1);	
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

void reinitvRow(vector<int> *vRow, int *mergeCount, int *mergElements)
{
	//cout<<"reached 168(reinitvRow)- "<<endl;;

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
	//cout<<"reached 179(updateVRow)- "<<row<<endl;;
	int col = mergElements[*mergeCount];
	vector<int> element = ve[row][col];
	for(int count = element.size(); count > 0; count--)
	{
		vRow->pop_back();		
	}	
	mergElements[*mergeCount] = -1;
	*mergeCount--;
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

int main()
{	
	if(0 == readFile())
	{
		populatePoss();
		printOutput();
		for(int i = 0; i < 200; i++)
		{
			solve(1,1);
			mergeRow();
			mergeColumn();
			mergeBlock();
		}

		// cout<<"after solving\n";
		// printOutput();
		
		// for(int row = 1; row < 10; row++)
		// {
		// 	//rowSolve(row); not yet working
		// 	solve(1,1);
		// 	mergeRow();
		// 	mergeColumn();
		// 	mergeBlock();
		// }

		cout<<"after solving\n";
		printOutput();
	}
}


