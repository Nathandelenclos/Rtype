/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Graphic.cpp
*/

#include "Graphic.hpp"
#include "Drawable.hpp"

void Graphic::update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component)
{
    auto drawable = std::dynamic_pointer_cast<Drawable>(component);
    if (drawable) {
        auto packetdraw = drawable->getPacket();
        if (drawable->getHasChanged()) {
            _serverSocket->broadcast(packetdraw.get());
            drawable->setHasChanged(false);
        }
    }
}
