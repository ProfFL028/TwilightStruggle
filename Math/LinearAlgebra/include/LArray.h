
#ifndef LINEAR_ALGEBRA_LARRAY
#define LINEAR_ALGEBRA_LARRAY

class LArray {
public:
    LArray();
    LArray(double* datas, int size, const char* columnName="");
    virtual ~LArray();

public: 
    char* getColumnName();
    double* getDatas();
    int getLength();

public:
    static int COLUMN_BUF;

private:
    char* columnName;
    double* datas;
    int length;
};

#endif
