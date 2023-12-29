#include <stdio.h>
#include "menu.h"

int menu() {
    int input;
    printf("1开始2关于3分数其他退出\n");
    scanf("%d", &input);
    return input;
}

void about() {
    printf("-------------------------------\n");
}

int score() {
    FILE *f = fopen("score.json", "r");
}