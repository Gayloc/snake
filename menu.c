#include <stdio.h>
#include "menu.h"

int menu() {
    int input;
    printf("1��ʼ2����3���������˳�\n");
    scanf("%d", &input);
    return input;
}

void about() {
    printf("���������2307��ż���8008123201\n");
}

void score() {
    FILE *f = fopen("score.txt", "r");
    int score = 0;
    fscanf(f,"%d", &score);
    
    printf("�ϴη���: %d\n", score);
    fclose(f);
}