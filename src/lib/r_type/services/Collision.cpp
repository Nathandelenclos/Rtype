//
// Created by nathan on 1/10/24.
//

#include "Collision.hpp"
#include "Drawable.hpp"

void Collision::update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) {
    auto drawable = std::dynamic_pointer_cast<Drawable>(component);
    if (!drawable) return;

    for (auto &other: drawable->getDrawablesCollision()) {
        if (Collision::checkCollision(drawable, other)) {
            Collision::cancelMove(event, drawable);
        }
    }
}

bool Collision::checkCollision(const std::shared_ptr<Drawable>& drawable, const std::shared_ptr<Drawable>& other) {
    std::tuple<float, float> pos1 = drawable->getPosition();
    std::tuple<float, float> pos2 = other->getPosition();
    std::tuple<int, int, int, int> size1 = drawable->getRect();
    std::tuple<int, int, int, int> size2 = other->getRect();

    return std::get<0>(pos1) < std::get<0>(pos2) + std::get<2>(size2) &&
           std::get<0>(pos1) + std::get<2>(size1) > std::get<0>(pos2) &&
           std::get<1>(pos1) < std::get<1>(pos2) + std::get<3>(size2) &&
           std::get<1>(pos1) + std::get<3>(size1) > std::get<1>(pos2);
}

void Collision::cancelMove(const std::shared_ptr<Event>& event, const std::shared_ptr<Drawable>& drawable) {
    if (event->key == sf::Keyboard::Key::Left) {
        std::tuple<float, float> pos = drawable->getPosition();
        drawable->setPosition(std::make_tuple(std::get<0>(pos) + 5, std::get<1>(pos)));
    }
    if (event->key == sf::Keyboard::Key::Right) {
        std::tuple<float, float> pos = drawable->getPosition();
        drawable->setPosition(std::make_tuple(std::get<0>(pos) - 5, std::get<1>(pos)));
    }
    if (event->key == sf::Keyboard::Key::Up) {
        std::tuple<float, float> pos = drawable->getPosition();
        drawable->setPosition(std::make_tuple(std::get<0>(pos), std::get<1>(pos) + 5));
    }
    if (event->key == sf::Keyboard::Key::Down) {
        std::tuple<float, float> pos = drawable->getPosition();
        drawable->setPosition(std::make_tuple(std::get<0>(pos), std::get<1>(pos) - 5));
    }
}
