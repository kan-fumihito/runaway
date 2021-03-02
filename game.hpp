
#define WALL '#'
#define FREE '.'
#define PRED '@'
#define PREY '+'

const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

struct Position
{
    int x, y;
};

void transDistMap(const int **src, int **dest);
struct Position getPosition(const char **world, char kind);
void calcDist(const char **world, int **dist, struct Position start);
bool isFree(const char **world, struct Position pos);

void Predator(const char **world, int *action);
void Prey(const char **world, int *action);