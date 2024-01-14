/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#include "SoundComponent.hpp"

/**
 * @brief Construct a new Sound Component:: Sound Component object
 *
 * @param core
 * @param socket
 */
SoundComponent::SoundComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket) :
    AComponent(core)
{
    _type = ComponentType::SOUND;
    if (!_buffer.loadFromFile("../src/client/assets/sounds/click.wav"))
        throw std::runtime_error("Cannot load click.wav");
    _sound.setBuffer(_buffer);
    _socket = std::move(socket);
}

void SoundComponent::display(sf::RenderWindow &window)
{
}

/**
 * @brief action, play the sound
 */
void SoundComponent::action()
{
    _sound.play();
}

void SoundComponent::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
}

/**
 * @brief setSound, set the sound
 * @param path the path of the sound
 */
void SoundComponent::setSound(const std::string &path)
{
    if (!_buffer.loadFromFile(path))
        throw std::runtime_error("Cannot load " + path);
    _sound.setBuffer(_buffer);
}

/**
 * @brief stop, stop the sound
 */
void SoundComponent::stop()
{
    _sound.stop();
}
