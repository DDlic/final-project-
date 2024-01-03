#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BOARD_SIZE 5

int a[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { 0 };  // �C���O
int pointcount = 0, bigpoint[3] = {0, 0, 0};  // �̰����A����3x3, 4x4, 5x5�C���O
int boardSize;  // �C���O�j�p

void show() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n\n");
    }
}

void clearScreen() {
    // �M�̩R�O�ھھާ@�t�Τ��P�i�঳�Ҥ��P
    system("cls"); // Windows
    // system("clear"); // Unix/Linux
}

int random(int Max) {
    return (rand() % Max == 0) ? 4 : 2;
}

int randomPos(int Max) {
    return rand() % Max;
}

void addNewNumber() {
    int iPos = randomPos(boardSize);
    int jPos = randomPos(boardSize);
    while (a[iPos][jPos] != 0) {
        iPos = randomPos(boardSize);
        jPos = randomPos(boardSize);
    }
    a[iPos][jPos] = random(10);
}

void newGame(int size) {
    boardSize = size;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            a[i][j] = 0;
        }
    }
    printf("�̰����G%d\n", bigpoint[size - 3]);
    pointcount = 0;
    int iFirstPos = randomPos(boardSize);
    int jFirstPos = randomPos(boardSize);
    a[iFirstPos][jFirstPos] = random(10);
    addNewNumber();
    show();
}

void realChange(int *line, int size) {
    int i, j;
    // ���ʫD�s����
    for (i = 0, j = 0; i < size; i++) {
        if (line[i] != 0) {
            line[j++] = line[i];
        }
    }
    while (j < size) {
        line[j++] = 0;
    }

    // �X�֬ۦP������
    for (i = 0; i < size - 1; i++) {
        if (line[i] == line[i + 1] && line[i] != 0) {
            line[i] *= 2;
            pointcount += line[i];
            for (j = i + 1; j < size - 1; j++) {
                line[j] = line[j + 1];
            }
            line[size - 1] = 0;
        }
    }
}

void transpose() {
    int temp;
    for (int i = 0; i < boardSize; i++) {
        for (int j = i + 1; j < boardSize; j++) {
            temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
        }
    }
}

void reverse() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize / 2; j++) {
            int temp = a[i][j];
            a[i][j] = a[i][boardSize - j - 1];
            a[i][boardSize - j - 1] = temp;
        }
    }
}

void moveAndMerge(int isReverse, int isTranspose) {
    if (isTranspose) {
        transpose();
    }
    if (isReverse) {
        reverse();
    }

    for (int i = 0; i < boardSize; i++) {
        realChange(a[i], boardSize);
    }

    if (isReverse) {
        reverse();
    }
    if (isTranspose) {
        transpose();
    }

    addNewNumber();
    clearScreen();
    show();
    printf("�z�����ơG%d\n", pointcount);
}

void upChange() {
    moveAndMerge(0, 1);
    printf("�W\n");
}

void downChange() {
    moveAndMerge(1, 1);
    printf("�U\n");
}

void leftChange() {
    moveAndMerge(0, 0);
    printf("��\n");
}

void rightChange() {
    moveAndMerge(1, 0);
    printf("�k\n");
}

int isGameOver() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (a[i][j] == 0) {
                return 0;
            }
            if (j < boardSize - 1 && a[i][j] == a[i][j + 1]) {
                return 0;
            }
            if (i < boardSize - 1 && a[i][j] == a[i + 1][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    srand(time(NULL));
    int size;
    printf("�п�J�C���O�j�p�]3-5�^: ");
    scanf("%d", &size);
    if (size < 3 || size > 5) {
        printf("�L�Ī��j�p�C�C���O�j�p�N�]�� 4x4�C\n");
        size = 4;
    }

    char op;
    newGame(size);
    while (1) {
        if (isGameOver()) {
            printf("�C�������I�z�����ơG%d\n", pointcount);
            if (pointcount > bigpoint[size - 3]) {
                bigpoint[size - 3] = pointcount;
            }
            printf("�O�_�A���@���H(y/n): ");
            scanf(" %c", &op);
            if (op == 'y' || op == 'Y') {
                printf("�п�J�s���C���O�j�p�]3-5�^: ");
                scanf("%d", &size);
                newGame(size);
            } else {
                break;
            }
        }

        printf("�п�J�ާ@�]w=�W, s=�U, a=��, d=�k, n=���s�}�l�^: ");
        scanf(" %c", &op);
        if (op == 'n') {
            if (pointcount > bigpoint[size - 3]) {
                bigpoint[size - 3] = pointcount;
            }
            printf("�п�J�s���C���O�j�p�]3-5�^: ");
            scanf("%d", &size);
            newGame(size);
            continue;
        }
        switch (op) {
            case 'w': upChange(); break;
            case 's': downChange(); break;
            case 'a': leftChange(); break;
            case 'd': rightChange(); break;
            default: printf("�L�Ī���J�I\n"); break;
        }
    }
    return 0;
}


