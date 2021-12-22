#include <iostream>
#include "object.h"

int main() {

    ObjectInfo::regist("A", A::createObject);
    Object* obj = ObjectInfo::forName("A");

    delete obj;
    return 0;
}
