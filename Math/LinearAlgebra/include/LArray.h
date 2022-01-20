
#ifndef LINEAR_ALGEBRA_LARRAY
#define LINEAR_ALGEBRA_LARRAY

namespace la {

class LArray final {
public:
// constructor and destructor
    /**
     * create an empty array.
     * */
    LArray();
    /**
     * create an LArray with given datas and columnName. If columnName is null or empty set to UNAMED.
     * 
     * */
    LArray(double* datas, const int& size, const char* columnName="");
    /**
     * deep copy LArray.
     * https://en.cppreference.com/w/cpp/language/rule_of_three
     * */
    LArray(const LArray& );
    /**
     * destruct LArray. delete datas and columnName string. set data length to 0.
     * */
    virtual ~LArray();

public:
// useful factories for building LArray.
    static LArray* zeros(const int& size, const char* columnName="");
    static LArray* ones(const int& size, const char* columnName="");
    static LArray* constant(const int& v, const int& size, const char* columnName="");

    void copy(const LArray& v);

public:
// operators.
    LArray* add(const double& v);
    LArray* minus(const double& v);
    LArray* multi(const double& v);
    LArray* div(const double& v);

// overload +-*/ operators, avoid use these method for a lot of data copy operators.
    LArray operator+(const double& v) const;
    LArray operator-(const double& v) const;
    LArray operator*(const double& v) const;
    LArray operator/(const double& v) const;

    LArray& operator+=(const double& v);
    LArray& operator-=(const double& v);
    LArray& operator*=(const double& v);
    LArray& operator/=(const double& v);

    LArray* add(const LArray& b);
    LArray* minus(const LArray& b);
    LArray* multi(const LArray& b);
    LArray* div(const LArray& b);

    LArray& operator+=(const LArray& v);
    LArray& operator-=(const LArray& v);
    LArray& operator*=(const LArray& v);
    LArray& operator/=(const LArray& v);

// overload +-*/ operators, avoid use these method for a lot of data copy operators.
    LArray operator+(const LArray& b) const;
    LArray operator-(const LArray& b) const;
    LArray operator*(const LArray& b) const;
    LArray operator/(const LArray& b) const;



public: 
// get and set methods for attributes.
    char* getColumnName();
    double* getDatas();
    int getLength();

    void setColumnName(const char* columnName);
    /**
     * point this->datas to datas, which will not copy the data.
     * */
    void setDatas(double* datas, const int& length);
    void copyDatas(const double* datas, const int& length);

    void clean();
    void cleanData();
    void cleanColumnName();

    double& operator[] (int);
    // as operator + has been overloaded, it needs deepcopy instead of reference.
    LArray& operator=(const LArray& v);

public:
// static values
    static const int COLUMN_BUF;
    static const char* UNAMED;
private:
// attributes
    char* columnName = nullptr;
    double* datas = nullptr;
    int length = 0;

    bool dataOwner = true;
};

}
#endif
