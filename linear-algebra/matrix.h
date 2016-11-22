#ifndef _MATH_OBJECTS_LINEAR_ALGEBRA_MATRIX_HH

#define _MATH_OBJECTS_LINEAR_ALGEBRA_MATRIX_HH

#include <initializer_list>
#include <stdexcept>
#include <iostream>

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
    for(number i = 0; i < M; ++i) {
        for(number j = 0; j < N; ++j) {
            data[i][j] = *iterator;
            ++iterator;
        }
    }
}

Matrix(F init[M][N]) {
    for(number i = 0; i < M; ++i) {
        for(number j = 0; j < N; ++j) {
            data[i][j] = init[i][j];
        }
    }
}

Matrix(F list[M*N]) {
    for(number i = 0; i < M; ++i) {
        for(number j = 0; j < N; ++j) {
            data[i][j] = list[i + j];
        }
    }
}

Matrix(const Matrix<M, N, F>& matrix) {
    for(number i = 0; i < M; ++i) {
        for(number j = 0; j < N; ++j) {
            data[i][j] = matrix.data[i][j];
        }
    }
}

number size() const {
    return M * N;
}

number rows() const {
    return M;
}

number columns() const {
    return N;
}

F operator()(number i, number j) const {
    --i;
    --j;
    if((i >= M) or (j >= N)) {
        throw std::out_of_range("i must be in the range [1, M] and j in range [1, N]");
    }

    return data[i][j];
}

Matrix<M, N, F> operator+(const Matrix<M, N, F>& matrix) const {
    F sum[M][N];
    for(number i = 0; i < M; ++i) {
        for(number j = 0; j < N; ++j) {
            sum[i][j] = data[i][j] + matrix.data[i][j];
        }
    }

    return Matrix<M, N, F>(sum);
}

template<number K>
Matrix<M, K, F> operator*(const Matrix<N, K, F>& matrix) const {
    F mul[M][K];
    for(number i = 0; i < M; ++i) {
        for(number j = 0; j < K; ++j) {
            mul[i][j] = 0;
            for(number k = 0; k < N; ++k) {
                mul[i][j] += data[i][k] * matrix(k + 1, j + 1);
            }
        }
    }

    return Matrix<M, K, F>(mul);
}

Matrix<N, M, F> T() const {
    F transpose[N][M];
    for(number i = 0; i < N; ++i) {
        for(number j = 0; j < M; ++j) {
            transpose[i][j] = data[j][i];
        }
    }

    return Matrix<N, M, F>(transpose);
}

protected:
F data[M][N];

private:
Matrix() = default;
};

template<number M, number N, typename F>
Matrix<M, N, F> operator*(const F& scalar, const Matrix<M, N, F>& matrix) {
    F prod[M][N];
    for(number i = 0; i < M; ++i) {
        for(number j = 0; j < N; ++j) {
            prod[i][j] = scalar * matrix(i + 1, j + 1);
        }
    }

    return Matrix<M, N, F>(prod);
}

template<number M, number N, typename F>
std::ostream& operator<<(std::ostream& out, const Matrix<M, N, F>& matrix) {
    for(number i = 1; i <= M; ++i) {
        out << '(';
        for(number j = 1; j <= N; ++j) {
            std::cout << matrix(i, j);
            if(j < N) {
                out << ", ";
            }
        }
        std::cout << ')';
        if(i < M) {
            out << std::endl;
        }
    }
}
}
}

#endif
