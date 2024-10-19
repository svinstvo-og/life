#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

int x_dim;
int y_dim;
int alive_proc;
vector<vector<char>> field;
vector<vector<char>> next_field;

int createField(int x_dim, int y_dim, int alive_proc) {
    if (alive_proc > 100 || 0 > alive_proc) {
        cout << "Alive % have to be in range of 0-100";
        return 1;
    }
    field = vector<vector<char>>(x_dim);

    for (int i=0; i < x_dim; i++) {
        field[i] = vector<char>(y_dim);
        for (int j=0; j < y_dim; j++) {
            if (rand() % 100 < alive_proc) {
                field[i][j] = '@';
            }
            else {
                field[i][j] = '.';
            }
        }
    }
    return 0;
}

int printField(vector<vector<char>> field, int x_dim, int y_dim) {
    for (int i=0; i < x_dim; i++) {
        for (int j=0; j < y_dim; j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

int aliveArround(vector<vector<char>> field, int x_dim, int y_dim, int x_coord, int y_coord) { //DIM = dimention size, COORD = coordinate
    int counter = 0;

    for (int i = x_coord-1; i < x_coord+2; i++) {
        if (i < 0 || i > x_dim) {
            continue;
        }
        else {
            for (int j = y_coord-1; j < y_coord+2; j++){
                if (j < 0 || y_dim < j) {
                    continue;
                }
                if (i == x_coord && j == y_coord) {
                    continue;
                }
                if (field[i][j] == '@') {
                    counter++;
                    //cout << "Found @ at " << i << j << endl;
                }
            }
        }
    }
    return counter;
}

int updateField(vector<vector<char>> field, int x_dim, int y_dim) {
    int alive;

    for (int i=0; i < x_dim; i++) {
        for (int j=0; j < y_dim; j++) {
            alive = aliveArround(field, x_dim, y_dim, i, j);
            if (field[i][j] == '.' && alive == 3) { // rule 4
                next_field[i][j] = '@';
            }
            else {
                if (alive > 3 || alive < 2) { // rule 3 and 1
                    field[i][j] = '.';
                }
            }
        }
    }

    field = next_field;
    return 0;
}

void startSimulation(vector<vector<char>> field, int x_dim, int y_dim) {
    for (int i=0; i < 10; i++) {
        printField(field, x_dim, y_dim);
        updateField(field, x_dim, y_dim);
    }
}

int main() {  
    srand(time(0));
    next_field = field;

    //cout << "Enter size of X dimention, size of Y and % of alive cells in field: " << endl;
    ///cin >> x_dim;
    ///cin >> y_dim;
    ///cin >> alive_proc;

    x_dim = 30;
    y_dim = 60;
    alive_proc = 10;

    createField(x_dim, y_dim, alive_proc);

    aliveArround(field, x_dim, y_dim, x_dim, y_dim);

    //startSimulation(field, x_dim, y_dim);

    //updateField(field, x_dim, y_dim);

    return 0;
}