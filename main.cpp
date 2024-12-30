#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <easyx.h>
#include <math.h>
#include <conio.h>

# 2048

int matrix[4][4];
#define GRID_SIZE   120 // 格子的宽度和高度
#define INTERVAL    15  // 格子的间隔
enum Color {
    zero = RGB(205, 193, 180),//0的颜色
    twoTo1 = RGB(238, 228, 218),//2的颜色
    twoTo2 = RGB(237, 224, 200),//4的颜色
    twoTo3 = RGB(242, 177, 121),//8的颜色
    twoTo4 = RGB(245, 149, 99),//16的颜色
    twoTo5 = RGB(246, 124, 95),//32的颜色
    twoTo6 = RGB(246, 94, 59),//64的颜色
    twoTo7 = RGB(242, 177, 121),//128的颜色
    twoTo8 = RGB(237, 204, 97),//256的颜色
    twoTo9 = RGB(255, 0, 128),//512的颜色
    twoTo10 = RGB(145, 0, 72),//1024的颜色
    twoTo11 = RGB(242, 17, 158),//2048的颜色
    back = RGB(187, 173, 160),//背景颜色
};
Color colors[13] = {zero, twoTo1, twoTo2, twoTo3, twoTo4, twoTo5, twoTo6, twoTo7, twoTo8, twoTo9, twoTo10, twoTo11,
                    back};

// 随机数生成2、4,2的概率更高
int createNumber() {
    if (rand() % 10 != 0) {
        return 2;
    } else {
        return 4;
    }
}

//  空白处填充数
void matrixFillNumber() {
    while (true) {
            int r = rand() % 4;
            int c = rand() % 4;
        if (matrix[r][c] == 0) {
            matrix[r][c] = 2;
            break;
        }
    }
}

void init() {
    srand(time(NULL));
    for (int i = 0; i < 2; i++) {
        matrixFillNumber();
    }
}

void t() {
    int r = rand() % 4;
    int c = rand() % 4;
    if (matrix[r][c] == 0) {
        matrix[r][c] = createNumber();
    }
}

//int matrix[4][4] = {{0, 2, 2, 0},
//                    {2, 0, 2, 2},
//                    {0, 4, 4, 2},
//                    {2, 4, 4, 4}};

// 反转数组下标交换函数
int *get(int x, int y, char inv) {
    switch (inv) {
        case 'i':
            return &matrix[y][x];
        default:
            return &matrix[x][y];
    }
}

// 合并函数
void ty(int begin, int c, int *temp, int be, char inv,bool* isMove) {
    if (*get(begin, c, inv) != 0) {
        if (*get(*temp, c, inv) == 0) {
            *get(*temp, c, inv) = *get(begin, c, inv);
            *get(begin, c, inv) = 0;
            *isMove = true;
        } else if (*get(*temp, c, inv) == *get(begin, c, inv)) {
            *get(*temp, c, inv) *= 2;
            *get(begin, c, inv) = 0;
            *temp += be;
            *isMove = true;
        } else {
            *get(*temp + be, c, inv) = *get(begin, c, inv);
            if ((*temp + be) != begin) {
                *get(begin, c, inv) = 0;
                *isMove = true;
            }
            *temp += be;
        }
    }
}

//  移动函数
void move(char direcainon) {
    bool isMove = false;
    char inv;
    if (direcainon == 'r' || direcainon == 'l') inv = 'i';
    if (direcainon == 'u' || direcainon == 'l') {
        for (int c = 0; c < 4; c++) {
            int temp = 0;
            for (int begin = 1; begin < 4; begin++) {
                ty(begin, c, &temp, 1, inv,&isMove);
            }
        }
    } else if (direcainon == 'd' || direcainon == 'r') {
        for (int c = 0; c < 4; c++) {
            int temp = 3;
            for (int begin = 2; begin >= 0; begin--) {
                ty(begin, c, &temp, -1, inv,&isMove);
            }
        }
    }
    if (isMove){
        matrixFillNumber();
    }
}

void kb() {
    //  获取键盘按键
    int key = _getch();
    switch (key) {
        case 'W':
        case 'w':
        case '72':
            move('u');
//          matrixFillNumber();
            break;
        case 'S':
        case 's':
        case '80':
            move('d');
//            matrixFillNumber();
            break;
        case 'A':
        case 'a':
        case '75':
            move('l');
//            matrixFillNumber();
            break;
        case 'D':
        case 'd':
        case '77':
            move('r');
//            matrixFillNumber();
            break;
    }
}

void draw() {
    //  画格子
    setbkcolor(RGB(187, 173, 160));
    cleardevice();
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            //  求格子坐标
            int x = k * GRID_SIZE + (k + 1) * INTERVAL;
            int y = i * GRID_SIZE + (i + 1) * INTERVAL;
            int index = matrix[i][k] ? log2(matrix[i][k]) : 0;
            setfillcolor(colors[index]);
            solidroundrect(x, y, x + GRID_SIZE, y + GRID_SIZE, 15, 15);
            if (matrix[i][k]) {
                //  写入数据,但是要先把数字转为字符串
                char numberStr[5] = {0};
                sprintf(numberStr, "%d ", matrix[i][k]);
                settextcolor(RGB(119, 110, 101));
                settextstyle(60, 0, "Arial Black");
                setbkmode(TRANSPARENT);
                //  文字居中
                int hspace = (GRID_SIZE - textwidth(numberStr)) / 2;
                int vspace = (GRID_SIZE - textheight(numberStr)) / 2;
                outtextxy(x + hspace + 9, y + vspace, numberStr);
            }

            printf("%5d ", matrix[i][k]);
        }
        printf("\n");
    }
    printf("----------------------\n");
}


int main() {

    // 窗口
    initgraph(4 * GRID_SIZE + (4 + 1) * INTERVAL, 4 * GRID_SIZE + (4 + 1) * INTERVAL, EX_SHOWCONSOLE);

    init();
    while (true){
        draw();
        kb();
    }

//    while (true){
//        int key = _getch();
//        printf("%d\n",key);
//    }

    return 0;
}