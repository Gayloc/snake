#include "controller.h"

int main()
{
    int map[COL][ROW];

    while (start())
    {
        init(map);
        loop(map);
    }
    return 0;
}