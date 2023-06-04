#include <iostream>
#include <fstream>

/**
 * save data to file.
 * Problems: It truncate the file before updating it. What if it needs to be read concurrency?
 * Writing data to files may not be atomic, depending on the size of the write. Concurrency readers might get incomplete code.
 * What is the data actually persisted to the disk?
 * @param fileName
 * @param data
 * @return
 */
bool saveData(std::string fileName, const char* data, size_t length) {

    std::ofstream fout(fileName, std::ios::binary);
    fout.write(data, length);

    fout.close();
}

bool saveDataAtomicRename(std::string fileName, const char* data, size_t length) {
    std::string tmpName = fileName + ".tmp";
    std::ofstream tmp(tmpName, std::ios::binary);
    std::cout << sizeof(data) << std::endl;
    tmp.write(data, length);
    tmp.flush();
    tmp.close();

    std::rename(tmpName.c_str(), fileName.c_str());
    std::remove(tmpName.c_str());
}

int main() {
    char bytes[] = {'H', 'l', 'L', '1', 'O', ' '};
    saveDataAtomicRename("data.txt", bytes, sizeof(bytes));
    return 0;
}


