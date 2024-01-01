#include "controller.h"
#include "stdio.h"

int getScore()
{
    FILE *f = fopen("score.txt", "r");
    int score = 0;
    fscanf(f,"%d", &score);
    
    return score;
    fclose(f);
}

int main()
{
    int map[COL][ROW];

    while (start())
    {
        init(map);
        int length = loop(map);
        
        if(getScore()<length)
        {
            FILE *file = fopen("score.txt", "w");
            fprintf(file, "%d", length);
            fclose(file);
        }
    }
    return 0;
}

