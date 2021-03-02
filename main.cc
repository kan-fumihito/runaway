#include <thread>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include "game.hpp"

#define WAITTIME 1000000

int H, W;

void printWorld(char **world);
void threadPredator(char **world, struct Position pred, int *action);
void threadPrey(char **world, struct Position prey, int *action);

int main(int argc, char *argv[])
{
    char **world;
    std::string filename = "world.dat";
    struct Position prey, pred;
    int i, turn = 30;
    int prey_action, pred_action;

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

    pred = getPosition((const char **)world, PRED);
    prey = getPosition((const char **)world, PREY);
    for (i = 0; i < turn; i++)
    {
        system("clear");
        std::cout << "turn" << ':' << i + 1 << std::endl;
        printWorld(world);

        std::thread th_prey(threadPrey, world, prey, &prey_action);
        std::thread th_predator(threadPredator, world, pred, &pred_action);

        usleep(WAITTIME);

        th_predator.join();
        th_prey.join();

        world[pred.y][pred.x] = FREE;
        world[prey.y][prey.x] = FREE;
        if (pred_action != -1)
        {
            pred.y += dy[pred_action];
            pred.x += dx[pred_action];
        }
        if (prey_action != -1)
        {

            prey.y += dy[prey_action];
            prey.x += dx[prey_action];
        }
        world[prey.y][prey.x] = PREY;
        world[pred.y][pred.x] = PRED;
        if (prey.y == pred.y && prey.x == pred.x)
        {
            system("clear");
            std::cout << "turn" << i + 1 << std::endl;
            printWorld(world);
            std::cout << "Predator Win" << std::endl;
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
    std::cout << "Prey Win" << std::endl;

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

void threadPredator(char **world, struct Position pred, int *action)
{
    struct Position pos;

    *action = -1;
    Predator((const char **)world, action);

    if (0 <= *action && *action <= 3)
    {
        pos.y = pred.y + dy[*action];
        pos.x = pred.x + dx[*action];
        if (isFree((const char **)world, pos))
        {
            return;
        }
    }
    *action = -1;
}
void threadPrey(char **world, struct Position prey, int *action)
{
    struct Position pos;

    *action = -1;
    Prey((const char **)world, action);

    if (0 <= *action && *action <= 3)
    {
        pos.y = prey.y + dy[*action];
        pos.x = prey.x + dx[*action];
        if (isFree((const char **)world, pos))
        {
            return;
        }
    }
    *action = -1;
}
