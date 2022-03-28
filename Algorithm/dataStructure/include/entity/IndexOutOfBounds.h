//
// Created by Administrator on 2021/9/9.
//

#ifndef ALGORITHM_INDEXOUTOFBOUNDS_H
#define ALGORITHM_INDEXOUTOFBOUNDS_H

#include <iostream>
#include <exception>

using namespace std;

class IndexOutOfBounds : public exception {
public:
    const char* what() const throw() ;
};


#endif //ALGORITHM_INDEXOUTOFBOUNDS_H
