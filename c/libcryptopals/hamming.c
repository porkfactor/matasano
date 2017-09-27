#include <pm/hamming.h>

uint64_t hamming_distance(char const *l, char const *r)
{
    uint64_t distance = 0UL;
    char const *p1;
    char const *p2;

    for(p1 = l, p2 = r; (*p1) && (*p1); p1++, p2++)
    {
        distance += __builtin_popcount((*p1) ^ (*p2));
    }

    return distance;
}


