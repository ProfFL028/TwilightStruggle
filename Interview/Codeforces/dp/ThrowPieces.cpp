/**
* There are N levels in a building, and you have K pieces. You can drop a piece down in ith floor, it may break down or it wouldn't.
 * Your job is to find the max level where the piece would not be break down. Tell us the minimal time you can.
*/

#include <iostream>

using namespace std;

/**
 * Simple dp solution.
 * @param nFloors
 * @param nPieces
 */
void solve1(int nFloors, int nPieces) {
    if (nFloors < 1 || nPieces < 1) {
        cout << 0 << endl;
    }
    if (nPieces == 1) {
        cout << nFloors << endl;
    }

    int dp[nFloors + 1][nPieces + 1];
    for (int i = 0; i <= nFloors; i++) {
        for (int j = 0; j <= nPieces; j++) {
            dp[i][j] = 0;
        }
    }
    for (int i = 1; i <= nFloors; i++) {
        dp[i][1] = i;
    }

    for (int i = 1; i <= nFloors; i++) {
        for (int j = 2; j <= nPieces; j++) {
            int minStep = INT_MAX;
            for (int k = 1; k <= i; k++) {
                minStep = min(minStep, max(dp[k - 1][j - 1], dp[i - k][j]));
            }
            dp[i][j] = minStep + 1;
        }
    }

    cout << dp[nFloors][nPieces] << endl;
}

/**
 * space saving solution for it.
 * @param nFloors
 * @param nPieces
 */
void solve2(int nFloors, int nPieces) {
    if (nFloors < 1 || nPieces < 1) {
        cout << 0 << endl;
        return ;
    }
    if (nPieces == 1) {
        cout << 1 << endl;
        return ;
    }

    int* curDp = new int[nFloors + 1];
    int* preDp = new int[nFloors + 1];
    for (int i = 0; i <= nFloors; i++) {
        curDp[i] = i;
        preDp[i] = i;
    }

    for (int i = 1; i <= nFloors; i++) {
        for (int j = 2; j <= nPieces; j++) {
            int minStep = INT_MAX;
            for (int k = 1; k <= i; k++) {
                minStep = min(minStep, max(preDp[k - 1], curDp[i - k]));
            }
            preDp[i] = curDp[i];
            curDp[i] = minStep + 1;
        }
    }

    cout << curDp[nFloors] << endl;
}

/**
 * speed up with Quadrilateral inequality
 * @param nFloors
 * @param nPieces
 */
void solve3(int nFloors, int nPieces) {
    if (nFloors < 1 || nPieces < 1) {
        cout << 0 << endl;
        return ;
    }
    if (nPieces == 1) {
        cout << 1 << endl;
        return ;
    }
    int* curDp = new int[nFloors + 1];
    int* preDp = new int[nFloors + 1];
    int* cands = new int[nFloors + 1];
    for (int i = 0; i <= nFloors; i++) {
        curDp[i] = i;
        preDp[i] = i;
        cands[i] = 1;
    }

    for (int i = 1; i <= nFloors; i++) {
        for (int j = nPieces; j >= 2; j--) {
            int minStep = INT_MAX;
            int minEnum = cands[j];
            int maxEnum = j == nPieces ? i / 2 + 1 : cands[j+1];
            for (int k = minEnum; k <= maxEnum; k++) {
                int cur = max(preDp[k - 1], curDp[i - k]);
                if (cur <= minStep) {
                    minStep = cur;
                    cands[j] = k;
                }
            }
            preDp[i] = curDp[i];
            curDp[i] = minStep + 1;
        }
    }

    cout << curDp[nFloors] << endl;
}

int log2N(int n) {
    int ans = -1;
    while (n != 0) {
        ans++;
        n >>= 1;
    }
    return ans;
}

void solve4(int nFloors, int nPieces) {
    if (nFloors < 1 || nPieces < 1) {
        cout << 0 << endl;
        return ;
    }
    if (nPieces == 1) {
        cout << nFloors << endl;
        return ;
    }

    int bsTime = log2N(nFloors) + 1;
    if(nPieces >= bsTime) {
        cout << bsTime << endl;
        return ;
    }

    int dp[nPieces];
    int ans = 0;
    while (true) {
        ans++;
        int previous = 0;
        for (int i = 0; i < nPieces; i++) {
            int tmp = dp[i];
            dp[i] = dp[i] + previous + 1;
            previous = tmp;
            if (dp[i] >= nFloors) {
                cout << ans << endl;
                return ;
            }
        }
    }
}

int main() {
    int nFloors = 105;
    int nPieces = 2;
    solve4(nFloors, nPieces);
}