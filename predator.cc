#include <queue>
#include "game.hpp"

extern int H, W;

void Predator(const char **world, int *action)
{
    int **dist_prey;
    struct Position pred, prey, pos, npos;
    int min_dist;
    int i;

    dist_prey = new int *[H];
    for (i = 0; i < H; i++)
    {
        dist_prey[i] = new int[W];
    }

    pred = getPosition(world, PRED);
    prey = getPosition(world, PREY);
    calcDist(world, dist_prey, prey);
    min_dist = H * W;
    for (i = 0; i < 4; i++)
    {
        pos.y = pred.y + dy[i];
        pos.x = pred.x + dx[i];

        if (isFree(world, pos) && (min_dist > dist_prey[pos.y][pos.x]))
        {
            min_dist = dist_prey[pos.y][pos.x];
            npos = pos;
        }
    }
    switch ((npos.y - pred.y) * 10 + (npos.x - pred.x))
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