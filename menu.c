#include <stdio.h>
#include "menu.h"

int menu() {
    int input;
    printf(" ________  ________   ________  ___  __    _______      \n");
    printf("|\\   ____\\|\\   ___  \\|\\   __  \\|\\  \\|\\  \\ |\\  ___ \\     \n");
    printf("\\ \\  \\___|\\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\/  /|\\ \\   __/|    \n");
    printf(" \\ \\_____  \\ \\  \\\\ \\  \\ \\   __  \\ \\   ___  \\ \\  \\_|/__  \n");
    printf("  \\|____|\\  \\ \\  \\\\ \\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\     \n");
    printf("    ____\\_\\  \\ \\__\\\\ \\__\\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\_______\\\n");
    printf("   |\\_________\\|__| \\|__|\\|__|\\|__|\\|__| \\|__|\\|_______|\n");
    printf("   \\|_________|                                         \n");
    printf("����1��ʼ��Ϸ\n");
    printf("����2�鿴��Ϣ\n");
    printf("����3�鿴��߷���\n");
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
    
    printf("��߷���: %d\n", score);
    fclose(f);
}