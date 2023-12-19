#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "controller.h"

int get_food_axis(int max)
{
    srand((unsigned int)time(NULL));

    int lower_bound = 1;
    int upper_bound = max;

    int range = upper_bound - lower_bound + 1;

    int random_number = rand() % range + lower_bound;

    return random_number;
}

void food(int map[COL][ROW])
{
    struct Point food_axis;

    do
    {
        food_axis.x = get_food_axis(COL - 1);
        food_axis.y = get_food_axis(ROW - 1);
    } while (map[food_axis.x][food_axis.y] != 0);

    map[food_axis.x][food_axis.y] = -2;
}

void init(int map[COL][ROW])
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

void printMap(int map[COL][ROW])
{
    system("cls");
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < ROW; j++)
        {
            if (map[i][j] == -1)
            {
                printf("#");
                // printf("%d",map[i][j]);
            }
            else if (map[i][j] == -2)
            {
                printf("F");
                // printf("%d",map[i][j]);
            }
            else
            {
                if (map[i][j])
                {
                    printf("X");
                    // printf("%d",map[i][j]);
                }
                else
                {
                    printf(" ");
                    // printf("%d",map[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

int start()
{
    int selection;
    printf("说明:w,a,s,d控制方向\n输入1开始,输入0结束\n");
    scanf("%d", &selection);
    switch (selection)
    {
    case 1:
        return 1;
        break;

    default:
        return 0;
        break;
    }
}

void move(int map[COL][ROW])
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

int forward(int map[COL][ROW], struct Point *head, enum Direction direction, int *length)
{
    switch (direction)
    {
    case down:
        if (map[head->y + 1][head->x] != 0)
        {
            if (map[head->y + 1][head->x] == -2)
            {
                *length = *length + 1;
                food(map);
            }
            else
            {
                printf("Game Over!,最大长度%d\n",*length);
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
                printf("Game Over!,最大长度%d\n",*length);
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
                printf("Game Over!,最大长度%d\n",*length);
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
                printf("Game Over!,最大长度%d\n",*length);
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
        break;
    }
    return 1;
}

void loop(int map[COL][ROW])
{
    struct Point head = {ROW / 2, COL / 2};
    int length = 3;
    enum Direction direction = right;
    food(map);
    printMap(map);
    for (;;)
    {
        DWORD start_time = GetTickCount();
        int timeout_flag = 0;

        while (!kbhit())
        {
            DWORD current_time = GetTickCount();

            if (current_time - start_time >= TIME)
            {
                timeout_flag = 1;
                break;
            }
        }

        while (!timeout_flag)
        {
            char ch = getch();
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

        if (!forward(map, &head, direction, &length))
        {
            break;
        }
        printMap(map);
    }
}
