#include <queue>
#include <stdio.h>
#include "game.hpp"

extern int H, W;

void Prey(const char **world, int *action)
{
    int **dist_pred, **dist_far;
    struct Position pred, prey, far, pos, npos;
    int max_dist, min_dist;
    int i, j;

    dist_pred = new int *[H];
    dist_far = new int *[H];
    for (i = 0; i < H; i++)
    {
        dist_pred[i] = new int[W];
        dist_far[i] = new int[W];
    }

    pred = getPosition(world, PRED);
    prey = getPosition(world, PREY);
    calcDist(world, dist_pred, pred);
    max_dist = 0;
    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
        {
            if (max_dist <= dist_pred[i][j])
            {
                max_dist = dist_pred[i][j];
                far.y = i;
                far.x = j;
            }
        }
    }
    calcDist(world, dist_far, far);
    if (far.y == prey.y && far.x == prey.x)
    {
        *action = -1;
        return;
    }

    min_dist = H * W+1;
    max_dist = -1;
    for (i = 0; i < 4; i++)
    {
        pos.y = prey.y + dy[i];
        pos.x = prey.x + dx[i];

        if (isFree(world, pos) && (min_dist > dist_far[pos.y][pos.x]))
        {
            min_dist = dist_far[pos.y][pos.x];
        }
    }
    for (i = 0; i < 4; i++)
    {
        pos.y = prey.y + dy[i];
        pos.x = prey.x + dx[i];

        if (isFree(world, pos) && min_dist == dist_far[pos.y][pos.x] && max_dist <= dist_pred[pos.y][pos.x])
        {
            max_dist = dist_pred[pos.y][pos.x];
            npos = pos;
        }
    }

    switch ((npos.y - prey.y) * 10 + (npos.x - prey.x))
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