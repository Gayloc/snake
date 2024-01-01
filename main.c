#include "controller.h"
#include "stdio.h"

int main()
{
    int map[COL][ROW];

    while (start())
    {
        init(map);
        int length = loop(map);
        
        FILE *file = fopen("score.txt", "w");
        fprintf(file, "%d", length);
        fclose(file);
    }
    return 0;
}