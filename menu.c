#include <stdio.h>
#include "menu.h"

int menu() {
    int input;
    printf("1��ʼ2����3���������˳�\n");
    scanf("%d", &input);
    return input;
}

void about() {
    printf("-------------------------------\n");
}

int score() {
    FILE *f = fopen("score.json", "r");
}