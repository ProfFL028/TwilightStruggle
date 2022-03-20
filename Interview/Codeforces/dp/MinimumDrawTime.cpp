/**
* Given a array represent how much time a single drawer draw the image and a number represent how many drawers, your job is to arrange
 * the job so that the total num is minimum. you must arrange jobs one by one.
 * 1 1 1 4 3, num=3 -> 3,4,3=>4
*/

#include <iostream>

using namespace std;

int getNeedNum(int *arr, int arrSize, int lim) {
    int ans = 1;
    int sum = 0;
    for (int i = 0; i < arrSize; ++i) {
        if (arr[i] > lim) {
            return INT_MAX;
        } else {
            sum += arr[i];
            if (sum > lim) {
                ans++;
                sum = arr[i];
            }
        }
    }

    return ans;
}

int main() {
    int* arr = new int[5]{1, 1, 1, 4, 3};
    int arrSize = 5;
    int drawCount = 3;
    if (drawCount >=arrSize) {
        int ans = INT_MAX;
        for (int i =0; i < arrSize;i++) {
            ans = max(arr[i], ans);
        }
        cout << ans << endl;
    } else {
        int minSum = 0;
        int maxSum = 0;
        for (int i = 0; i < arrSize; i++) {
            maxSum += arr[i];
        }
        while (minSum != maxSum - 1) {
            int mid = (minSum + maxSum) / 2;
            if (getNeedNum(arr, arrSize, mid) > drawCount) {
                minSum = mid;
            } else {
                maxSum = mid;
            }
        }
        cout << maxSum << endl;
    }

    return 0;
}