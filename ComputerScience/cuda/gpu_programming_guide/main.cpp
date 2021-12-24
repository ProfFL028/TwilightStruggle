#include <iostream>
#include "BMPFileReader.h"
#include <sys/time.h>
#include <pthread.h>

using namespace std;
using namespace img;

unsigned char *imgData;
int numThreads = 4;
int imgHeight;
int imgWidth;
int rowBytes;

void *(*MTFlipFunc)(void *arg);

void *MTFlipH(void *tid) {
    long threadStart = *((int *) tid);
    long interval = (imgHeight - 1) / numThreads + 1;
    threadStart *= interval;
    long threadEnd = threadStart + interval;

    int centerV = imgWidth / 2;
    for (int j = threadStart; j < threadEnd && j < imgHeight; j++) {
        int posH = j * rowBytes;
        for (int i = 0; i < centerV; i++) {
            int posOriginal = posH + i;
            int posDest = posH + imgWidth - 1 - i;
            unsigned char tmp = imgData[posOriginal];
            imgData[posOriginal] = imgData[posDest];
            imgData[posDest] = tmp;
        }
    }

    pthread_exit(0);
}


int main() {
    BMPFileReader reader;
    BMPFile *file = reader.read("tree.bmp");

    cout << *file << endl;

    cout << file->getColorAt(63, 50) << endl;

    struct timeval t;
    double startTime, endTime;
    double timeElapsed;

    const int REPEATS = 129;

    gettimeofday(&t, NULL);
    startTime = (double) t.tv_sec * 1000000.0 + ((double) t.tv_usec);

    for (int i = 0; i < REPEATS; i++) {
        file->flipH();
    }

    gettimeofday(&t, NULL);
    endTime = (double) t.tv_sec * 1000000.0 + ((double) t.tv_usec);
    timeElapsed = (endTime - startTime) / 1000.00;
    timeElapsed /= REPEATS;

    cout << "single thread, Total times:" << timeElapsed << endl;


    for (int n = 2; n < 13; n++) {
        gettimeofday(&t, NULL);
        startTime = (double) t.tv_sec * 1000000.0 + ((double) t.tv_usec);
        int thParam[128];
        pthread_t thHandle[128];
        pthread_attr_t thAttr;
        pthread_attr_init(&thAttr);
        pthread_attr_setdetachstate(&thAttr, PTHREAD_CREATE_JOINABLE);
        numThreads = n;
        file->numThreads = n;
        imgData = file->imgData;
        imgWidth = file->info->width;
        imgHeight = file->info->height;
        rowBytes = file->rowBytes;
        MTFlipFunc = MTFlipH;
        for (int i = 0; i < REPEATS; i++) {
            for (int t = 0; t < file->numThreads; t++) {
                thParam[t] = t;
                int thErr = pthread_create(&thHandle[t], &thAttr, MTFlipFunc, (void *) &thParam[t]);

                if (thErr != 0) {
                    cerr << "Error create multi thread!" << endl;
                    exit(EXIT_FAILURE);
                }
            }
            pthread_attr_destroy(&thAttr);
            for (int t = 0; t < file->numThreads; t++) {
                pthread_join(thHandle[t], NULL);
            }
        }
        gettimeofday(&t, NULL);
        endTime = (double) t.tv_sec * 1000000.0 + ((double) t.tv_usec);
        timeElapsed = (endTime - startTime) / 1000.00;
        timeElapsed /= REPEATS;
        cout << "Number Thread[ " << numThreads << " ] Total times:" << timeElapsed << endl;
    }

    file->save("treeV.bmp");
    file->flipV();
    file->save("treeVH.bmp");


    return 0;
}
