
#include "object.h"

Object::Object() {

}

std::map<std::string, ObjectConstructorFn> ObjectInfo::nameConstructorMap;

Object* ObjectInfo::forName(const std::string objectName) {
    std::map<std::string, ObjectConstructorFn>::const_iterator iter = ObjectInfo::nameConstructorMap.find(objectName);

    return iter->second();
}

bool ObjectInfo::regist(const std::string objectName, ObjectConstructorFn constructorFn) {
    std::pair< std::map< std::string, ObjectConstructorFn >::iterator, bool> res =
        ObjectInfo::nameConstructorMap.insert(std::map<std::string, ObjectConstructorFn>::value_type(objectName, constructorFn));

    return res.second;
}