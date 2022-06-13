#include <iostream>

using namespace std;

class length {
public:
    explicit length(double l1) : l{l1} {}

    friend length operator+(length l1, length l2) {
        return length{l1.l + l2.l};
    }

    friend ostream &operator<<(ostream &out, const length &l) {
        cout << l.l / 1000.0 << "km" << endl;
        return out;
    }

private:
    double l;
};

namespace sts {
    length operator "" _m(long double l) {
        return length(l);
    }

    length operator "" _km(long double l) {
        return length(1000.0 * l);
    }

    length operator "" _nm(long double l) {
        return length(1852.0 * l);
    }
}

int main() {
    using namespace sts;
    cout << "2km + 30m=" << 2._km + 30.0_m << endl;
    cout << "2.5m + 12nm=" << 2.5_m + 12._nm << endl;
    return 0;
}