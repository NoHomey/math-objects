#ifndef _MATH_OBJECTS_LINEAR_ALGEBRA_MATRIX_HH

#define _MATH_OBJECTS_LINEAR_ALGEBRA_MATRIX_HH

#include <initializer_list>
#include <stdexcept>

typedef unsigned int number;

namespace math_objects {
namespace linear_algebra {
template<number M, number N, typename F>
class Matrix {
public:
Matrix(std::initializer_list<F> list) {
    if(list.size() != (M * N)) {
        throw std::length_error("Matrix size is not M * N");
    }
    auto iterator = std::begin(list);
    rows = M;
    columns = N;
    for(number i = 0; i < M; ++i) {
        for(number j = 0; j < N; ++j) {
            data[i][j] = *iterator;
            ++iterator;
        }
    }
}

F operator()(number i, number j) const {
    --i;
    --j;
    if((i > M) or (j > N)) {
        throw std::out_of_range("i must be in the range [1, M] and j in range [1, N]");
    }
    return data[i][j];
}

protected:
F data[M][N];
number rows;
number columns;
};
}
}

#endif
