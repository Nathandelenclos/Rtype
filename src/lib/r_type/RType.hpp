/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RType.hpp
*/

#pragma once

#include <iostream>
#include <utility>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "IGame.hpp"
#include "./services/Graphic.hpp"
#include "./Scenes/IScene.hpp"
#include "./Scenes/Lobby/Lobby.hpp"

class RType : public IGame {
public:
    explicit RType(std::shared_ptr<ServerSocket> socket) {
        _socket = std::move(socket);
        _scenes["Lobby"] = std::make_shared<LobbyScene>(_socket);
        _currentScene = _scenes["Lobby"];
        gettimeofday(&_chrono, nullptr);
    }

    ~RType() override = default;

    void update(std::shared_ptr<Event> event) override {
        timeval now{};
        timeval diff{};
        gettimeofday(&now, nullptr);
        timersub(&now, &_chrono, &diff);
        if (diff.tv_usec >= 1000) {
            for (const auto& entity : _currentScene->getEntities())
                for (const auto& component : entity->getComponents()) {
                    auto draw = std::dynamic_pointer_cast<Drawable>(component);
                    auto [x, y] = draw->getPosition();
                    if (x + 200 >= 800)
                        direction = -0.5;
                    else if (x <= 0)
                        direction = 0.5;
                    if (draw)
                        draw->setPosition({x + direction, y});
                }
            _currentScene->update(event);
            _chrono = now;
        }
        if (event) {
            std::cout << "Event received" << std::endl;
            if (event->key == sf::Keyboard::Key::Up) {
                std::cout << "Up" << std::endl;
                for (const auto& entity : _currentScene->getEntities())
                    for (const auto& component : entity->getComponents()) {
                        auto draw = std::dynamic_pointer_cast<Drawable>(component);
                        auto [x, y] = draw->getPosition();
                        if (draw)
                            draw->setPosition({x, y - 10});
                    }
            }
            if (event->key == sf::Keyboard::Key::Down) {
                for (const auto& entity : _currentScene->getEntities())
                    for (const auto& component : entity->getComponents()) {
                        auto draw = std::dynamic_pointer_cast<Drawable>(component);
                        auto [x, y] = draw->getPosition();
                        if (draw)
                            draw->setPosition({x, y + 10});
                    }
            }
            _currentScene->update(event);
        }
    }

    std::shared_ptr<ServerSocket> _socket;
    std::map<std::string, std::shared_ptr<ISceneRType>> _scenes;
    std::shared_ptr<ISceneRType> _currentScene;
    timeval _chrono;
    float direction = 0.5;
};
