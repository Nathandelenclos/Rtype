//
// Created by talleux on 12/13/23.
//

#include <iostream>
#include "GameEngine.hpp"

GameEngine::GameEngine() {
    std::cout << "GameEngine constructor" << std::endl;
}

GameEngine::~GameEngine() {
    std::cout << "GameEngine destructor" << std::endl;
}

void GameEngine::run() {
    std::cout << "GameEngine::run()" << std::endl;
}
