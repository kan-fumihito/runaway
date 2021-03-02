#include <queue>
#include "game.hpp"

extern int H, W;

void Chaser(const char **world, int *action)
{
    int **dist_fugi;
    struct Position chas, fugi, pos, npos;
    int min_dist;
    int i;

    dist_fugi = new int *[H];
    for (i = 0; i < H; i++)
    {
        dist_fugi[i] = new int[W];
    }

    chas = getPosition(world, CHASER);
    fugi = getPosition(world, FUGITIVE);
    calcDist(world, dist_fugi, fugi);
    min_dist = H * W;
    for (i = 0; i < 4; i++)
    {
        pos.y = chas.y + dy[i];
        pos.x = chas.x + dx[i];

        if (isFree(world, pos) && (min_dist > dist_fugi[pos.y][pos.x]))
        {
            min_dist = dist_fugi[pos.y][pos.x];
            npos = pos;
        }
    }
    switch ((npos.y - chas.y) * 10 + (npos.x - chas.x))
    {
    case 0 * 10 + 1:
        *action = 0;
        break;
    case 1 * 10 + 0:
        *action = 1;
        break;
    case 0 * 10 + -1:
        *action = 2;
        break;
    case -1 * 10 + 0:
        *action = 3;
        break;
    default:
        *action = -1;
    }
}