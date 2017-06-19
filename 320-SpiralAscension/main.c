/* 
 * Link: https://www.reddit.com/r/dailyprogrammer/comments/6i60lr/20170619_challenge_320_easy_spiral_ascension/
 *
 * We save the spiral in an n x n Matrix using a 2D array
 * The number at coordinates (x, y) is in the x-th row and the y-th column
 *
 * /  -  -  -  y
 * |  1  2  3  4
 * | 12 13 14  5
 * | 11 16 15  6
 * x 10  9  8  7
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void print(int n, int spiral[n][n]) {
    int square = n * n;

    int numDigits = floor(log10(square)) + 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%*d ", numDigits, spiral[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    bool reverse = argc > 1;

    while(1) {
        int num = 0;
        scanf("%d", &num);

        if(num <= 0) {
            // Abort on non positive numbers
            break;
        }

        int spiral[num][num];

        /*
         * The coordinates in the spiral we are currently at
         */
        int x = 0, y = 0;

        /*
         * For each number we travel on in the direction given by these two variables
         * With these initial values we travel from the top left to the right
         */
        int xDiff = 0;
        int yDiff = 1;

        /*
         * When walking the spiral this counts how many turns are left until we completed one layer of the spiral
         * In the beginning there are three turns after that there are always two turns
         */
        int turns = 3;

        /*
         * Length of edges in the current layer
         * The number of steps we can take on an edge before we need to turn depends on what layer we are currently in
         * in the beginning it is one less than the side length of the spiral and decreases by one for each layer
         */
        int len = num - 1;

        /*
         * Counts how many steps we have remaining before we need to turn
         */
        int lenRemaining = len;

        for (int i = 1; i <= num * num; ++i) {
            /*
             * Just in case
             */
            if(x >= num || y >= num || x < 0 || y < 0) {
                fprintf(stderr, "An error occured while walking the spiral\n");
                continue;
            }

            spiral[x][y] = i;

            if(lenRemaining == 0) {
                /*
                 * We need to turn
                 */

                turns--;

                /*
                 * Set the new movement vectors
                 */
                int xDiffOld = xDiff;
                xDiff = yDiff;
                yDiff = -xDiffOld;

                /*
                 * If we have no turns left, we have reached a new layer
                 */
                if(turns == 0) {
                    len--;
                    turns = 2;
                }

                /*
                 * Reset lenRemaining
                 */
                lenRemaining = len;
            }

            /*
             * Apply movement vector and decrease remaining steps
             */
            x += reverse? yDiff : xDiff;
            y += reverse? xDiff : yDiff;
            lenRemaining--;
        }

        print(num, spiral);
    }
    return 0;
}
