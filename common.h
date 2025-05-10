#ifndef COMMON_H
#define COMMON_H

#include <graphics.h> // EasyX图形库头文件
#include <stdlib.h>  
#include <time.h>  
#include <conio.h>    // 控制台输入输出头文件
#include <windows.h>  // Windows API头文件

// 定义窗口大小和单元格大小
#define WIDTH 800
#define HEIGHT 600
#define CELL_SIZE 20

// 定义迷宫的单元格结构
typedef struct {
    int x, y;
} Point;

// 定义颜色
const COLORREF WALL_COLOR = WHITE;       // 墙的颜色（白色）
const COLORREF PATH_COLOR = BLACK;       // 通道颜色（黑色）
const COLORREF START_COLOR = GREEN;      // 起点颜色（绿色）
const COLORREF END_COLOR = BLUE;         // 终点颜色（蓝色）
const COLORREF SOLUTION_COLOR = RED;     // 解决路径颜色（红色）
const COLORREF EXPLORING_COLOR = YELLOW; // 探索中颜色（黄色）

#endif // COMMON_H
