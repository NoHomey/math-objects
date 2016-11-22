#include "linear-algebra/matrix.h"

#include <iostream>

int main() {
    math_objects::linear_algebra::Matrix<2, 2, int> m = {
        1, 2,
        3, 4   
    };

    std::cout << m(2, 2) << std::endl;

    return 0;
}
