//
// Created by talleux on 12/29/23.
//

#include "MusicComponent.hpp"
#include <iostream>

MusicComponent::MusicComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket) :
    AComponent(core)
{
    _type = ComponentType::MUSIC;
    if (!_music.openFromFile("../src/client/assets/musics/music.ogg"))
        throw std::runtime_error("Cannot load music.ogg");
    _music.setLoop(true);
    _music.setVolume(_volume);
    _socket = std::move(socket);
    _clientCore = core;
}

MusicComponent::~MusicComponent()
{
    _music.stop();
}

void MusicComponent::display(sf::RenderWindow &window)
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

void MusicComponent::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
}

void MusicComponent::setSound(const std::string &path)
{
    if (!_music.openFromFile(path))
        throw std::runtime_error("Cannot load " + path);
}

bool MusicComponent::isPlaying() const
{
    std::cout << "isPlaying " << _music.getStatus() << " " << sf::Music::Playing << std::endl;
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

    if (paused) {
        _music.play();
        std::cout << "play" << std::endl;
    } else {
        do {
            _music.pause();
            std::cout << "pause" << std::endl;
        } while (_music.getStatus() != sf::Music::Paused && _music.getStatus() != sf::Music::Stopped);
    }
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

void MusicComponent::setPersistant(bool persistant)
{
    _persistant = persistant;
}

bool MusicComponent::getPersistant() const
{
    return _persistant;
}
