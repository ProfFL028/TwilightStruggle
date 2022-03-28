
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream input;
    input.open("../data/sample_file.cpp");
    int bufferSize = 10e5;
    char* buffer = new char[bufferSize];
    if (input.is_open()) {
        bool isMultiLine = false;
        while (!input.eof()) {
            input.getline(buffer, bufferSize);
            char* newLine = new char[bufferSize];
            memset(newLine, 0, bufferSize * sizeof(char));
            int i = 0;
            int newLineIndex = 0;
            bool isInString = false;
            bool isSlash = false;
            while (i < bufferSize && buffer[i] != 0) {
                if (!isMultiLine) {
                    if (!isInString) {
                        if (isSlash && buffer[i] == '/') {
                            newLine[i - 1] = ' ';
                            break;
                        } else if (isSlash && buffer[i] == '*') {
                            newLine[i - 1] = ' ';
                            isMultiLine = true;
                        } else {
                            isSlash=false;
                        }
                        if (buffer[i] == '/') {
                            isSlash = true;
                        }
                    }
                    if (!isMultiLine) {
                        if (buffer[i] == '"') {
                            isInString = !isInString;
                        }
                        newLine[newLineIndex++] = buffer[i];
                    }
                } else {
                    if (buffer[i] == '/' && buffer[i-1] == '*') {
                        isMultiLine = false;
                    }
                }
                i++;
            }
            cout << newLine << endl;
            delete [] newLine;
        }
    } else {
        cerr << "Open file error, please checkout!!" << endl;
    }

    return 0;
}
