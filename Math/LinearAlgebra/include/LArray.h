
#ifndef LINEAR_ALGEBRA_LARRAY
#define LINEAR_ALGEBRA_LARRAY

namespace la {

class LArray final {
public:
// constructor and destructor
    LArray();
    LArray(double* datas, int size, const char* columnName="");
    LArray(const LArray& );  // this is important!!!! for you need to copy all datas instead of just copy pointer.
    virtual ~LArray();

public:
// useful factories for building LArray.
    static LArray* zeros(int size, const char* columnName="");
    static LArray* ones(int size, const char* columnName="");
    static LArray* constant(int v, int size, const char* columnName="");

public:
// operators.
    LArray* add(double v);
    LArray* minus(double v);
    LArray* multi(double v);
    LArray* div(double v);

public: 
// get and set methods for attributes.
    char* getColumnName();
    double* getDatas();
    int getLength();

    double& operator[] (int);
    LArray& operator=(const LArray& v); // this is important!!!! for you need to copy all datas instead of just copy pointer.
    LArray operator+(const LArray& b) const; 

public:
// static values
    static int COLUMN_BUF;

private:
// attributes
    char* columnName;
    double* datas;
    int length;
};

}
#endif
