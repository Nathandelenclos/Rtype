//
// Created by nathan on 1/10/24.
//

#include "Move.hpp"

void Move::update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) {
    auto drawable = std::dynamic_pointer_cast<Drawable>(component);
    std::string attribute = component->getAttribute();
    if (drawable == nullptr || event == nullptr || attribute != "player " + std::to_string(event->id))
        return;

    auto [x, y] = drawable->getPosition();
    switch (event->key) {
        case sf::Keyboard::Key::Up:
            drawable->setPosition({x, y - 5});
            break;
        case sf::Keyboard::Key::Down:
            drawable->setPosition({x, y + 5});
            break;
        case sf::Keyboard::Key::Left:
            drawable->setPosition({x - 5, y});
            break;
        case sf::Keyboard::Key::Right:
            drawable->setPosition({x + 5, y});
            break;
        default:
            break;
    }
}
