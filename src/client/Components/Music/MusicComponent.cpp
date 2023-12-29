//
// Created by talleux on 12/29/23.
//

#include "MusicComponent.hpp"
#include <iostream>

MusicComponent::MusicComponent(std::shared_ptr<ClientSocket> socket)
{
    _type = ComponentType::MUSIC;
    if (!_music.openFromFile("../src/client/assets/musics/music.ogg"))
        throw std::runtime_error("Cannot load music.ogg");
    _music.setLoop(true);
    _music.setVolume(_volume);
    _socket = std::move(socket);
}

MusicComponent::~MusicComponent()
{
    _music.stop();
}

void MusicComponent::display(sf::RenderWindow& window)
{
    if (_music.getStatus() != sf::Music::Playing)
        if (_toPlay) {
            _music.play();
            _toPlay = false;
        }
}

void MusicComponent::action()
{
    _music.play();
}

void MusicComponent::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
}

void MusicComponent::setSound(const std::string& path)
{
    if (!_music.openFromFile(path))
        throw std::runtime_error("Cannot load " + path);
}

bool MusicComponent::isPlaying() const
{
    return _music.getStatus() == sf::Music::Playing;
}

bool MusicComponent::getLoop() const
{
    return _music.getLoop();
}

float MusicComponent::getVolume() const
{
    return _volume;
}

void MusicComponent::setLoop(bool loop)
{
    _music.setLoop(loop);
}

void MusicComponent::setPaused(bool paused)
{
    if (paused)
        _music.play();
    else
        _music.pause();
}

void MusicComponent::setVolume(float volume)
{
    _volume = volume;
    _music.setVolume(volume);
}

void MusicComponent::handleClick()
{

}

void MusicComponent::stop()
{
    std::cout << "stop" << std::endl;
    _music.stop();
}
