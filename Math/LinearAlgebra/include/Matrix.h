#ifndef LINEAR_ALGEBRA_MATRIX
#define LINEAR_ALGEBRA_MATRIX

namespace la {
    class Matrix final {
    public:
        Matrix();

        Matrix(double *data, const short *shape);

        Matrix(const Matrix &m);

        virtual ~Matrix();

    public:
        Matrix& operator=(const Matrix& v);
        double& operator[](const int& i);

    public:
        void setData(double *data, const short *shape);
        void copyData(const double *data, const short *shape);

        double* getData();
        short* getShape();
        int getDataSize();

        void clean();
    private:
        double *data = nullptr;
        short *shape = nullptr;
        bool dataOwner = false;

        void copyShape(const short* shape);
    public:
        static const short MAX_SHAPE_SIZE;

    };
}

#endif