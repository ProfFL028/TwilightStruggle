/**
 * given an array of increase different points, and num posts, find the min distance.
 * [1, 2, 3, 4, 5, 10000], Num:2
 * choose 3 and 10000-> min: 6
 */

#include <iostream>

using namespace std;

int main() {
    int numPoints = 6;
    int *points = new int[numPoints]{1, 2, 3, 4, 5, 10000};
    int numPost = 2;

    int oneDp[numPoints][numPoints];
    for (int i = 0; i < numPoints; ++i) {
        oneDp[i][i] = 0;
    }
    for (int i = 0; i < numPoints; ++i) {
        for (int j = i + 1; j < numPoints; ++j) {
            oneDp[i][j] = oneDp[i][j - 1] + points[j] - points[(i + j) / 2];
        }
    }

    int disDp[numPost][numPoints];
    int s[numPost][numPoints];

    for (int j = 0; j != numPoints; j++) {
        disDp[0][j] = oneDp[0][j];
        s[0][j] = 0;
    }

    int minK = 0;
    int maxK = 0;
    int cur = 0;
    for (int i = 0; i < numPost; ++i) {
        for (int j = numPoints - 1; j > i; --j) {
            minK = s[i - 1][j];
            maxK = j == numPoints - 1 ? numPoints - 1 : s[i][j + 1];
            disDp[i][j] = INT_MAX;
            for (int k = minK; k <= maxK; k++) {
                cur = disDp[i - 1][k] + oneDp[k + 1][j];
                if (cur <= disDp[i][j]) {
                    disDp[i][j] = cur;
                    s[i][j] = k;
                }
            }
        }
    }
    cout << disDp[numPost - 1][numPoints - 1] << endl;
    return 0;
}
