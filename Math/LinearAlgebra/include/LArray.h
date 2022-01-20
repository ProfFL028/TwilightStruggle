
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
    LArray(double* datas, int size, const char* columnName="");
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
    static LArray* zeros(int size, const char* columnName="");
    static LArray* ones(int size, const char* columnName="");
    static LArray* constant(int v, int size, const char* columnName="");

public:
// operators.
    LArray* add(double v);
    LArray* minus(double v);
    LArray* multi(double v);
    LArray* div(double v);

    LArray operator+(const double& v) const;
    LArray operator-(const double& v) const;
    LArray operator*(const double& v) const;
    LArray operator/(const double& v) const;

    LArray& operator+=(const double& v);
    LArray& operator-=(const double& v);
    LArray& operator*=(const double& v);
    LArray& operator/=(const double& v);

    LArray& add(const LArray& b);
    LArray& minus(const LArray& b);
    LArray& multi(const LArray& b);
    LArray& div(const LArray& b);

    LArray& operator+=(const LArray& v);
    LArray& operator-=(const LArray& v);
    LArray& operator*=(const LArray& v);
    LArray& operator/=(const LArray& v);

    LArray operator+(const LArray& b) const;
    LArray operator-(const LArray& b) const;
    LArray operator*(const LArray& b) const;
    LArray operator/(const LArray& b) const;



public: 
// get and set methods for attributes.
    char* getColumnName();
    double* getDatas();
    int getLength();

    double& operator[] (int);
    LArray& operator=(const LArray& v);

public:
// static values
    static const int COLUMN_BUF;
    static const char* UNAMED;
private:
// attributes
    char* columnName;
    double* datas;
    int length;
};

}
#endif
