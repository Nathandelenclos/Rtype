//
// Created by talleux on 12/13/23.
//

#ifndef BOOTSTRAP_RTYPE_HPP
#define BOOTSTRAP_RTYPE_HPP

#include <iostream>
#include "../IGame.hpp"


class RType : public IGame {
public:
    RType() {
        std::cout << "RType constructor" << std::endl;
    }

    ~RType() override {
        std::cout << "RType destructor" << std::endl;
    }

    void run() override {
        std::cout << "RType::run()" << std::endl;
    }
};


#endif //BOOTSTRAP_RTYPE_HPP
