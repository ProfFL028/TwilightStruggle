#include <iostream>

using namespace std;

int random(int min, int max, int type = 0) //range : [min, max]
{
    static bool first = true;
    if (first) {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    if (type == 0) {
        return min + rand() % ((max + 1) - min);
    } else if (type == 1) { // odd
        int x = min + rand() % ((max + 1) - min);
        return x % 2 == 0 ? ((x + 1) > max ? (min % 2 == 1 ? min : (min + 1)) : x + 1) : x;
    } else { // even
        int x = min + rand() % ((max + 1) - min);
        return x % 2 == 0 ? x : ((x + 1) > max ? (min % 2 == 0 ? min : (min + 1)) : x + 1);
    }
}

int ArgPos(char *str, int argc, char **argv) {
    int a;
    for (a = 1; a < argc; a++)
        if (!strcmp(str, argv[a])) {// 查找对应的参数
            if (a == argc - 1) {
                printf("Argument missing for %s\n", str);
                exit(1);
            }
            return a;// 匹配成功，返回值所在的位置
        }
    return -1;
}

int main(int argc, char **argv) {
    char* fileName = new char[65535];
    fileName = "../data/input_test.txt";
    int i;
    if ((i = ArgPos((char *) "-filename", argc, argv)) > 0) strcpy(fileName, argv[i + 1]);

    int testCase = 100;
    if ((i = ArgPos((char *) "-test_case", argc, argv)) > 0) testCase = atoi(argv[i + 1]);

    int lenType = 0;
    if ((i = ArgPos((char *) "-len_type", argc, argv)) > 0) lenType = atoi(argv[i + 1]);
    int lenMin = 1;
    if ((i = ArgPos((char *) "-len_min", argc, argv)) > 0) lenMin = atoi(argv[i + 1]);
    int lenMax = 20;
    if ((i = ArgPos((char *) "-len_max", argc, argv)) > 0) lenMax = atoi(argv[i + 1]);

    int numType = 0;
    if ((i = ArgPos((char *) "-num_type", argc, argv)) > 0) numType = atoi(argv[i + 1]);
    int min = 1;
    if ((i = ArgPos((char *) "-min", argc, argv)) > 0) min = atoi(argv[i + 1]);
    int max = 10;
    if ((i = ArgPos((char *) "-max", argc, argv)) > 0) max = atoi(argv[i + 1]);

    freopen(fileName, "w", stdout);
    cout << testCase << endl;

    for (int i = 0; i < testCase; i++) {
        int len = random(lenMin, lenMax, lenType);
        cout << len << endl;

        for (int j = 0; j < len; j++) {
            cout << random(min, max, numType) << " ";
        }
        cout << endl;
    }

    return 0;
}
