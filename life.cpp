#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include "life.h"

using namespace std;

Life::Life(int x_dim, int y_dim, int alive_proc) {
    this->x_dim = x_dim;
    this->y_dim = y_dim;

    if (alive_proc > 100 || 0 > alive_proc) {
        cout << "Alive % has to be in range of 0-100";
    }
    else {
        this->field = vector<vector<char>>(x_dim);

        for (int i=0; i < x_dim; i++) {
            this->field[i] = vector<char>(y_dim);
            for (int j=0; j < y_dim; j++) {
                if (rand() % 100 < alive_proc) {
                    this->field[i][j] = '@';
                }
                else {
                    this->field[i][j] = '.';
                }
            }
        }
    }
}

Life::Life() {
    this->x_dim = 90;
    this->y_dim = 160;
    this->field = vector<vector<char>>(this->x_dim);

        for (int i=0; i < this->x_dim; i++) {
            this->field[i] = vector<char>(this->y_dim);
            for (int j=0; j < this->y_dim; j++) {
                if (rand() % 100 < 10) {
                    this->field[i][j] = '@';
                }
                else {
                    this->field[i][j] = '.';
                }
            }
        }
}

void Life::printField() {
    for (int i=0; i < this->x_dim; i++) {
        for (int j=0; j < this->y_dim; j++) {
            cout << this->field[i][j] << " ";
        }
        cout << endl;
    }
}

int Life::aliveArround(int x_coord, int y_coord) {
    int counter = 0;

    for (int i = x_coord-1; i < x_coord+2; i++) {
        if (i < 0 || i >= this->x_dim) {
            continue;
        }
        else {
            for (int j = y_coord-1; j < y_coord+2; j++){
                if (j < 0 || this->y_dim < j) {
                    continue;
                }
                if (i == x_coord && j == y_coord) {
                    continue;
                }
                if (this->field[i][j] == '@') {
                    counter++;
                    //cout << "Found @ at " << i << j << endl;
                }
            }
        }
    }
    return counter;
}

void Life::updateField() {
    vector<vector<char>> next_field = this->field;
    int alive;

    for (int i=0; i < this->x_dim; i++) {
        for (int j=0; j < y_dim; j++) {
            alive = aliveArround(i, j);
            if (this->field[i][j] == '.' && alive == 3) { // rule 4
                next_field.at(i).at(j) = '@';
            }
            else {
                if (alive > 3 || alive < 2) { // rule 3 and 1
                    next_field.at(i).at(j) = '.';
                }
            }
        }
    }

    this->field = move(next_field);
}

void Life::startSimulation() {
    while (true) {
        system("clear");

        Life::printField();
        Life::updateField();

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {  

    srand(time(0));

    Life game = Life();

    //game.printField();

    game.startSimulation();

    return 0;
}