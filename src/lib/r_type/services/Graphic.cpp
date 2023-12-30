/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Graphic.cpp
*/

#include "Graphic.hpp"
#include "Drawable.hpp"

void Graphic::update(IGame *game, std::vector<IObject*> objects) {
    for (auto &object : objects) {
        auto drawable = dynamic_cast<Drawable*>(object);
        if (drawable) {
            drawable->draw();
        }
    }
}
