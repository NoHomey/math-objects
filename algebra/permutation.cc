#include <initializer_list>
#include <vector>
#include <iostream>

using Cycle = std::vector<size_t>;

class Permutation {
protected:
size_t* elements;
size_t count;

public:
Permutation(const size_t size)
: elements{nullptr}, count{size} {
    try {
        elements = new size_t[count];
    } catch(std::bad_alloc& error) {
        throw error;
    }
}

Permutation(const Permutation& copyOf)
: Permutation(copyOf.count) {
    for(size_t i = 0; i < count; ++i) {
        elements[i] = copyOf.elements[i];
    }
}

Permutation(const std::initializer_list<size_t> list)
: Permutation(list.size()) {
    bool* check = new bool[count];
    size_t i = 0;
    for(auto e: list) {
        elements[i++] = e;
        check[e - 1] = true;
    }
    bool isPermutation = true;
    for(size_t i = 0; i < count; ++i) {
        if(check[i] == false) {
            isPermutation = false;
            break;
        }
    }
    delete[] check;
    if(!isPermutation) {
        throw std::exception();
    }
}

Permutation(const size_t n, const std::initializer_list<Cycle> list)
: Permutation(n) {
    for(size_t i = 0; i < n; ++i) {
        elements[i] = i + 1;
    }
    for(auto e: list) {
        Permutation result = operator()(e);
        for(size_t i = 0; i < n; ++i) {
            elements[i] = result.elements[i];
        }
    }
}

~Permutation() {
    delete[] elements;
}

size_t size() const {
    return count;
}

size_t operator()(const size_t i) const {
    return elements[i - 1];
}

Permutation operator()(const size_t i, const size_t j) const {
    Permutation result = {*this};
    const size_t i1 = i - 1;
    const size_t j1 = j - 1;
    const size_t tmp = elements[i1];
    result.elements[i1] = elements[j1];
    result.elements[j1] = tmp;

    return result;
}

Permutation operator()(const Cycle& cycle) const {
    const size_t cycleSize = cycle.size();
    Permutation result = Permutation(*this);
    size_t prev = cycle[0];
    size_t next = cycle[1];
    for(size_t i = 1; i < cycleSize; ++i) {
        result.elements[prev - 1] = next;
        prev = next;
        next = cycle[i + 1];
    }
    result.elements[cycle[cycleSize - 1] - 1] = cycle[0];
    
    return result;
}

Permutation operator^(const size_t power) const {
    Permutation result = Permutation(count);
    for(size_t i = 0; i < count; ++i) {
        result.elements[i] = operator()(i + 1);
        for(size_t j = 1; j < power; ++j) {
            result.elements[i] = operator()(result.elements[i]);
        }
    }

    return result;
}
};

std::ostream& operator<<(std::ostream& out, const Permutation& permutaion) {
    size_t size = permutaion.size();
    out << '(';
    for(size_t i = 1; i <= size; ++i) {
        out << permutaion(i) << (i < size ? ' ' : ')');
    }

    return out;
}

int main() {
    Permutation p1 = {1, 2, 4, 3};
    //Permutation p2 = {1, 2, 4, 5};
    std::cout << p1(p1(3)) << std::endl;
    std::cout << (p1^2) << std::endl;
    std::cout << p1(3, 4) << std::endl;
    std::cout << p1(3, 4)({1, 4, 3}) << std::endl;
    std::cout << Permutation(10, {{1, 10, 4, 7, 9, 6, 2}, {3, 8}}) << std::endl;

    return 0;
}