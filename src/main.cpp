#include "vector.hpp"
#include "ray.hpp"
#include<iostream>


int main() {
    Vector a (1, 2, 0);
    Vector b (2, 1, 0);
    Ray r (a, b);
    std::cout << r.atT(1) << std::endl;
    std::cout << r.atT(1.7543) << std::endl;
    
    
    return 0;
}