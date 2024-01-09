//
// Created by talleux on 12/29/23.
//

#pragma once

#include <SFML/Audio.hpp>
#include "Components/AComponent.hpp"

class SoundComponent : public AComponent {
    public:
        explicit SoundComponent(ClientCore* core, std::shared_ptr<ClientSocket> socket);
        ~SoundComponent() override = default;

        void action() override;
        void display(sf::RenderWindow& window) override;

        void setSound(const std::string& path);
        void stop();

        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;

    private:
        sf::SoundBuffer _buffer;
        sf::Sound _sound;
        std::shared_ptr<ClientSocket> _socket;
};


