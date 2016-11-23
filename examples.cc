#include "linear-algebra/matrix.h"

#include <iostream>

using namespace math_objects::linear_algebra;

int main() {
    Matrix<2, 3, int> m = {
        1, 3, 5,
        2, 4, 6   
    };
    auto mt = m.T();
    auto r = RowVector<3, int>({0, 1, 0});
    auto c = ColumnVector<3, int>({0, 1, 0});
    std::cout << (m + m) << std::endl;
    std::cout << (9 * m) << std::endl;
    std::cout << m << std::endl;
    std::cout << mt << std::endl;
    std::cout << (m * mt) << std::endl;
    std::cout << m(2, 3) << std::endl;
    std::cout << mt(3, 2) << std::endl;
    std::cout << (Matrix<2, 2, int>({0, 1, 0, 0}) * Matrix<2, 2, int>({0, 0, 0, 1})) << std::endl;
    std::cout << (3 * r) << std::endl;
    std::cout << (3 * c) << std::endl;
    std::cout << r(2) << std::endl;
    std::cout << c(2) << std::endl;
    std::cout << (r * c) << std::endl;
    std::cout << (c * r) << std::endl;
    int matrix[6][6] = {
        {1, 2, 3, 4, 1, 9},
        {1, 4, 2, 3, 1, 9},
        {1, 3, 4, 2, 1, 9},
        {1, 5, 5, 5, 1, 9},
        {1, 2, 3, 4, 5, 9},
        {9, 9, 9, 9, 9, 9}
    };
    std::cout << det(SquareMatrix<6, int>(matrix)) << std::endl;

    return 0;
}
