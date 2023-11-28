#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char terrain[24][80];
int height = 21; 
int width = 80;

int isValid(int, int);

void printTerrain() {

    for(int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            printf("%c", terrain[i][j]);

        }
        printf("\n");
    }

}

void createEmptyMap() {

    for(int i = 0; i < height; i++) {

        for(int j = 0; j < width; j++) {

            terrain[i][j] = '.';

        }
        

    }

}

void createBoulder() {

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            if ((i == 0 || j == 0 || i == height-1 || j == width-1) && (terrain[i][j] != '#')) {

                terrain[i][j] = '%';

            }

        }

    }

}

void createCarrot() {

    int numCarrot = rand() % 3 + 8;
    srand(time(NULL));
    int xCoor = rand() % 10 + 5; // height coordinate
    srand(time(NULL));
    int yCoor = rand() % 40 + 20; // width coordinate
    srand(time(NULL));
    
   

    for (int i = xCoor - (numCarrot - 1); i < (xCoor - (numCarrot - 1)) + (numCarrot + (numCarrot - 1)); i++) {

        for (int j = yCoor - (numCarrot - 1); j < (yCoor - (numCarrot - 1)) + (numCarrot + (numCarrot - 1)); j++) {

           
            int true = isValid(i,j);

            if (true == 1) {

                terrain[i][j] = '^';

            }

            

        }

    }

}

void createWater() {

    int numWater = rand() % 3 + 8;
    srand(time(NULL));
    int xCoor = rand() % 10 + 5; // height coordinate
    srand(time(NULL));
    int yCoor = rand() % 40 + 20; // width coordinate
    srand(time(NULL));
    
    
    for (int i = xCoor - (numWater - 1); i < (xCoor - (numWater - 1)) + (numWater+ (numWater - 1)); i++) {

        for (int j = yCoor - (numWater - 1); j < (yCoor - (numWater - 1)) + (numWater + (numWater - 1)); j++) {

           
            int true = isValid(i,j);

            if (true == 1) {

                terrain[i][j] = '~';

            }

            

        }

    }

}

void createLongGrass() {

    int numLGrass = rand() % 3 + 8;
    srand(time(NULL));
    int xCoor = rand() % 10 + 5; // height coordinate
    int yCoor = rand() % 40 + 20; // width coordinate
    
    

    for (int i = xCoor - (numLGrass - 1); i < (xCoor - (numLGrass - 1)) + (numLGrass + (numLGrass - 1)); i++) {

        for (int j = yCoor - (numLGrass - 1); j < (yCoor - (numLGrass - 1)) + (numLGrass + (numLGrass - 1)); j++) {

           
            int true = isValid(i,j);

            if (true == 1) {

                terrain[i][j] = ':';

            }

            

        }

    }

}

void createRock() {

    int numRock = rand() % 3 + 8;
    srand(time(NULL));
    int xCoor = rand() % 10 + 5; // height coordinate
    srand(time(NULL));
    int yCoor = rand() % 40 + 20; // width coordinate
    srand(time(NULL));
    
    
    for (int i = xCoor - (numRock - 1); i < (xCoor - (numRock - 1)) + (numRock+ (numRock- 1)); i++) {

        for (int j = yCoor - (numRock - 1); j < (yCoor - (numRock - 1)) + (numRock + (numRock - 1)); j++) {

           
            int true = isValid(i,j);

            if (true == 1) {

                terrain[i][j] = '%';

            }

            

        }

    }

}

void fillEmpty() {

       srand(time(NULL));
    int fillNumber = rand()%20 + 200;
 
    int xCoor = 0;
    int yCoor = 0;
    int type = 0;

   

    for (int i = 0; i < fillNumber; i++) {

       
        xCoor = rand()%18+1;
        yCoor = rand()%77 + 1;
        type = rand()%4;

        if (terrain[xCoor][yCoor] == '.') {

            if (type == 0) {

                terrain[xCoor][yCoor] = '%';

            } else if (type == 1) {

                terrain[xCoor][yCoor] = ':';

            } else if (type == 2) {

                terrain[xCoor][yCoor] = '^';

            } else if (type == 3) {

                terrain[xCoor][yCoor] = '~';

            } 

        } 

    }

}

int isValid(int x, int y) {

    if (x >= 0 && y >= 0 && terrain[x][y] == '.') {

        return 1;

    } else {

        return 0;

    }

}

void createPath() {

    int north = rand()%40 + 20;
    srand(time(NULL));
    int south = rand()%40+ 40;
    srand(time(NULL));
    int west = rand()%10 + 5;
    srand(time(NULL));
    int east = rand()%10 + 5;
    srand(time(NULL));

    terrain[0][north] = '#';
    terrain[height-1][south] = '#';
    terrain[west][0] = '#';
    terrain[east][width-1] = '#';

    int bigger = 0;

    if (east > west) {

        bigger = east;

    } else {

        bigger = west;

    }

    for (int i = 0; i <= bigger; i++) {

        terrain[i][north] = '#';

       if (i == east) {

        for (int j = north; j < 80; j++) {

            terrain[east][j] = '#'; 

        }

       }

       if (i == west) {

        for( int j = north; j > 0; j--) {

            terrain[west][j] = '#';

        }

       }

    }

    if (west > east) {

        for (int i = west; i <= south; i++) {

            terrain[i][south] = '#';

        }

    } else {

        for (int i = east; i <= south; i++) {

            terrain[i][south] = '#';

        }

    }

   
   

    int pokeBuildingX = north - (rand() % 10 + 5);
    srand(time(NULL));  

    terrain[west-1][pokeBuildingX] = 'C';
    terrain[west-2][pokeBuildingX] = 'C';
    terrain[west-1][pokeBuildingX+1] = 'C';
    terrain[west-2][pokeBuildingX+1] = 'C';

    int pokeMartX = north + (rand() % 10 + 3);
    srand(time(NULL));
    terrain[east-1][pokeMartX] = 'M';
    terrain[east-2][pokeMartX] = 'M';
    terrain[east-1][pokeMartX+1] = 'M';
    terrain[east-2][pokeMartX+1] = 'M';

}



int main() {

    createEmptyMap();
    createBoulder();
    createWater();
    createLongGrass();
    createCarrot();
    createRock();
    createWater();
    createLongGrass();
    createCarrot();
    createRock();
    createPath();
    fillEmpty();
    printTerrain();

}