#include <stdio.h>
#include <stdlib.h>

void bounceLogic(int *pos, int *v) {
    // moved is the position after velocity
    int moved = *pos + *v;

    while (moved < 0 || moved > 19) {
        if (moved < 0) {
            // left wall bounce
            moved = -moved;
            *v = -*v;
        } else if (moved > 19) {
            // right wall bounce
            moved = 19 - (moved - 19);
            *v = -*v;
        }
    }
    // Update position
    *pos = moved;
}

void particleMovement(int *x, int *y, int *vx, int *vy) {
    bounceLogic(x, vx);
    bounceLogic(y, vy);
}

void updateParticles(int x[], int y[], int vx[], int vy[], int *numParticles, int numSeconds) {
    for (int t = 0; t < numSeconds; t++) {
        // Update the position of each particle
        for (int i = 0; i < *numParticles; i++) {
            particleMovement(&x[i], &y[i], &vx[i], &vy[i]);
        }

        // Check for collision
        int collision[400] = {0};

        // Check for collision
        for (int i = 0; i < *numParticles; i++) {
            for (int j = i + 1; j < *numParticles; j++) {
                // If the position of particles
                if (x[i] == x[j] && y[i] == y[j]) {
                    collision[i] = 1;
                    collision[j] = 1;
                }
            }
        }

        // Rearrange the particles array to remove the collided particles
        int newPos = 0;
        for (int i = 0; i < *numParticles; i++) {
            if (!collision[i]) {
                // Copy the particle to the new position
                x[newPos] = x[i];
                y[newPos] = y[i];
                vx[newPos] = vx[i];
                vy[newPos] = vy[i];
                newPos++;
            }
        }
        // Update the number of particles
        *numParticles = newPos;
    }
}

void updateGrid(char **grid, int x[], int y[], int numParticles) {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 22; j++) {
            // Empty spaces
            grid[i][j] = ' ';
        }
    }

    for (int i = 0; i < numParticles; i++) {
        if (x[i] >= 0 && x[i] <= 19 && y[i] >= 0 && y[i] <= 19) {
            // Particles
            grid[20-y[i]][x[i] + 1] = '+';
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input file> <output file> <num sec>\n", argv[0]);
        return 1;
    }

    int numSeconds = atoi(argv[3]);
    FILE *inFile = fopen(argv[1], "r");
    if (!inFile) {
        perror("Failed to open input file");
        return 1;
    }

    // Assume max 400 particles
    int x[400], y[400], vx[400], vy[400];

    // Pointer to the number of particles
    int numParticles = 0;
    int *ptr_numParticles = &numParticles;

    while (fscanf(inFile, "%d,%d,%d,%d", &x[numParticles], &y[numParticles], &vx[numParticles], &vy[numParticles]) != EOF) {
        numParticles++;
    }
    fclose(inFile);

    updateParticles(x, y, vx, vy, ptr_numParticles, numSeconds);

    // Initialize the grid
    char **grid = (char **)malloc(22 * sizeof(char *));
    for (int i = 0; i < 22; i++) {
        grid[i] = (char *)malloc(22 * sizeof(char));
    }

    updateGrid(grid, x, y, numParticles);

    FILE *outFile = fopen(argv[2], "w");
    if (!outFile) {
        perror("Failed to open output file");
        return 1;
    }

    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 22; j++) {
            if (i == 0 || i == 21 || j == 0 || j == 21) {
                fprintf(outFile, "%c", '*');
            } else {
                fprintf(outFile, "%c", grid[i][j]);
            }
        }
        fprintf(outFile, "\n");
    }
    fclose(outFile);

    // Allocated memory
    for (int i = 0; i < 22; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
