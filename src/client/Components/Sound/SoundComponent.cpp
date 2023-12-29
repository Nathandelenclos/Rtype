//
// Created by talleux on 12/29/23.
//

#include "SoundComponent.hpp"

SoundComponent::SoundComponent(std::shared_ptr<ClientSocket> socket)
{
    _type = ComponentType::SOUND;
    if (!_buffer.loadFromFile("../src/client/assets/sounds/click.wav"))
        throw std::runtime_error("Cannot load click.wav");
    _sound.setBuffer(_buffer);
    _socket = std::move(socket);
}

void SoundComponent::display(sf::RenderWindow& window)
{
}

void SoundComponent::action()
{
    _sound.play();
}

void SoundComponent::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
}
