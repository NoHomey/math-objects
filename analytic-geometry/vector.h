#ifndef _MATH_OBJECTS_ANALYTIC_GEOMETRY_VECTOR_HH
#define _MATH_OBJECTS_ANALYTIC_GEOMETRY_VECTOR_HH

#include <initializer_list>
#include <stdexcept>
#include <iostream>

typedef unsigned short number;

namespace math_objects {
namespace analytic_geometry {
class Vector {
public:
Vector(const std::initializer_list<double> list) throw(std::length_error) {
    if(list.size() != 3) {
        throw std::length_error("Vector size is not 3");
    }
    auto iterator = std::begin(list);
    for(number i = 0; i < 3; ++i) {
        Vector::coordinates[i] = *iterator;
        ++iterator;
    };
}

Vector(double coordinates[3]) {
    for(number i = 0; i < 3; ++i) {
        Vector::coordinates[i] = coordinates[i];
    };
}

double operator()(number i) const throw(std::out_of_range) {
    --i;
    if(i > 2) {
        throw std::out_of_range("i must be: 1, 2 or 3");
    }
    return coordinates[i];
}

Vector operator+(const Vector& vector) const {
    double sum[3];
    for(number i = 0; i < 3; ++i) {
        sum[i] = coordinates[i] + vector.coordinates[i];
    };
    return {sum};
}

protected:
double coordinates[3];
};

Vector operator*(const double scalar, const Vector& vector) {
    double prod[3];
    for(number i = 0; i < 3; ++i) {
        prod[i] = vector(i + 1) * scalar;
    };
    return {prod};
}

std::ostream& operator<<(std::ostream& out, const Vector& vector) {
    out << '(';
    for(number i = 1; i < 4; ++i) {
        out << vector(i);
        if(i != 3) {
            out << ", ";
        }
    };
    out << ')';
}
}
}

#endif