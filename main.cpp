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

// ������ɫ������ʹ������ɶ�
const COLORREF WALL_COLOR = WHITE;       // ǽ����ɫ����ɫ��
const COLORREF PATH_COLOR = BLACK;       // ͨ����ɫ����ɫ��
const COLORREF START_COLOR = GREEN;      // �����ɫ����ɫ��
const COLORREF END_COLOR = BLUE;         // �յ���ɫ����ɫ��
const COLORREF SOLUTION_COLOR = RED;     // ���·����ɫ����ɫ��
const COLORREF EXPLORING_COLOR = YELLOW; // ̽������ɫ����ɫ��

// ���������յ�λ��
Point start = {0, 0};
Point end = {WIDTH / CELL_SIZE - 1, HEIGHT / CELL_SIZE - 1};

void initMaze() {
    for (int i = 0; i < WIDTH / CELL_SIZE; i++) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; j++) {
            maze[i][j] = 1; // ��ʼ��Ϊǽ����ɫ��
            visited[i][j] = 0;
        }
    }
}

void drawMaze() {
    for (int i = 0; i < WIDTH / CELL_SIZE; i++) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; j++) {
            if (maze[i][j] == 1) { // ǽ
                setfillcolor(WALL_COLOR);
            } else if (maze[i][j] == 0) { // ͨ��
                setfillcolor(PATH_COLOR);
            } else if (maze[i][j] == 2) { // ���·��
                setfillcolor(SOLUTION_COLOR);
            }
            solidrectangle(i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE);
        }
    }

    // ��������յ�
    setfillcolor(START_COLOR);
    solidrectangle(start.x * CELL_SIZE, start.y * CELL_SIZE, (start.x + 1) * CELL_SIZE, (start.y + 1) * CELL_SIZE);
    
    setfillcolor(END_COLOR);
    solidrectangle(end.x * CELL_SIZE, end.y * CELL_SIZE, (end.x + 1) * CELL_SIZE, (end.y + 1) * CELL_SIZE);
    
    // ȷ�����Ʋ���������ʾ
    FlushBatchDraw();
}

void generateMaze(int x, int y) {
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    visited[x][y] = 1;
    maze[x][y] = 0; // ����Ϊͨ������ɫ��

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
            maze[nx][ny] = 0; // ����Ϊͨ������ɫ��
            generateMaze(nnx, nny);
        }
    }
}

// �޸���⺯����ʹ���ں�ɫͨ����Ѱ��·��
int solveMaze(int x, int y, int ex, int ey) {
    if (x == ex && y == ey) {
        maze[x][y] = 2; // ����յ�
        setfillcolor(SOLUTION_COLOR);
        solidrectangle(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
        
        // ���±���յ㣬ȷ����ʼ������ɫ��
        setfillcolor(END_COLOR);
        solidrectangle(end.x * CELL_SIZE, end.y * CELL_SIZE, (end.x + 1) * CELL_SIZE, (end.y + 1) * CELL_SIZE);
        
        FlushBatchDraw(); // ˢ����ʾ
        Sleep(50);
        return 1;
    }
    
    // ע�⣺�����Ϊ����Ƿ���ͨ����maze[x][y] == 0����������ǽ
    if (x < 0 || x >= WIDTH / CELL_SIZE || y < 0 || y >= HEIGHT / CELL_SIZE || maze[x][y] == 1 || visited[x][y]) {
        return 0;
    }
    
    visited[x][y] = 1;
    
    // ��ʱ��ǵ�ǰ̽��·���㣨��ɫ��
    setfillcolor(EXPLORING_COLOR);
    solidrectangle(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
    FlushBatchDraw(); // ˢ����ʾ
    Sleep(10); // �����ӳ٣�ʹ���̿ɼ�
    
    if (solveMaze(x + 1, y, ex, ey) || solveMaze(x - 1, y, ex, ey) || 
        solveMaze(x, y + 1, ex, ey) || solveMaze(x, y - 1, ex, ey)) {
        maze[x][y] = 2; // ���Ϊ·��
        setfillcolor(SOLUTION_COLOR);
        solidrectangle(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
        
        // ���±����㣬ȷ����ʼ������ɫ��
        if (x == start.x && y == start.y) {
            setfillcolor(START_COLOR);
            solidrectangle(start.x * CELL_SIZE, start.y * CELL_SIZE, (start.x + 1) * CELL_SIZE, (start.y + 1) * CELL_SIZE);
        }
        
        FlushBatchDraw(); // ˢ����ʾ
        Sleep(50);
        return 1;
    }
    
    // �����ǰ�㲻��·���ϣ��ָ�Ϊ��ɫ��ͨ����
    setfillcolor(PATH_COLOR);
    solidrectangle(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
    FlushBatchDraw(); // ˢ����ʾ
    Sleep(10);
    
    return 0;
}

int main() {
    initgraph(WIDTH, HEIGHT);
    srand(time(NULL));
    
    // ����������ͼģʽ����߻�ͼЧ��
    BeginBatchDraw();

    initMaze();
    generateMaze(start.x, start.y);
    drawMaze();

    // ��ʾ��ʼ��ʾ
    RECT r = {WIDTH/2 - 150, HEIGHT/2 - 30, WIDTH/2 + 150, HEIGHT/2 + 30};
    settextstyle(20, 0, _T("����"));
    settextcolor(RED);
    drawtext(_T("��ɫ: ���, ��ɫ: �յ�\n���������ʼ���"), &r, DT_CENTER | DT_VCENTER);
    FlushBatchDraw();
    
    _getch(); // �ȴ��û�����
    
    // ���»����Թ���������ʾ���֣�
    drawMaze();
    
    memset(visited, 0, sizeof(visited));
    solveMaze(start.x, start.y, end.x, end.y);
    
    // ���±�������յ㣬ȷ��������������Ȼ�ɼ�
    setfillcolor(START_COLOR);
    solidrectangle(start.x * CELL_SIZE, start.y * CELL_SIZE, (start.x + 1) * CELL_SIZE, (start.y + 1) * CELL_SIZE);
    
    setfillcolor(END_COLOR);
    solidrectangle(end.x * CELL_SIZE, end.y * CELL_SIZE, (end.x + 1) * CELL_SIZE, (end.y + 1) * CELL_SIZE);
    
    FlushBatchDraw();
    
    // ��ʾ�����ʾ
    settextstyle(20, 0, _T("����"));
    settextcolor(RED);
    drawtext(_T("�Թ��ѽ������������˳�"), &r, DT_CENTER | DT_VCENTER);
    FlushBatchDraw();
    
    // ����������ͼģʽ
    EndBatchDraw();

    _getch(); // �ȴ��û��������˳�
    closegraph();
    return 0;
}
