#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int ip[9][9] ={9,0,8,0,3,1,0,0,0, 0,0,0,0,2,0,5,0,0,5,0,0,0,9,0,0,4,0,0,0,0,8,0,0,0,0,5,8,3,2,0,0,0,1,7,4,1,0,0,0,0,7,0,0,0,0,8,0,0,5,0,0,0,3,0,0,7,0,8,0,0,0,0,0,0,0,4,7,0,6,0,2};
vector<int>  v[81];
vector<int>  ve[81];
void  printVectorV(int count1, int count2);
void reinitVector(int row, int col);
void mergeColumn();
void mergeSovleColumn(vector<int> *v2);

//populates v[vNum] after initialisation
void checkAndInsert(int vNum, int row, int col)
{
	int temp = ip[row][col];
	vector<int>::iterator itNum;

	int tempCount = count(v[vNum].begin(),v[vNum].end(), temp);

	if(tempCount == 0)
	{
		vector<int>::iterator it0;
	 	it0 = find(v[vNum].begin(), v[vNum].end(), 0);
		v[vNum].at(it0-v[vNum].begin()) = temp;
	}
}
//populate v[vNum] by row check
void populateMapRow(int count, int count2)
{
	//add column elements
	for(int column = 0; column < 9; column++)
	{
		if(column == count2)
		{
			continue;
		}	//check if present
		if(ip[count][column] != 0)
		checkAndInsert(9*count + count2, count, column);
	}
}


//populate v[vNum] by column check
void populateMapColumn(int count, int count2)
{
//add column elements
	for(int row = 0; row < 9; row++)
	{
		if(row == count)
			continue;
		//check if present
		if(ip[row][count2] != 0)
			checkAndInsert(9*count + count2, row, count2);
	}

	if((count == 1)&&(count2 == 0))
	{
		//cout<<"populating with column for 10\n";
		//printVector(count, count2);
	}
}


//populate v[vNum] by block check
void populateMapGrid(int count, int count2)
{
	for(int row = (int)(count/3) * 3; row < (int)(count/3) * 3 + 3; row++)
	{
		for(int col = (count2/3) * 3; col < (count2/3) * 3 + 3; col++)
		{
			//same element
			if((row == count) && (col == count2)) continue;
			if(ip[row][col] != 0)
			checkAndInsert(9*count + count2, row, col);
		}
	}
}

void  printVectorV(int count1, int count2)
{
	vector<int>::iterator itNum = v[9*count1 + count2].begin();
	for(itNum; itNum != v[9*count1 + count2].end(); itNum++)
	{
		cout<<*itNum<<"\t";
	}
	cout<<endl;
}

void  printVectorVe(int count1, int count2)
{
	//cout<<"size = "<<ve[9*count1 + count2].size()<<"\t";
	vector<int>::iterator itNum = ve[9*count1 + count2].begin();
	for(itNum; itNum != ve[9*count1 + count2].end(); itNum++)
	{
		cout<<*itNum<<"\t";
	}
	cout<<endl;
}

void populateVe(int row, int col)
{
	/*if((row == 4) && (col == 4))
	{
		cout<<"44 ve[4][4] size = \t"<<v[40].size()<<"   ";
	}*/

	for(int i = 1; i < 10; i++)
	{
		//cout<<"populate Ve\t"<<row<<col<<"\t"<<i<<endl;
		if(ip[row][col] != 0) continue;
		int iCount = count(v[9*row + col].begin(), v[9*row + col].end(), i);
		if(iCount == 0)
		{
			int rep = count(ve[9*row + col].begin(), ve[9*row + col].end(), i);
			if(rep != 0) continue;
			//cout<<"inside  if\t"<<row<<col<<"\t"<<i<<endl;
			vector<int>::iterator it0;
			it0 = find(ve[9*row + col].begin(), ve[9*row + col].end(), 0);
			if(it0 != ve[9*row + col].end() )
			ve[9*row + col].at(it0-ve[9*row + col].begin()) = i;
		}
	}
	//cout<<"44 ve[4][4] size = \t"<<v[40].size()<<"   ";	
}

void populateMaps()
{
	//row elements
	for(int count1 = 0; count1 < 9; count1++)
	{
		for(int count2 = 0; count2 < 9; count2++)
		{
			if(ip[count1][count2] != 0) 
			{
				reinitVector(count1, count2);	//redundant
				continue;
			}
			populateMapRow(count1, count2);
			populateMapColumn(count1, count2);
			populateMapGrid(count1, count2);
			populateVe(count1, count2);
		}
	}
}

void reinitVector(int row, int col)
{
	/*for(int row = 0; row <9; row++)
		for(int col = 0; col < 9; col++){*/
	for(int i = 0; i < 9; i++)
	{
		v[9*row+col].pop_back();
		ve[9*row+col].pop_back();
	}

	for(int i = 0; i < 9; i++)
	{
		v[9*row+col].push_back(0);
		ve[9*row+col].push_back(0);
	}
	//printVector(row, col);
}

void updateVe(int row, int col, int num)
{
	int index = 9*row+col;
	if(ip[row][col] == 0)
	{
		int tempCount = count(ve[index].begin(), ve[index].end(), num);
		if(tempCount == 1)
		{
			vector<int>::iterator itTemp;
			itTemp = find(ve[index].begin(), ve[index].end(), num);
			ve[index].at(itTemp-ve[index].begin()) = 0;
		}
	}

	else
	{
		reinitVector(row, col); //redundant
	}
}

void updateV(int row, int col, int num)
{
	//check if the number is already there if not add at first 0
	int index = 9*row+col;
	if(ip[row][col] == 0)
	{
		int tempCount = count(v[index].begin(), v[index].end(), num);
		if(tempCount == 0)
		{
			vector<int>::iterator it0;
			it0 = find(v[index].begin(), v[index].end(), 0);
			v[index].at(it0-v[index].begin()) = num;
		}
	}

	else
	{
		reinitVector(row, col); //redundant
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
			//ve and v should be zero
			reinitVector(row, cCol);
		}
		//update vector
		updateV(row, cCol, num);
	
		updateVe(row, cCol, num);
	}

	for(int cRow = 0; cRow < 9; cRow++)
	{
		if(cRow == row) continue;
		updateV(cRow, col, num);
		updateVe(cRow, col, num);
	}
	//column 8
	//block	4 
	//00 --- 11 12 21 22
	//01 ---- 10 12 20 22
	//02---- 10 12  11 21
	//for 3x3 - row%3 = vRow%3 or col%3 = vCol%3 continue
	for(int cRow = row/3; cRow < row/3 + 3; cRow++)
	{
			if(cRow%3 == row%3) continue;
		for(int cCol = col/3; cCol < col/3 + 3; cCol++)
		{
			if(cCol%3 == cRow % 3) continue;
			updateV(cRow, col, num);
			updateVe(cRow, cCol, num);
		}
	}
}

void solve(int row, int column)
{
	for(int count1 = 0; count1 < 9; count1++)
	{
		for(int count2 = 0; count2 < 9; count2++)
		{
			if(ip[count1][count2] != 0)
				continue;

			int zeroCount=count(v[9*count1 + count2].begin(),v[9*count1 + count2].end(),0);
			if(zeroCount == 1)
			{
				//cout<<"zeroCount\t"<<count1<<count2<<endl;;
				for(int i = 1; i < 10; i++)
				{
					int iCount = count(v[9*count1 + count2].begin(),v[9*count1 + count2].end(), i);
					if(iCount == 0)
					{
						//if((count1 == 8)&&(count2 == 1))
							//printVectorV(count1, count2);
						if((count1 == 1) &&(count2 == 2))
						{
							cout<<"solution \n";	

							cout<< "vector V at 12 \t";printVectorV(1, 2);	
							cout<< "vector Ve at 12 \t";printVectorVe(1, 2);	
							cout<<"\n"<<i<<"\n\n"; 
						}

						ip[count1][count2] = i;	//found something - call update dependents
						updateDependents(count1, count2);
						break;
					}
				}
			}
		}
	}
	//cout<<"solve ends\n";
}

void printOutput()
{
	for(int count = 0; count < 9; count++)
	{
		for(int count2 = 0; count2 < 9; count2++)
		{
			cout<<ip[count][count2]<<"   ";
			if(count2 % 3 == 2) cout<<"   ";
		}
		cout<<"\n";
		if(count % 3 == 2) cout<<endl;
	}
}

void vecInit()
{
	for(int i = 0; i < 81; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			v[i].push_back(0);
			ve[i].push_back(0);
		}
	}
	cout<<"init\t"<<ve[40].size()<<endl;
}

void mergeSovle(vector <int> *v2)
{
	for(int row = 0; row < 9; row++)
	{

		for(int i = 1; i < 10; i++)
		{
			solve(0, 0);
			if(1 == count(v2[row].begin(),v2[row].end(), i))
			{
				vector<int>::iterator it;
				it = find(v2[row].begin(), v2[row].end(), i);
				int pos = (it-v2[row].begin())/9;

				if((row == 1) &&(pos == 2))
				{
					cout<< "vector V at 10 \t";printVectorV(1, 2);	
					cout<< "vector Ve at 10 \t";printVectorVe(1, 2);	
				}

				ip[row][pos] = i; 
				//reinitVector(row,pos);
				updateDependents(row, pos);
				solve(0, 0);
				break;	
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
		v2[row].reserve( 9*(v[1].size())); // preallocate memory
		for(int col = 0; col < 9; col++)
		{
				//cout<<"merging size(, col) -"<<row<<","<<col<<") - "<<ve[9*row+col].size()<<endl;
				v2[row].insert(v2[row].end(), ve[9*row+col].begin(), ve[9*row+col].end());
		}
	}
	mergeSovle(&v2[0]);
}

void mergeSovleColumn(vector <int> *v2)
{
	for(int col = 0; col < 9; col++)
	{
		for(int i = 1; i < 10; i++)
		{
			solve(0, 0);
			if(1 == count(v2[col].begin(),v2[col].end(), i))
			{
				vector<int>::iterator it;
				it = find(v2[col].begin(), v2[col].end(), i);
				int pos = (it-v2[col].begin())/9;

				if((pos == 1) &&(col == 2))
				{
					cout<< "vector V at 10 \t";printVectorV(1, 2);	
					cout<< "vector Ve at 10 \t";printVectorVe(1, 2);	
				}

				ip[pos][col] = i; 
				//reinitVector(row,pos);
				updateDependents(pos, col);
				solve(0, 0);
				break;	
			}
		}	
	}
}

void mergeColumn()
{
	vector<int> v2[9];
	for(int col = 0; col < 9; col++)
	{
		v2[col].clear();
		v2[col].reserve( 9*(v[1].size())); // preallocate memory
		for(int row = 0; row < 9; row++)
		{
				//cout<<"merging size(, col) -"<<row<<","<<col<<") - "<<ve[9*row+col].size()<<endl;
				v2[col].insert(v2[col].end(), ve[9*row+col].begin(), ve[9*row+col].end());
		}
	}
	mergeSovleColumn(&v2[0]);
}

int main()
{
	//ip is given
	vecInit();
	populateMaps();
	for(int i = 0; i < 5; i++)
	{
		//solve(1,1);
		//solve(1,1);solve(1,1);solve(1,1);solve(1,1);solve(1,1);solve(1,1);
		mergeRow();
		//mergeColumn();
		//populateMaps();
	}
	printOutput();
}
