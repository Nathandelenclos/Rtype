//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include <vector>
#include <memory>
#include <sys/time.h>
#include "../Components/IComponent.hpp"
#include "../Components/Sound/SoundComponent.hpp"
#include "../Components/Music/MusicComponent.hpp"

class IScene {
    public:
        explicit IScene(ClientCore* clientCore) : _clientCore(clientCore) {}
        virtual ~IScene() = default;

        virtual void addComponent(std::shared_ptr<IComponent> component) = 0;
        virtual void display(sf::RenderWindow& window) = 0;

        virtual void update() = 0;
        virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
        virtual void receiveData() = 0;

        virtual void pauseScene() = 0;
        virtual void resumeScene() = 0;
        virtual void stopScene() = 0;

    bool continueScene = true;
private:
        std::vector<std::shared_ptr<IComponent>> _components;
    protected:
        ClientCore* _clientCore;
        timeval _pingTime{};
};
