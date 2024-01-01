#include "controller.h"
#include <stdio.h>

int getScore() //获取文件中的最高分数并返回
{
    FILE *f = fopen("score.txt", "r");
    int score = 0;
    fscanf(f,"%d", &score);
    
    return score;
    fclose(f);
}

int main() //程序入口
{
    int map[COL][ROW]; //地图

    while (start()) //进入主菜单
    {
        init(map);
        int length = loop(map); //进入游戏循环并记录长度
        
        if(getScore()<length)
        {
            FILE *file = fopen("score.txt", "w");
            fprintf(file, "%d", length);
            fclose(file);
        }
    }
    return 0;
}

