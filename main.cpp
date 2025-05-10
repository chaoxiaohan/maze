#include "common.h"
#include "maze.h"
#include "graphics.h"
#include "pathfinder.h"
#include <string.h> // 用于memset函数

int main() {
    // 初始化图形窗口
    initgraph(WIDTH, HEIGHT);
    srand(time(NULL));

    // 开启批量绘图模式，提高绘图效率
    BeginBatchDraw();

    // 初始化并生成迷宫
    initMaze();
    generateMaze(start.x, start.y);

    // 确保终点可达
    ensureEndpointAccessible();

    // 检查是否有路径，如果没有，创建一条直接路径
    if (!checkPathExists()) {
        createDirectPath();
    }

    // 绘制迷宫
    drawMaze();

    // 显示开始提示
    showMessage(_T("绿色: 起点, 蓝色: 终点\n按任意键开始求解"));

    _getch(); // 等待用户按键

    // 重新绘制迷宫（覆盖提示文字）
    drawMaze();

    // 求解迷宫
    memset(visited, 0, sizeof(visited));
    solveMaze(start.x, start.y, end.x, end.y);

    // 重新标记起点和终点，确保它们在求解后仍然可见
    setfillcolor(START_COLOR);
    solidrectangle(start.x * CELL_SIZE, start.y * CELL_SIZE, (start.x + 1) * CELL_SIZE, (start.y + 1) * CELL_SIZE);

    setfillcolor(END_COLOR);
    solidrectangle(end.x * CELL_SIZE, end.y * CELL_SIZE, (end.x + 1) * CELL_SIZE, (end.y + 1) * CELL_SIZE);

    FlushBatchDraw();

    // 显示完成提示
    showMessage(_T("迷宫已解决！按任意键退出"));

    // 结束批量绘图模式
    EndBatchDraw();

    _getch(); // 等待用户按键后退出
    closegraph();
    return 0;
}
