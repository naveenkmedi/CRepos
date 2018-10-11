#ifndef __MAIN_H
#define __MAIN_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "row.h"
#include "column.h"
#include "file2.h"
#include "block.h"
#include "fileRead.h"

#include "eRow.h"
#include "eColumn.h"
#include "eBlock.h"

extern int ip[9][9];
extern vector<int> ve[9][9];

void populatePoss();
void solve(int row, int column);

void updateVe(int row, int col, int num);
void updateDependents(int row, int col);
			
int shrinkedSize(vector<int> vRow);
void checkVe(int row, int col);
vector<int> shrinkVector(vector<int> v);


#endif