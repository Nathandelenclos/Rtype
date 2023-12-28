/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Graphic.cpp
*/

#include "Graphic.hpp"
#include "Drawable.hpp"

void Graphic::update(std::vector<IObject *> objects) {
    std::cout << "Graphic::update()" << std::endl;
    for (auto &object : objects) {
        auto drawable = dynamic_cast<Drawable*>(object);
        if (drawable) {
            drawable->draw();
        }
    }
}
