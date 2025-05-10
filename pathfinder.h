#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "common.h"

// 检查从特定位置是否可以到达终点
bool testPath(int x, int y);

// 迷宫求解函数
int solveMaze(int x, int y, int ex, int ey);

#endif // PATHFINDER_H
