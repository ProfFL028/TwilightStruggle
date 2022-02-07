#include <iostream>
#include <tuple>
#include <gtest/gtest.h>
using namespace std;

TEST(Tuple_test, PropertyTest) {
    tuple<int, double, char*> t0;
    tuple<int, double, char*> t1(1, 0.1, "s");
    t0 = t1;
    get<1>(t1) = 0.2;

    EXPECT_EQ(get<1>(t0), 0.1);
    EXPECT_EQ(get<1>(t1), 0.2);
    EXPECT_EQ(3, tuple_size<decltype(t0)>::value);
}

TEST(Tuple_test, ConstructTest) {
    tuple<int, double> t0;
    tuple<int, double> t1(1, 3.14);

    double d = 5;
    tuple<double&> t2(d);
    tuple<const double&> t3(d + 3.14);

    d = 10;
    EXPECT_EQ(d, get<0>(t2));
}

TEST(Tuple_test, MakeTupleTest) {
    int a = 1;
    double b = 2.0;
    const tuple<int, double>& t0 = make_tuple(a, b);

    int& c = a;
    double& d = b;
    auto t1 = make_tuple(c, d); // tuple<int, double>!!!!!
    auto t2 = make_tuple(ref(c), ref(d)); // tuple<int&, double&>
    auto t3 = make_tuple(cref(c), cref(d));
}

tuple<int, int, int> extendedEuclid(int a, int b) {
    if (b == 0) {
        return make_tuple(a, 1, 0);
    } else {
        int d, x, y;
        tie(d, x, y) = extendedEuclid(b, a % b);
        return make_tuple(d, y, x - (a / b) * y);
    }
}

TEST(Tuple_test, TieIgnoreTest) {
    int i; char c; double b;
    tie(i, c, b) = make_tuple(1, 'a', 5.5);
    cout << i << " " << c << " " << b << endl;
    int d, x, y;
    tie(d, x, y) = extendedEuclid(8, 12);
    tie(d, ignore, ignore) = extendedEuclid(9, 6);

    cout << d << endl;
}
