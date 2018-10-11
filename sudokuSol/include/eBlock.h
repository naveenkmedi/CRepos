#ifndef __EBLOCK_H
#define __EBLOCK_H

#include "main.h"

int unsolvedCountBlock(int i, int j);

// void mergeSolveBlock(vector <int> *vb, int row, int col);
// void mergeBlock();

int blockSolve(int i, int j);
void updateBlockElements(int row, int col, vector<int> vBlock, int* mergeCount, int mergElements[][2]);
void updateVBlock(int row, int col, vector<int> (*vBlock), int *mergeCount, int mergElements[][2]);
void reinitvBlock(vector<int> *vBlock, int *mergeCount, int mergElements[][2]);

#endif