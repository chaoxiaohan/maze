#include "common.h"
#include "maze.h"
#include "graphics.h"
#include "pathfinder.h"
#include <string.h> 

int main() {
    // ��ʼ��
    initgraph(WIDTH, HEIGHT);
    srand(time(NULL));
    BeginBatchDraw();
    initMaze();
    //�Թ�����
    generateMaze(start.x, start.y);
    // ȷ���յ�ɴ�
    ensureEndpointAccessible();
    // ����Ƿ���·�������û�У�����һ��ֱ��·��
    if (!checkPathExists()) {
        createDirectPath();
    }
    // �����Թ�
    drawMaze();
    // ��ʾ��ʼ��ʾ
    showMessage(_T("��ɫ: ���, ��ɫ: �յ�\n���������ʼ���"));
    _getch(); // �ȴ��û�����
    // ���»����Թ���������ʾ���֣�
    drawMaze();
    // ����Թ�
    memset(visited, 0, sizeof(visited));
    solveMaze(start.x, start.y, end.x, end.y);

    // ���±�������յ�
    setfillcolor(START_COLOR);
    solidrectangle(start.x * CELL_SIZE, start.y * CELL_SIZE, (start.x + 1) * CELL_SIZE, (start.y + 1) * CELL_SIZE);

    setfillcolor(END_COLOR);
    solidrectangle(end.x * CELL_SIZE, end.y * CELL_SIZE, (end.x + 1) * CELL_SIZE, (end.y + 1) * CELL_SIZE);

    FlushBatchDraw();

    // ��ʾ�����ʾ
    showMessage(_T("�Թ��ѽ������������˳�"));
    EndBatchDraw();
    _getch(); // �ȴ��û��������˳�
    closegraph();
    return 0;
}
