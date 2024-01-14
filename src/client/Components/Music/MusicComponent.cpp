/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#include "MusicComponent.hpp"
#include <iostream>

/**
 * @brief Construct a new Music Component:: Music Component object
 *
 * @param core
 * @param socket
 */
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

/**
 * @brief Destroy the Music Component:: Music Component object
 *
 */
MusicComponent::~MusicComponent()
{
    _music.stop();
}

/**
 * @brief Display the Music Component
 *
 * @param window
 */
void MusicComponent::display(sf::RenderWindow &window)
{
    if (_music.getStatus() != sf::Music::Playing)
        if (_toPlay) {
            _music.play();
            _toPlay = false;
        }
}

/**
 * @brief action, play the music
 */
void MusicComponent::action()
{
    _music.play();
}

/**
 * @brief handle Event for the Music Component
 */
void MusicComponent::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
}

/**
 * @brief set the Sound
 * @param path
 */
void MusicComponent::setSound(const std::string &path)
{
    if (!_music.openFromFile(path))
        throw std::runtime_error("Cannot load " + path);
}

/**
 * @brief isPlaying,
 * @return the status of the music
 */
bool MusicComponent::isPlaying() const
{
    std::cout << "isPlaying " << _music.getStatus() << " " << sf::Music::Playing << std::endl;
    return _music.getStatus() == sf::Music::Playing;
}

/**
 * @brief getLoop get the music loop
 * @return the music loop
 */
bool MusicComponent::getLoop() const
{
    return _music.getLoop();
}

/**
 * @brief getVolume get the music volume
 * @return the music volume
 */
float MusicComponent::getVolume() const
{
    return _volume;
}

/**
 * @brief setLoop set the music loop
 * @param loop
 */
void MusicComponent::setLoop(bool loop)
{
    _music.setLoop(loop);
}

/**
 * @brief setPaused set the music paused
 * @param paused
 */
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

/**
 * @brief setVolume set the music volume
 * @param volume
 */
void MusicComponent::setVolume(float volume)
{
    _volume = volume;
    _music.setVolume(volume);
}

/**
 * @brief handleClick
 */
void MusicComponent::handleClick()
{
}

/**
 * @brief stop, stop the music
 */
void MusicComponent::stop()
{
    std::cout << "stop" << std::endl;
    _music.stop();
}

/**
 * @brief setPersistant set the music persistant
 * @param persistant
 */
void MusicComponent::setPersistant(bool persistant)
{
    _persistant = persistant;
}

/**
 * @brief getPersistant get the music persistant
 * @return the music persistant
 */
bool MusicComponent::getPersistant() const
{
    return _persistant;
}
