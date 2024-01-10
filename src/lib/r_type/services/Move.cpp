/*
** EPITECH PROJECT, 2023
** RTYPE
** File description:
** Move.cpp
*/

#include "Move.hpp"

void Move::update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) {
    auto drawable = std::dynamic_pointer_cast<Drawable>(component);
    std::string attribute = component->getAttribute();
    if (drawable == nullptr || event == nullptr || attribute != "player " + std::to_string(event->id))
        return;

    float speed = 5;
    auto [x, y] = drawable->getPosition();
    if (event->key == sf::Keyboard::Key::Up)
        y -= speed;
    if (event->key == sf::Keyboard::Key::Down)
        y += speed;
    if (event->key == sf::Keyboard::Key::Left)
        x -= speed;
    if (event->key == sf::Keyboard::Key::Right)
        x += speed;
    drawable->setPosition({x, y});
}
