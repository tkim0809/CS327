#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//int count = 0;

bool validMove(int x, int y) {

    if (x < 0 || y < 0 || x >= 5 || y >= 5) {

        return false;

    }

    return true;

}

void knightTour(int afterMove[5][5], int x, int y, int num) {

    afterMove[x][y] = num;
    int row[] = {2,1,-1,-2,-2,-1,1,2,2};
    int col[] = {1,2,2,1,-1,-2,-2,-1,1};

    if (num >= 25) {
        //count++;
        for (int i = 0; i < 5; i++) {

            for (int j = 0; j < 5; j++) {

                if (i == 4 && j == 4) {

                    printf("%d", afterMove[i][j]);

                } else {

                printf("%d,", afterMove[i][j]);


                }
            }


        }

        printf("\n");


    afterMove[x][y] = 0;
    return;

    }

   for (int k = 0; k < 8; k++) {

    int newX = x + row[k];
    int newY = y + col[k];

    if (validMove(newX, newY) && !afterMove[newX][newY]) {

        knightTour(afterMove, newX, newY, num + 1);

    }

   }

    afterMove[x][y] = 0;

}

int main() {

    int afterMove[5][5] = {0};

    int num = 1;

    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 5; j++) {

            knightTour(afterMove, i, j, num);

        }

    }

    //printf("%d", count);

    return 0;

}