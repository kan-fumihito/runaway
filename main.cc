#include <thread>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <random>
#include "game.hpp"

#define WAITTIME 1000000

int H, W;
int prob=20;

void printWorld(char **world);
void threadChaser(char **world, struct Position chas, int *action);
void threadFugitive(char **world, struct Position fugi, int *action);

int main(int argc, char *argv[])
{
    char **world;
    std::string filename = "world.dat";
    struct Position fugi, chas;
    int i, turn = 30;
    int fugi_action, chas_action;

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
        {
            if (argc >= i + 1)
            {
                filename = argv[i + 1];
                i++;
            }
            else
            {
                std::cout << "argument error" << std::endl;
            }
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            if (argc >= i + 1)
            {
                turn = std::atoi(argv[i + 1]);
                i++;
            }
            else
            {
                std::cout << "argument error" << std::endl;
            }
        }else if (strcmp(argv[i], "-p") == 0)
        {
            if (argc >= i + 1)
            {
                prob = std::atoi(argv[i + 1]);
                i++;
            }
            else
            {
                std::cout << "argument error" << std::endl;
            }
        }
    }

    std::ifstream ifs(filename);
    ifs >> H >> W;
    world = new char *[H];
    for (i = 0; i < H; i++)
    {
        world[i] = new char[W];
        ifs >> world[i];
    }

    chas = getPosition((const char **)world, CHASER);
    fugi = getPosition((const char **)world, FUGITIVE);
    for (i = 0; i < turn; i++)
    {
        system("clear");
        std::cout << "turn" << ':' << i << std::endl;
        printWorld(world);

        std::thread th_fugi(threadFugitive, world, fugi, &fugi_action);
        std::thread th_chasator(threadChaser, world, chas, &chas_action);

        usleep(WAITTIME);

        th_chasator.join();
        th_fugi.join();

        world[chas.y][chas.x] = FREE;
        world[fugi.y][fugi.x] = FREE;
        if (chas_action != -1)
        {
            chas.y += dy[chas_action];
            chas.x += dx[chas_action];
        }
        if (fugi_action != -1)
        {

            fugi.y += dy[fugi_action];
            fugi.x += dx[fugi_action];
        }
        world[fugi.y][fugi.x] = FUGITIVE;
        world[chas.y][chas.x] = CHASER;
        if (fugi.y == chas.y && fugi.x == chas.x)
        {
            system("clear");
            std::cout << "turn" << i + 1 << std::endl;
            printWorld(world);
            std::cout << "Chaser Win" << std::endl;
            for (i = 0; i < H; i++)
            {
                delete world[i];
            }
            delete world;

            return 0;
        }
    }
    system("clear");
    std::cout << "turn" << i << std::endl;
    printWorld(world);
    std::cout << "Fugitive Win" << std::endl;

    for (i = 0; i < H; i++)
    {
        delete world[i];
    }
    delete world;

    return 0;
}

void printWorld(char **world)
{
    int i, j;
    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
        {
            std::cout << world[i][j];
        }
        std::cout << std::endl;
    }
}

void threadChaser(char **world, struct Position chas, int *action)
{
    struct Position pos;

    *action = -1;
    Chaser((const char **)world, action);

    if (0 <= *action && *action <= 3)
    {
        pos.y = chas.y + dy[*action];
        pos.x = chas.x + dx[*action];
        if (isFree((const char **)world, pos))
        {
            return;
        }
    }
    *action = -1;
}
void threadFugitive(char **world, struct Position fugi, int *action)
{
    struct Position pos;

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(1, 100);
    int n = distr(eng);

    *action = -1;
    if (n > prob)
    {
        Fugitive((const char **)world, action);

        if (0 <= *action && *action <= 3)
        {
            pos.y = fugi.y + dy[*action];
            pos.x = fugi.x + dx[*action];
            if (isFree((const char **)world, pos))
            {
                return;
            }
        }
        *action = -1;
    }
}
