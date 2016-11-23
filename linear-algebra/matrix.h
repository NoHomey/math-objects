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
Matrix(const std::initializer_list<F> list) {
    if(list.size() != (M * N)) {
        throw std::length_error("Matrix size is not M * N");
    }
    auto iterator = std::begin(list);
    data = new F*[M];
    for(number i = 0; i < M; ++i) {
        data[i] = new F[N];
        for(number j = 0; j < N; ++j) {
            data[i][j] = *iterator;
            ++iterator;
        }
    }
}

Matrix(const F init[M][N]) {
    data = new F*[M];
    for(number i = 0; i < M; ++i) {
        data[i] = new F[N];
        for(number j = 0; j < N; ++j) {
            data[i][j] = init[i][j];
        }
    }
}

Matrix(const F list[M*N]) {
    data = new F*[M];
    for(number i = 0; i < M; ++i) {
        data[i] = new F[N];
        for(number j = 0; j < N; ++j) {
            data[i][j] = list[i + j];
        }
    }
}

Matrix(const Matrix<M, N, F>& matrix) {
    data = new F*[M];
    for(number i = 0; i < M; ++i) {
        data[i] = new F[N];
        for(number j = 0; j < N; ++j) {
            data[i][j] = matrix.data[i][j];
        }
    }
}

~Matrix() {
    for(number i = 0; i < M; ++i) {
        delete[] data[i];
    }
    delete[] data;
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

F operator()(number i) const {
    --i;
    if(M == 1) {
        if(i >= N) {
            throw std::out_of_range("i must be in the range [1, N]");
        }
        return data[0][i];
    } else if (N == 1) {
        if(i >= M) {
            throw std::out_of_range("i must be in the range [1, M]");
        }
        return data[i][0];
    } else {
        throw std::out_of_range("Operation not supported. Matrix is not a Vector");
    }
}

F** raw() const {
    return const_cast<F**>(data);
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
F** data;

private:
Matrix() = default;
};

template<number N, typename F>
using RowVector = Matrix<1, N, F>;

template<number N, typename F>
using ColumnVector = Matrix<N, 1, F>;

template<number N, typename F>
using SquareMatrix = Matrix<N, N, F>;

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

template<typename F>
F raw_det(const number n, F** matrix);

template<number N, typename F>
F det(const SquareMatrix<N, F> matrix) {    
    return raw_det(N, matrix.raw());
}

template<typename F>
F raw_det(const number n, F** matrix) {
    F result = 0;
    if(n == 1) {
        return matrix[0][0];
    } else {
        const number minorN = n - 1;
        for(number i = 0; i < n; ++i) {
            F** minor = new F*[minorN];
            for(number k = 1; k < n; ++k) {
                minor[k - 1] = new F[minorN];
                for(number j = 0; j < n; ++j) {
                    if(j != i) {
                        minor[k - 1][j - (j < i ? 0 : 1)] = matrix[k][j];
                    }
                }
            }
            result += ((i % 2) == 0 ? 1 : -1) * matrix[0][i] * raw_det<F>(minorN, minor);
            for(number k = 0; k < minorN; ++k) {
                delete[] minor[k];
            }
            delete[] minor;
        }
    }
    return result;
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
