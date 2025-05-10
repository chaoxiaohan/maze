#include "common.h"
#include "maze.h"
#include "graphics.h"
#include "pathfinder.h"
#include <string.h> // ����memset����

int main() {
    // ��ʼ��ͼ�δ���
    initgraph(WIDTH, HEIGHT);
    srand(time(NULL));

    // ����������ͼģʽ����߻�ͼЧ��
    BeginBatchDraw();

    // ��ʼ���������Թ�
    initMaze();
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

    // ���±�������յ㣬ȷ��������������Ȼ�ɼ�
    setfillcolor(START_COLOR);
    solidrectangle(start.x * CELL_SIZE, start.y * CELL_SIZE, (start.x + 1) * CELL_SIZE, (start.y + 1) * CELL_SIZE);

    setfillcolor(END_COLOR);
    solidrectangle(end.x * CELL_SIZE, end.y * CELL_SIZE, (end.x + 1) * CELL_SIZE, (end.y + 1) * CELL_SIZE);

    FlushBatchDraw();

    // ��ʾ�����ʾ
    showMessage(_T("�Թ��ѽ������������˳�"));

    // ����������ͼģʽ
    EndBatchDraw();

    _getch(); // �ȴ��û��������˳�
    closegraph();
    return 0;
}
