#include <queue>
#include "game.hpp"

extern int H, W;

void copyWorld(const char **src, char **dest)
{
    int i, j;
    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}
void transDistMap(const char **src, int **dest)
{
    int i, j;
    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
        {
            switch (src[i][j])
            {
            case CHASER:
            case FUGITIVE:
            case FREE:
                dest[i][j] = 0;
            default:
                dest[i][j] = -1;
            }
        }
    }
}
struct Position getPosition(const char **world, char kind)
{
    struct Position pos;
    int i, j;

    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
        {
            if (world[i][j] == kind)
            {
                pos.y = i;
                pos.x = j;
                return pos;
            }
        }
    }

    pos.y = -1;
    pos.x = -1;
    return pos;
}
void calcDist(const char **world, int **dist, struct Position start)
{
    std::queue<struct Position> que;
    struct Position pos, npos;
    char **flag;
    int i;

    flag = new char *[H];
    for (i = 0; i < H; i++)
    {
        flag[i] = new char[W];
    }

    transDistMap(world, dist);
    copyWorld(world, flag);
    flag[start.y][start.x] = WALL;
    que.push(start);

    while (!que.empty())
    {
        pos = que.front();
        que.pop();

        for (i = 0; i < 4; i++)
        {
            npos.y = pos.y + dy[i];
            npos.x = pos.x + dx[i];
            if (isFree((const char **)flag, npos))
            {
                que.push(npos);
                flag[npos.y][npos.x] = WALL;
                dist[npos.y][npos.x] = dist[pos.y][pos.x] + 1;
            }
        }
    }
}
bool isFree(const char **world, struct Position pos)
{
    if (0 <= pos.y && pos.y < H && 0 <= pos.x && pos.x < W)
    {
        return (world[pos.y][pos.x] != WALL) ? true : false;
    }
    return false;
}