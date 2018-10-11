#ifndef __EROW_H
#define __EROW_H

#include "main.h"

int unsolvedCountRow(int row);
int rowSolve(int row);

void updateRowElements(int row, vector<int> vRow, int* mergeCount, int *mergElements);

void reinitvRow(vector<int> *vRow, int *mergeCount, int *mergElements);
void updateVRow(int row, vector<int> (*vRow), int *mergeCount, int *mergElements);

#endif