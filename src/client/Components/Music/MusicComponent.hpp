//
// Created by talleux on 12/29/23.
//

#pragma once

#include "Components/AComponent.hpp"
#include <SFML/Audio.hpp>

class MusicComponent : public AComponent
{
  public:
    explicit MusicComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket);
    ~MusicComponent() override;
    void action() override;
    void display(sf::RenderWindow &window) override;

    void setSound(const std::string &path);
    bool isPlaying() const;
    bool getLoop() const;
    float getVolume() const;
    bool getPersistant() const;
    void setLoop(bool loop);
    void setPaused(bool paused);
    void setVolume(float volume);
    void setPersistant(bool persistant);
    void stop();

    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;
    void handleClick();

  private:
    sf::Music _music;
    std::shared_ptr<ClientSocket> _socket;
    bool _toPlay = true;
    float _volume = 100;
    bool _persistant = false;
};
