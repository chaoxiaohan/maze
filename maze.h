#ifndef MAZE_H
#define MAZE_H

#include "common.h"

// 迷宫数组和访问标记数组
extern int maze[WIDTH / CELL_SIZE][HEIGHT / CELL_SIZE];
extern int visited[WIDTH / CELL_SIZE][HEIGHT / CELL_SIZE];

// 起点和终点
extern Point start;
extern Point end;

// 迷宫初始化函数
void initMaze();

// 迷宫生成函数
void generateMaze(int x, int y);

// 确保终点可达
void ensureEndpointAccessible();

// 检查是否存在从起点到终点的路径
bool checkPathExists();

// 创建一条直接路径
void createDirectPath();

#endif // MAZE_H
