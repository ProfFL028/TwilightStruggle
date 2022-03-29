#ifdef DATASTRUCTURE_PRIORITYQUUE_H
/**
 * leave the file here. in notice that cpp doesn't allow template splitted from .h
 * see https://stackoverflow.com/questions/1724036/splitting-templated-c-classes-into-hpp-cpp-files-is-it-possible for detail.
 */
/**
 *  let us look at the compilation process. The header files are never compiled. They are only preprocessed.
 *  The preprocessed code is then clubbed with the cpp file which is actually compiled. Now if the compiler has
 *  to generate the appropriate memory layout for the object it needs to know the data type of the template class.
 */
#endif