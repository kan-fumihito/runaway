#include <fstream>
#include <iostream>
#include "game.hpp"

using namespace std;

int H, W;

int main(void)
{
    char **world;
    int i, j, action;
    ifstream ifs("world.dat");

    ifs >> H >> W;

    world = new char *[H];
    for (i = 0; i < H; i++)
    {
        world[i] = new char[W];
        ifs >> world[i];
    }

    //Chaser((const char **)world, &action);
    //Fugitive((const char **)world, &action);

    cout << action << endl;

    return 0;
}