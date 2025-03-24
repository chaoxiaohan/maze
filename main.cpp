#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 800
#define HEIGHT 600
#define CELL_SIZE 20

typedef struct {
    int x, y;
} Point;

int maze[WIDTH / CELL_SIZE][HEIGHT / CELL_SIZE];
int visited[WIDTH / CELL_SIZE][HEIGHT / CELL_SIZE];

// 定义颜色常量，使代码更可读
const COLORREF WALL_COLOR = WHITE;       // 墙的颜色（白色）
const COLORREF PATH_COLOR = BLACK;       // 通道颜色（黑色）
const COLORREF START_COLOR = GREEN;      // 起点颜色（绿色）
const COLORREF END_COLOR = BLUE;         // 终点颜色（蓝色）
const COLORREF SOLUTION_COLOR = RED;     // 解决路径颜色（红色）
const COLORREF EXPLORING_COLOR = YELLOW; // 探索中颜色（黄色）

// 定义起点和终点位置
Point start = {0, 0};
Point end = {WIDTH / CELL_SIZE - 1, HEIGHT / CELL_SIZE - 1};

void initMaze() {
    for (int i = 0; i < WIDTH / CELL_SIZE; i++) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; j++) {
            maze[i][j] = 1; // 初始化为墙（白色）
            visited[i][j] = 0;
        }
    }
}

void drawMaze() {
    for (int i = 0; i < WIDTH / CELL_SIZE; i++) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; j++) {
            if (maze[i][j] == 1) { // 墙
                setfillcolor(WALL_COLOR);
            } else if (maze[i][j] == 0) { // 通道
                setfillcolor(PATH_COLOR);
            } else if (maze[i][j] == 2) { // 解决路径
                setfillcolor(SOLUTION_COLOR);
            }
            solidrectangle(i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE);
        }
    }

    // 标记起点和终点
    setfillcolor(START_COLOR);
    solidrectangle(start.x * CELL_SIZE, start.y * CELL_SIZE, (start.x + 1) * CELL_SIZE, (start.y + 1) * CELL_SIZE);
    
    setfillcolor(END_COLOR);
    solidrectangle(end.x * CELL_SIZE, end.y * CELL_SIZE, (end.x + 1) * CELL_SIZE, (end.y + 1) * CELL_SIZE);
    
    // 确保绘制操作立即显示
    FlushBatchDraw();
}

void generateMaze(int x, int y) {
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    visited[x][y] = 1;
    maze[x][y] = 0; // 设置为通道（黑色）

    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp[2];
        temp[0] = directions[i][0];
        temp[1] = directions[i][1];
        directions[i][0] = directions[r][0];
        directions[i][1] = directions[r][1];
        directions[r][0] = temp[0];
        directions[r][1] = temp[1];
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        int nnx = nx + directions[i][0];
        int nny = ny + directions[i][1];
        if (nnx >= 0 && nnx < WIDTH / CELL_SIZE && nny >= 0 && nny < HEIGHT / CELL_SIZE && !visited[nnx][nny]) {
            maze[nx][ny] = 0; // 设置为通道（黑色）
            generateMaze(nnx, nny);
        }
    }
}

// 修改求解函数，使其在黑色通道中寻找路径
int solveMaze(int x, int y, int ex, int ey) {
    if (x == ex && y == ey) {
        maze[x][y] = 2; // 标记终点
        setfillcolor(SOLUTION_COLOR);
        solidrectangle(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
        
        // 重新标记终点，确保它始终是蓝色的
        setfillcolor(END_COLOR);
        solidrectangle(end.x * CELL_SIZE, end.y * CELL_SIZE, (end.x + 1) * CELL_SIZE, (end.y + 1) * CELL_SIZE);
        
        FlushBatchDraw(); // 刷新显示
        Sleep(50);
        return 1;
    }
    
    // 注意：这里改为检查是否是通道（maze[x][y] == 0），而不是墙
    if (x < 0 || x >= WIDTH / CELL_SIZE || y < 0 || y >= HEIGHT / CELL_SIZE || maze[x][y] == 1 || visited[x][y]) {
        return 0;
    }
    
    visited[x][y] = 1;
    
    // 临时标记当前探索路径点（黄色）
    setfillcolor(EXPLORING_COLOR);
    solidrectangle(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
    FlushBatchDraw(); // 刷新显示
    Sleep(10); // 短暂延迟，使过程可见
    
    if (solveMaze(x + 1, y, ex, ey) || solveMaze(x - 1, y, ex, ey) || 
        solveMaze(x, y + 1, ex, ey) || solveMaze(x, y - 1, ex, ey)) {
        maze[x][y] = 2; // 标记为路径
        setfillcolor(SOLUTION_COLOR);
        solidrectangle(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
        
        // 重新标记起点，确保它始终是绿色的
        if (x == start.x && y == start.y) {
            setfillcolor(START_COLOR);
            solidrectangle(start.x * CELL_SIZE, start.y * CELL_SIZE, (start.x + 1) * CELL_SIZE, (start.y + 1) * CELL_SIZE);
        }
        
        FlushBatchDraw(); // 刷新显示
        Sleep(50);
        return 1;
    }
    
    // 如果当前点不在路径上，恢复为黑色（通道）
    setfillcolor(PATH_COLOR);
    solidrectangle(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
    FlushBatchDraw(); // 刷新显示
    Sleep(10);
    
    return 0;
}

int main() {
    initgraph(WIDTH, HEIGHT);
    srand(time(NULL));
    
    // 开启批量绘图模式，提高绘图效率
    BeginBatchDraw();

    initMaze();
    generateMaze(start.x, start.y);
    drawMaze();

    // 显示开始提示
    RECT r = {WIDTH/2 - 150, HEIGHT/2 - 30, WIDTH/2 + 150, HEIGHT/2 + 30};
    settextstyle(20, 0, _T("宋体"));
    settextcolor(RED);
    drawtext(_T("绿色: 起点, 蓝色: 终点\n按任意键开始求解"), &r, DT_CENTER | DT_VCENTER);
    FlushBatchDraw();
    
    _getch(); // 等待用户按键
    
    // 重新绘制迷宫（覆盖提示文字）
    drawMaze();
    
    memset(visited, 0, sizeof(visited));
    solveMaze(start.x, start.y, end.x, end.y);
    
    // 重新标记起点和终点，确保它们在求解后仍然可见
    setfillcolor(START_COLOR);
    solidrectangle(start.x * CELL_SIZE, start.y * CELL_SIZE, (start.x + 1) * CELL_SIZE, (start.y + 1) * CELL_SIZE);
    
    setfillcolor(END_COLOR);
    solidrectangle(end.x * CELL_SIZE, end.y * CELL_SIZE, (end.x + 1) * CELL_SIZE, (end.y + 1) * CELL_SIZE);
    
    FlushBatchDraw();
    
    // 显示完成提示
    settextstyle(20, 0, _T("宋体"));
    settextcolor(RED);
    drawtext(_T("迷宫已解决！按任意键退出"), &r, DT_CENTER | DT_VCENTER);
    FlushBatchDraw();
    
    // 结束批量绘图模式
    EndBatchDraw();

    _getch(); // 等待用户按键后退出
    closegraph();
    return 0;
}
