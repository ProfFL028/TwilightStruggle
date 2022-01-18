#include <math.h>
#include "MathFunctions.h"
#include <cmath>

double mysqrt(int x) {
    #if defined(HAVE_LOG) && defined(HAVE_EXP)
    double result = exp(log(x) * 0.5);
    std::cout << "Computing sqrt of " << x << " to be " << result
                << " using log and exp" << std::endl;
    #else
    double result = sqrt(x);
    #endif
    return result;
}