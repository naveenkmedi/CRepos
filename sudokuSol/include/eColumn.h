#ifndef __ECOLUMN_H
#define __ECOLUMN_H

#include "main.h"

int columnSolve(int col);
int unsolvedCountColumn(int col);
void updateColumnElements(int col, vector<int> vColumn, int* mergeCount, int *mergElements);
void updateVColumn(int col, vector<int> (*vRow), int *mergeCount, int *mergElements);
void reinitvColumn(vector<int> *vColumn, int *mergeCount, int *mergElements);

#endif