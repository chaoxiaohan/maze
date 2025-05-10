#include "pathfinder.h"
#include "maze.h"
#include "graphics.h"

bool testPath(int x, int y) {
    // 如果到达终点，返回true
    if (x == end.x && y == end.y) {
        return true;
    }

    // 标记当前格子为已访问
    visited[x][y] = 1;

    // 四个方向：上、右、下、左
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 检查新位置是否有效且是通道且未访问
        if (nx >= 0 && nx < WIDTH / CELL_SIZE && ny >= 0 && ny < HEIGHT / CELL_SIZE &&
            maze[nx][ny] == 0 && !visited[nx][ny]) {
            if (testPath(nx, ny)) {
                return true;
            }
        }
    }

    return false;
}

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

    // 检查是否是通道且未访问
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
