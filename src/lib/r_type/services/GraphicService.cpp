/*
** EPITECH PROJECT, 2023
** RType
** File description:
** GraphicService.cpp
*/

#include "GraphicService.hpp"
#include "Drawable.hpp"
#include <iostream>

void GraphicService::update(std::vector<IObject *> objects) {
    std::cout << "GraphicService::update()" << std::endl;
    for (auto &object : objects) {
        auto drawable = dynamic_cast<Drawable*>(object);
        if (drawable) {
            drawable->draw();
            std::cout << "GraphicService::update() - " << std::endl;
        }
    }
}
