/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "Components/AComponent.hpp"
#include <SFML/Audio.hpp>

class MusicComponent : public AComponent
{
  public:

    /**
     * @brief Construct a new Music Component:: Music Component object
     *
     * @param core
     * @param socket
     */
    explicit MusicComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket);

    /**
     * @brief Destroy the Music Component:: Music Component object
     *
     */
    ~MusicComponent() override;

    /**
     * @brief action, play the music
     */
    void action() override;

    /**
     * @brief Display the Music Component
     *
     * @param window
     */
    void display(sf::RenderWindow &window) override;

    /**
     * @brief setSound set the sound of the component
     *
     * @param path
     */
    void setSound(const std::string &path);

    /**
     * @brief isPlaying
     *
     * @return true if the music is playing
     */
    bool isPlaying() const;

    /**
     * @brief getLoop
     *
     * @return true if the music is looping
     */
    bool getLoop() const;

    /**
     * @brief getVolume
     *
     * @return the volume of the music
     */
    float getVolume() const;

    /**
     * @brief getPersistant
     *
     * @return true if the music is persistant
     */
    bool getPersistant() const;

    /**
     * @brief setLoop
     *
     * @param loop
     */
    void setLoop(bool loop);

    /**
     * @brief setPaused
     *
     * @param paused
     */
    void setPaused(bool paused);

    /**
     * @brief setVolume
     *
     * @param volume
     */
    void setVolume(float volume);

    /**
     * @brief setPersistant
     *
     * @param persistant
     */
    void setPersistant(bool persistant);

    /**
     * @brief stop, stop the music
     */
    void stop();

    /**
     * @brief handleEvent, handle the event
     *
     * @param event
     * @param window
     */
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

    /**
     * @brief handleClick, handle the click
     */
    void handleClick();

  private:
    sf::Music _music;
    std::shared_ptr<ClientSocket> _socket;
    bool _toPlay = true;
    float _volume = 100;
    bool _persistant = false;
};
