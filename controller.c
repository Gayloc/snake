#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "controller.h"
#include "menu.h"

int get_food_axis(int max) //����ʳ������
{
    srand((unsigned int)time(NULL));

    int lower_bound = 1;
    int upper_bound = max;

    int range = upper_bound - lower_bound + 1;

    int random_number = rand() % range + lower_bound;

    return random_number;
}

void food(int map[COL][ROW]) //ʹ��ʳ����������ʳ��
{
    struct Point food_axis;

    do
    {
        food_axis.x = get_food_axis(COL - 1);
        food_axis.y = get_food_axis(ROW - 1);
    } while (map[food_axis.x][food_axis.y] != 0);

    map[food_axis.x][food_axis.y] = -2;
}

void init(int map[COL][ROW]) //��ͼ��ʼ��
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

void printMap(int map[COL][ROW]) //��ӡ��ͼ
{
    system("cls");
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; j < ROW; j++)
        {
            if (map[i][j] == -1)
            {
                printf("#"); //ǽ��
                // printf("%d",map[i][j]);
            }
            else if (map[i][j] == -2)
            {
                printf("F"); //ʳ��
                // printf("%d",map[i][j]);
            }
            else
            {
                if (map[i][j])
                {
                    printf("X"); //����
                    // printf("%d",map[i][j]);
                }
                else
                {
                    printf(" "); //�հ�
                    // printf("%d",map[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

int start() //���˵�������0ʱ�������
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

void move(int map[COL][ROW]) //�õ�ͼ���ߵ����岿�����ּ�һ��ʵ���ƶ�Ч��
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

int forward(int map[COL][ROW], struct Point *head, enum Direction direction, int *length) //�ƶ���ͷ
{
    switch (direction)
    {
    case down:
        if (map[head->y + 1][head->x] != 0)
        {
            if (map[head->y + 1][head->x] == -2)
            {
                *length = *length + 1; //��Ӧ����λ�ø�ֵ��ǰ����
                food(map); //����ʳ��
            }
            else
            {
                printf("Game Over!,����%d\n", *length);
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
                printf("Game Over!,����%d\n", *length);
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
                printf("Game Over!,����%d\n", *length);
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
                printf("Game Over!,����%d\n", *length);
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
        break; //����w,a,s,d���������
    }
    return 1; //û��ʧ�����������1
}

int loop(int map[COL][ROW]) //��Ϸѭ��
{
    struct Point head = {ROW / 2, COL / 2}; //Ĭ���ߵ�����λ�����м�
    int length = 3; //Ĭ�ϳ��ȣ���init�����еĳ�ʼ�����ƥ�䣩
    enum Direction direction = right; //Ĭ�Ϸ���
    food(map); //����ʳ��
    printMap(map);
    for (;;)
    {
        DWORD start_time = GetTickCount(); //����ϵͳ�ṩ��ǰʱ��
        int timeout_flag = 0; //��ʱ������־

        while (!kbhit()) //�������û�м�������
        {
            DWORD current_time = GetTickCount(); //��ȡ���ڵ�ʱ��

            if (current_time - start_time >= TIME) //�����ʱ
            {
                timeout_flag = 1;
                break;
            }
        }

        if (!timeout_flag) //���û�г�ʱ
        {
            char ch = getch(); //��ȡ�����ȴ���������
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

        if (!forward(map, &head, direction, &length)) //�����Ϸʧ��
        {
            break;
        }
        printMap(map);
    }
    return length; //���ر�����Ϸ����
}
