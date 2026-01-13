#pragma once
#include <iostream>
#include <limits>

namespace gm {

    template <typename T>
    T good_input() {
        T value;
        
        while (true) {
            std::cin >> value;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Value must be a number! Try again: ";
            } 
            else if (value < 0) {
                std::cout << "Number must be >0! Try again: ";
            }
            else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
    }
}