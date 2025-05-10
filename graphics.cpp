#include "graphics.h"
#include "maze.h"

void drawMaze() {
    for (int i = 0; i < WIDTH / CELL_SIZE; i++) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; j++) {
            if (maze[i][j] == 1) { // 墙
                setfillcolor(WALL_COLOR);
            }
            else if (maze[i][j] == 0) { // 通道
                setfillcolor(PATH_COLOR);
            }
            else if (maze[i][j] == 2) { // 解决路径
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

void showMessage(const TCHAR* message) {
    // 显示提示信息
    RECT r = { WIDTH / 2 - 150, HEIGHT / 2 - 30, WIDTH / 2 + 150, HEIGHT / 2 + 30 };
    settextstyle(20, 0, _T("宋体"));
    settextcolor(RED);
    drawtext(message, &r, DT_CENTER | DT_VCENTER);
    FlushBatchDraw();
}
