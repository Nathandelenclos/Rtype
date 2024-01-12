//
// Created by nathan on 1/10/24.
//

#include "Collision.hpp"
#include "Drawable.hpp"
#include "SFML/Graphics/Rect.hpp"

void Collision::update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) {
    auto drawable = std::dynamic_pointer_cast<Drawable>(component);
    if (!drawable) return;
    for (auto &other: drawable->getDrawablesCollision()) {
        if (Collision::checkCollision(drawable, other)) {
            if (drawable->_textureId == BULLET) {
                if (other->_textureId == ENEMY) {
                    drawable->_toDelete = true;
                    other->_toDelete = true;
                }
            }
        }
    }
}

bool Collision::checkCollision(const std::shared_ptr<Drawable>& drawable, const std::shared_ptr<Drawable>& other) {
    Position pos1 = drawable->getPosition();
    Position pos2 = other->getPosition();
    Size size1 = {std::get<2>(drawable->getRect()) * drawable->getScale(), std::get<3>(drawable->getRect()) * drawable->getScale()};
    Size size2 = {std::get<2>(other->getRect()) * other->getScale(), std::get<3>(other->getRect()) * other->getScale()};

    sf::Rect<float> rect1(std::get<0>(pos1), std::get<1>(pos1), std::get<0>(size1), std::get<1>(size1));
    sf::Rect<float> rect2(std::get<0>(pos2), std::get<1>(pos2), std::get<0>(size2), std::get<1>(size2));

    return rect1.intersects(rect2);
}

void Collision::cancelMove(const std::shared_ptr<Event>& event, const std::shared_ptr<Drawable>& drawable) {
    std::cout << "collision" << std::endl;
    std::tuple<float, float> pos = drawable->getPosition();
    std::cout << "pos: " << std::get<0>(pos) << " " << std::get<1>(pos) << std::endl;
    if (event == nullptr) return;
    switch (event->key) {
        case sf::Keyboard::Key::Left:
            std::cout << "left" << std::endl;
            drawable->setPosition(std::make_tuple(std::get<0>(pos) + 5, std::get<1>(pos)));
            break;
        case sf::Keyboard::Key::Right:
            std::cout << "Right" << std::endl;
            drawable->setPosition(std::make_tuple(std::get<0>(pos) - 5, std::get<1>(pos)));
            break;
        case sf::Keyboard::Key::Up:
            std::cout << "Up" << std::endl;
            drawable->setPosition(std::make_tuple(std::get<0>(pos), std::get<1>(pos) - 5));
            break;
        case sf::Keyboard::Key::Down:
            std::cout << "Down" << std::endl;
            drawable->setPosition(std::make_tuple(std::get<0>(pos), std::get<1>(pos) + 5));
            break;
        default:
            break;
    }
}
