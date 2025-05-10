#include "maze.h"
#include "pathfinder.h"
#include <string.h> // 用于memset函数

// 定义迷宫数组和访问过的数组
int maze[WIDTH / CELL_SIZE][HEIGHT / CELL_SIZE];
int visited[WIDTH / CELL_SIZE][HEIGHT / CELL_SIZE];

// 定义起点和终点位置
Point start = { 0, 0 };
Point end = { WIDTH / CELL_SIZE - 1, HEIGHT / CELL_SIZE - 1 };

void initMaze() {
    for (int i = 0; i < WIDTH / CELL_SIZE; i++) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; j++) {
            maze[i][j] = 1; // 初始化为墙（白色）
            visited[i][j] = 0;
        }
    }
}

void generateMaze(int x, int y) {
    int directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    visited[x][y] = 1;
    maze[x][y] = 0; // 设置为通道（黑色）

    // 随机打乱方向
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

    // 递归生成迷宫
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

void ensureEndpointAccessible() {
    // 确保终点是通道
    maze[end.x][end.y] = 0;

    // 如果终点周围全是墙，至少打通一个方向
    bool hasPath = false;
    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, -1, 0, 1 };

    for (int i = 0; i < 4; i++) {
        int nx = end.x + dx[i];
        int ny = end.y + dy[i];

        if (nx >= 0 && nx < WIDTH / CELL_SIZE && ny >= 0 && ny < HEIGHT / CELL_SIZE) {
            if (maze[nx][ny] == 0) { // 如果周围有通道
                hasPath = true;
                break;
            }
        }
    }

    // 如果终点周围没有通道，打通一条路
    if (!hasPath) {
        // 尝试打通左边
        if (end.x > 0) {
            maze[end.x - 1][end.y] = 0;
        }
        // 如果不能打通左边，尝试打通上边
        else if (end.y > 0) {
            maze[end.x][end.y - 1] = 0;
        }
    }
}

bool checkPathExists() {
    // 重置访问数组
    memset(visited, 0, sizeof(visited));

    // 使用路径查找函数检查路径
    return testPath(start.x, start.y);
}

void createDirectPath() {
    int x = start.x;
    int y = start.y;

    // 沿着水平方向移动
    while (x != end.x) {
        x += (x < end.x) ? 1 : -1;
        maze[x][y] = 0; // 设置为通道
    }

    // 然后沿着垂直方向移动
    while (y != end.y) {
        y += (y < end.y) ? 1 : -1;
        maze[x][y] = 0; // 设置为通道
    }
}
