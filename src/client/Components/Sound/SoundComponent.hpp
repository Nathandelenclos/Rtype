//
// Created by talleux on 12/29/23.
//

#pragma once

#include <SFML/Audio.hpp>
#include "../AComponent.hpp"

class SoundComponent : public AComponent {
    public:
        explicit SoundComponent(std::shared_ptr<ClientSocket> socket);
        ~SoundComponent() override = default;

        void action() override;
        void display(sf::RenderWindow& window) override;

        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;

    private:
        sf::SoundBuffer _buffer;
        sf::Sound _sound;
        std::shared_ptr<ClientSocket> _socket;
};


