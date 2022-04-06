#ifndef DATASTRUCTURE_STRING_UTILS_H
#define DATASTRUCTURE_STRING_UTILS_H

#include <iostream>

namespace utils {
    /**
     * Decode given uri.
     *
     * @param uri
     * @param length
     * @return
     */
    char *uriDecode(const char *uri, const size_t &length) {
        if (length == 0) {
            return nullptr;
        }
        char *result = new char[length];

        int i = 0;
        int j = 0;
        while (i < length) {
            if (uri[i] == '%') {
                if (i + 2 < length) {
                    int hex1 = uri[++i] - '0';
                    int hex2 = uri[++i] - '0';
                    if (hex1 < 0 || hex2 < 0) {
                        delete[] result;
                        return nullptr;
                    }
                    result[j++] = (hex1 << 4) + hex2;
                    i++;
                } else {
                    delete[] result;
                    return nullptr;
                }
            } else {
                result[j++] = uri[i++];
            }
        }
        return result;
    }
}

#endif