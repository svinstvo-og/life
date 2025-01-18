#ifndef LIFE_H
#define LIFE_H

#include <vector>

class Life
{
    int x_dim;
    int y_dim;
    std::vector<std::vector<char>> field;
    std::vector<std::vector<char>> next_field;
public:
    Life();
    Life(int x_dim, int y_dim, int alive_proc);
    void printField();
    int aliveArround(int x_coord, int y_coord);
    void updateField();
    void startSimulation();
};

#endif