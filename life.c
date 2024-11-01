/*
 コンウェイのライフゲーム
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define I 40 // 行数
#define J 40 // 列数

char world[I][J];

void draw(int gen)
{
    for (int i = 0; i < I; i++) {
        for (int j = 0; j < J; j++)
            printf(world[i][j] ? "◽️" : "  ");
        printf("\n");
    }
    printf("%6d世代\n", gen);
}

int count_neighbors(int i, int j)
{
    int n = 0;
    for (int di = -1; di < 2; di++)
        for (int dj = -1; dj < 2; dj++) {
            if (di == 0 && dj == 0) continue; // 自分は数えない
            n += world[(i + di + I) % I][(j + dj + J) % J];
        }
    return n;
}

void update(void)
{
    char next[I][J];
    for (int i = 0; i < I; i++)
        for (int j = 0; j < J; j++) {
            const int c = count_neighbors(i, j);
            next[i][j] = c == 2 ? world[i][j] : c == 3 ? 1 : 0;
        }
    memcpy(world, next, sizeof(world));
}

void init(void)
{
    srand(10); // 種10を変えると盤面の初期パターンが変わる
    for (int i = 0; i < I; i++)
        for (int j = 0; j < J; j++)
            //world[i][j] = rand() * 2.0 / (RAND_MAX + 1.0);
            world[i][j] = rand() % 2;
}

void clear(void)
{
    printf("\033c\033[0;0H"); // ターミナル初期化&カーソルを先頭に
}

void wait(int ms)
{
    struct timespec rem, req = { 0, ms * 1000000 };
    while(nanosleep(&req, &rem) == -1) req = rem;
}

int main()
{
    int gen = 0;
    init();
    for (;;) {
        clear();
        draw(gen++);
        update();
        wait(30); // 更新の間隔は適宜調整(ms)
    }
}
