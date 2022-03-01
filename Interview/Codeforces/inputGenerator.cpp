#include <iostream>
using namespace std;

int random(int min, int max) //range : [min, max]
{
    static bool first = true;
    if (first) {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

int main() {
    freopen("../data/output_test.txt", "w", stdout);

    int testCase = 10;
    for (int i = 0; i < testCase; i++) {
        int len = random(1, 20);
        cout << len << endl;

        for (int j = 0; j < len; j++) {
            cout << j << " ";
        }
        cout << endl;
    }

    return 0;
}