#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "controller.h"
#include "menu.h"

int get_food_axis(int max) //生成食物坐标
{
    srand((unsigned int)time(NULL));

    int lower_bound = 1;
    int upper_bound = max;

    int range = upper_bound - lower_bound + 1;

    int random_number = rand() % range + lower_bound;

    return random_number;
}

void food(int map[COL][ROW]) //使用食物坐标生成食物
{
    struct Point food_axis;

    do
    {
        food_axis.x = get_food_axis(COL - 1);
        food_axis.y = get_food_axis(ROW - 1);
    } while (map[food_axis.x][food_axis.y] != 0);

    map[food_axis.x][food_axis.y] = -2;
}

void init(int map[COL][ROW]) //地图初始化
{
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < ROW; j++)
        {
            if (i == 0 || j == 0 || i == COL - 1 || j == ROW - 1)
            {
                map[i][j] = -1;
            }
            else
            {
                map[i][j] = 0;
            }
        }
    }
    map[COL / 2][ROW / 2] = 3;
    map[COL / 2][ROW / 2 - 1] = 2;
    map[COL / 2][ROW / 2 - 2] = 1;
}

void printMap(int map[COL][ROW]) //打印地图
{
    system("cls");
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < ROW; j++)
        {
            if (map[i][j] == -1)
            {
                printf("#"); //墙壁
                // printf("%d",map[i][j]);
            }
            else if (map[i][j] == -2)
            {
                printf("F"); //食物
                // printf("%d",map[i][j]);
            }
            else
            {
                if (map[i][j])
                {
                    printf("X"); //身体
                    // printf("%d",map[i][j]);
                }
                else
                {
                    printf(" "); //空白
                    // printf("%d",map[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

int start() //主菜单，返回0时程序结束
{
    for (;;)
    {
        switch (menu())
        {
        case 1:
            return 1;
            break;

        case 2:
            about();
            continue;

        case 3:
            score();
            continue;

        case 4:
            help();
            continue;

        default:
            return 0;
            break;
        }
        break;
    }
}

void move(int map[COL][ROW]) //让地图中蛇的身体部分数字减一，实现移动效果
{
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < ROW; j++)
        {
            if (map[i][j] != -1 && map[i][j] != 0 && map[i][j] != -2)
            {
                map[i][j]--;
            }
        }
    }
}

int forward(int map[COL][ROW], struct Point *head, enum Direction direction, int *length) //移动蛇头
{
    switch (direction)
    {
    case down:
        if (map[head->y + 1][head->x] != 0)
        {
            if (map[head->y + 1][head->x] == -2)
            {
                *length = *length + 1; //对应方向位置赋值当前长度
                food(map); //生成食物
            }
            else
            {
                printf("Game Over!,分数%d\n", *length);
                return 0;
            }
        }
        else
        {
            move(map);
        }
        map[head->y + 1][head->x] = *length;
        head->y++;
        break;

    case left:
        if (map[head->y][head->x - 1] != 0)
        {
            if (map[head->y][head->x - 1] == -2)
            {
                *length = *length + 1;
                food(map);
            }
            else
            {
                printf("Game Over!,分数%d\n", *length);
                return 0;
            }
        }
        else
        {
            move(map);
        }
        map[head->y][head->x - 1] = *length;
        head->x--;
        break;

    case up:
        if (map[head->y - 1][head->x] != 0)
        {
            if (map[head->y - 1][head->x] == -2)
            {
                *length = *length + 1;
                food(map);
            }
            else
            {
                printf("Game Over!,分数%d\n", *length);
                return 0;
            }
        }
        else
        {
            move(map);
        }
        map[head->y - 1][head->x] = *length;
        head->y--;
        break;

    case right:
        if (map[head->y][head->x + 1] != 0)
        {
            if (map[head->y][head->x + 1] == -2)
            {
                *length = *length + 1;
                food(map);
            }
            else
            {
                printf("Game Over!,分数%d\n", *length);
                return 0;
            }
        }
        else
        {
            move(map);
        }
        map[head->y][head->x + 1] = *length;
        head->x++;
        break;

    default:
        break; //忽略w,a,s,d以外的输入
    }
    return 1; //没有失败情况，返回1
}

int loop(int map[COL][ROW]) //游戏循环
{
    struct Point head = {ROW / 2, COL / 2}; //默认蛇的生成位置在中间
    int length = 3; //默认长度（与init函数中的初始化情况匹配）
    enum Direction direction = right; //默认方向
    food(map); //生成食物
    printMap(map);
    for (;;)
    {
        DWORD start_time = GetTickCount(); //操作系统提供当前时间
        int timeout_flag = 0; //计时结束标志

        while (!kbhit()) //如果键盘没有键被按下
        {
            DWORD current_time = GetTickCount(); //获取现在的时间

            if (current_time - start_time >= TIME) //如果超时
            {
                timeout_flag = 1;
                break;
            }
        }

        if (!timeout_flag) //如果没有超时
        {
            char ch = getch(); //获取但不等待键盘输入
            switch (ch)
            {
            case 'w':
            case 'W':
                if (direction == right || direction == left)
                {
                    direction = up;
                }
                timeout_flag = 1;
                break;

            case 'a':
            case 'A':
                if (direction == up || direction == down)
                {
                    direction = left;
                }
                timeout_flag = 1;
                break;

            case 's':
            case 'S':
                if (direction == right || direction == left)
                {
                    direction = down;
                }
                timeout_flag = 1;
                break;

            case 'd':
            case 'D':
                if (direction == up || direction == down)
                {
                    direction = right;
                }
                timeout_flag = 1;
                break;

            default:
                timeout_flag = 1;
                break;
            }
        }

        if (!forward(map, &head, direction, &length)) //如果游戏失败
        {
            break;
        }
        printMap(map);
    }
    return length; //返回本局游戏分数
}
