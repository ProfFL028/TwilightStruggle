#ifndef LINEAR_ALGEBRA_MATRIX
#define LINEAR_ALGEBRA_MATRIX

#include <iostream>

namespace la {
    class Matrix final {
    public:
        Matrix();
        Matrix(double *data, const short *shape);
        Matrix(const Matrix &m);
        virtual ~Matrix();



    public:
        static Matrix* zeros(const short* shape);
        static Matrix* ones(const short* shape);
        static Matrix* constant(const double& v, const short* shape);

    public:
        Matrix& operator=(const Matrix& v);
        double& operator[](const int& i);

    public:
        Matrix& add(const double& v);
        Matrix& minus(const double& v);
        Matrix& multi(const double& v);
        Matrix& div(const double& v);

        Matrix& operator+=(const double& v);
        Matrix& operator-=(const double& v);
        Matrix& operator*=(const double& v);
        Matrix& operator/=(const double& v);

        Matrix operator+(const double& v);
        Matrix operator-(const double& v);
        Matrix operator*(const double& v);
        Matrix operator/(const double& v);

    public:
        Matrix& add(const Matrix& v);
        Matrix& minus(const Matrix& v);
        Matrix& multi(const Matrix& v);
        Matrix& div(const Matrix& v);

        Matrix& operator+=(const Matrix& v);
        Matrix& operator-=(const Matrix& v);
        Matrix& operator*=(const Matrix& v);
        Matrix& operator/=(const Matrix& v);

        Matrix operator+(const Matrix& v);
        Matrix operator-(const Matrix& v);
        Matrix operator*(const Matrix& v);
        Matrix operator/(const Matrix& v);

    public:
        friend std::ostream& operator<< (std::ostream& out, const Matrix& m);

    public:
        void setData(double *data, const short *shape=nullptr);
        void copyData(const double *data, const short *shape=nullptr);

        double* getData() const;
        short* getShape() const;
        int getDataSize() const;

        void clean();
    private:
        double *data = nullptr;
        short *shape = nullptr;
        bool dataOwner = false;

        void reshape(const short* shape);
    public:
        static const short MAX_SHAPE_SIZE;

    };
}

#endif