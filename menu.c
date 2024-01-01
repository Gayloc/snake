#include <stdio.h>
#include "menu.h"

int menu() {
    int input;
    printf("1开始2关于3分数其他退出\n");
    scanf("%d", &input);
    return input;
}

void about() {
    printf("计算机二类2307班古佳乐8008123201\n");
}

void score() {
    FILE *f = fopen("score.txt", "r");
    int score = 0;
    fscanf(f,"%d", &score);
    
    printf("上次分数: %d\n", score);
    fclose(f);
}