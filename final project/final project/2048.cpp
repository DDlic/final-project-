#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a[4][4] = { 0 };  // 4x4的遊戲板
int pointcount = 0;
// 顯示遊戲板
void show() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d    ", a[i][j]);
		}
		printf("\n\n");
	}
}

// 清除遊戲板
void clearScreen() {
	printf("\033[2J\033[H");  // \033[2J用來清除整個畫面、\033[H則用來將光標移動到左上角
}

// 生成隨機數，2的機率是4
int random(int Max) {
	if (rand() % Max == 0) {
		return 4;
	}
	else {
		return 2;
	}
}

// 生成隨機位置
int randomPos(int Max) {
	return rand() % Max;
}

// 在空白位置生成新的數字
void addNewNumber() {
	int iPos = randomPos(4);
	int jPos = randomPos(4);
	while (a[iPos][jPos] != 0) {
		iPos = randomPos(4);
		jPos = randomPos(4);
	}
	a[iPos][jPos] = random(10);
}

// 遊戲初始化
void newGame() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			a[i][j] = 0;
		}
	}
	int iFirstPos = randomPos(4);
	int jFirstPos = randomPos(4);
	a[iFirstPos][jFirstPos] = random(10);
	addNewNumber();
	show();
}

// 合併相鄰相同數字並移動
void realChange(int *a0, int *a1, int *a2, int *a3) {
	int a[4] = { *a0, *a1, *a2, *a3 };
	int sum = 0;

	for (int i = 0; i < 4; i++) {
		sum = 0;
		for (int j = i; j < 4; j++) {
			sum += a[j];
		}
		if (sum == 0) {
			break;
		}

		while (a[i] == 0) {
			for (int j = i; j < 3; j++) {
				a[j] = a[j + 1];
			}
			a[3] = 0;
		}
	}

	if (a[0] == a[1]) {
		if (a[2] == a[3]) {
			a[0] = 2 * a[0];
			pointcount += a[0];
			a[1] = 2 * a[2];
			pointcount += a[2];
			a[2] = 0;
			a[3] = 0;
		}
		else {
			a[0] = 2 * a[0];
			pointcount += a[0];
			a[1] = a[2];
			a[2] = a[3];
			a[3] = 0;
		}
	}
	else {
		if (a[1] == a[2]) {
			a[1] = 2 * a[1];
			pointcount += a[1];
			a[2] = a[3];
			a[3] = 0;
		}
		else {
			if (a[2] == a[3]) {
				a[2] = 2 * a[2];
				pointcount += a[2];
				a[3] = 0;
			}
		}
	}
	*a0 = a[0];
	*a1 = a[1];
	*a2 = a[2];
	*a3 = a[3];
}

// 向上移動
void upChange() {
	for (int j = 0; j < 4; j++) {
		realChange(&a[0][j], &a[1][j], &a[2][j], &a[3][j]);
	}
	addNewNumber();
	clearScreen();
	show();
	printf("Your Point:%d\n", pointcount);
	printf("right\n");
}

// 向下移動
void downChange() {
	for (int j = 0; j < 4; j++) {
		realChange(&a[3][j], &a[2][j], &a[1][j], &a[0][j]);
	}
	addNewNumber();
	clearScreen();
	show();
	printf("Your Point:%d\n", pointcount);
	printf("right\n");
}

// 向左移動
void leftChange() {
	for (int i = 0; i < 4; i++) {
		realChange(&a[i][0], &a[i][1], &a[i][2], &a[i][3]);
	}
	addNewNumber();
	clearScreen();
	show();
	printf("Your Point:%d\n", pointcount);
	printf("right\n");
}

// 向右移動
void rightChange() {
	for (int i = 0; i < 4; i++) {
		realChange(&a[i][3], &a[i][2], &a[i][1], &a[i][0]);
	}
	addNewNumber();
	clearScreen();
	show();
	printf("Your Point:%d\n", pointcount);
	printf("right\n");
}

// 判斷輸入的方向
int judge(char chGet) {
	switch (chGet) {
	case 'n':
		clearScreen();
		newGame();
		printf("請輸入: wsad上下左右、q退出、n新遊戲\n");
		break;
	case 'w':
		upChange();
		break;
	case 'a':
		leftChange();
		break;
	case 's':
		downChange();
		break;
	case 'd':
		rightChange();
		break;
	case 'q':
		return 0;
	default:
		break;
	}
	return 1;
}

int main() {
	printf("請輸入: wsad上下左右、q退出、n新遊戲\n");
	srand((int)time(0));
	newGame();
	char chGet;
	while (1) {
		scanf("%c", &chGet);
		if (!judge(chGet)) {
			printf("game over\n");
			break;
		}
	}
	return 0;
}
