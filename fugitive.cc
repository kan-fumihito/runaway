#include <queue>
#include "game.hpp"

extern int H, W;

void Fugitive(const char **world, int *action)
{
    int **dist_chas, **dist_far;
    struct Position chas, fugi, far, pos, npos;
    int max_dist, min_dist;
    int i, j;

    dist_chas = new int *[H];
    dist_far = new int *[H];
    for (i = 0; i < H; i++)
    {
        dist_chas[i] = new int[W];
        dist_far[i] = new int[W];
    }

    chas = getPosition(world, CHASER);
    fugi = getPosition(world, FUGITIVE);
    calcDist(world, dist_chas, chas);
    max_dist = 0;
    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
        {
            if (max_dist <= dist_chas[i][j])
            {
                max_dist = dist_chas[i][j];
                far.y = i;
                far.x = j;
            }
        }
    }
    calcDist(world, dist_far, far);
    if (far.y == fugi.y && far.x == fugi.x)
    {
        *action = -1;
        return;
    }

    min_dist = H * W + 1;
    max_dist = -1;
    for (i = 0; i < 4; i++)
    {
        pos.y = fugi.y + dy[i];
        pos.x = fugi.x + dx[i];

        if (isFree(world, pos) && (min_dist > dist_far[pos.y][pos.x]))
        {
            min_dist = dist_far[pos.y][pos.x];
        }
    }
    for (i = 0; i < 4; i++)
    {
        pos.y = fugi.y + dy[i];
        pos.x = fugi.x + dx[i];

        if (isFree(world, pos) && min_dist == dist_far[pos.y][pos.x] && max_dist <= dist_chas[pos.y][pos.x])
        {
            max_dist = dist_chas[pos.y][pos.x];
            npos = pos;
        }
    }

    switch ((npos.y - fugi.y) * 10 + (npos.x - fugi.x))
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