#include "linear-algebra/matrix.h"

#include <iostream>

using math_objects::linear_algebra::Matrix;

int main() {
    Matrix<2, 3, int> m = {
        1, 3, 5,
        2, 4, 6   
    };
    auto mt = m.T();
    std::cout << (m + m) << std::endl;
    std::cout << (9 * m) << std::endl;
    std::cout << m << std::endl;
    std::cout << mt << std::endl;
    std::cout << (m * mt) << std::endl;
    std::cout << m(2, 3) << std::endl;
    std::cout << mt(3, 2) << std::endl;
    std::cout << (Matrix<2, 2, int>({0, 1, 0, 0}) * Matrix<2, 2, int>({0, 0, 0, 1})) << std::endl;

    return 0;
}
