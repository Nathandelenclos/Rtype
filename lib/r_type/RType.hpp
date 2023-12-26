/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RType.hpp
*/

#pragma once

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
