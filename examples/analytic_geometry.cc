#include "../analytic-geometry/vector.h"

#include <iostream>

using namespace math_objects::analytic_geometry;

int main() {
    Vector vec = {1, 2, 3};
    std::cout << vec(3) << std::endl;
    std::cout << vec << std::endl;
    std::cout << 9 * vec << std::endl;
    std::cout << vec + Vector{3, -4, 5} << std::endl;

    return 0;
}
