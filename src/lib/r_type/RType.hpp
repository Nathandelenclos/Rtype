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
            for (const auto& entity : _currentScene->getEntities()) {
                if (entity->getAttribute() != "Player")
                    continue;
                for (const auto &component: entity->getComponents()) {
                    auto draw = std::dynamic_pointer_cast<Drawable>(component);
                    auto [x, y] = draw->getPosition();
                    if (x + 200 >= 800)
                        direction = -0.5;
                    else if (x <= 0)
                        direction = 0.5;
                    if (draw)
                        draw->setPosition({x + direction, y});
                }
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
            std::cout << "Event received" << std::endl;
            if (event->key == sf::Keyboard::Key::Space) {
                std::cout << "Space" << std::endl;
                std::shared_ptr<IEntity> entity = std::make_shared<IEntity>();
                std::shared_ptr<Drawable> drawable = std::make_shared<Drawable>();
                std::cout << "Component created" << std::endl;

                drawable->setAttribute("test");
                std::cout << "Attribute set" << std::endl;
                drawable->setPosition({100, 100});
                std::cout << "Position set" << std::endl;
                entity->addComponent(drawable);
                std::cout << "Component added" << std::endl;
                _currentScene->addEntity(entity);
                std::cout << "Entity added" << std::endl;


                std::shared_ptr<Packet> packet = std::make_shared<Packet>();
                packet->code = NEW_COMPONENT;
                packet->data_size = sizeof(NewComponent);
                packet->data = malloc(packet->data_size);
                NewComponent newComponent{};
                newComponent.type = ComponentTypeSocket ::SPRITESOCKET;
                newComponent.id = 0;
                std::cout << "Id set" << std::endl;
                std::cout << "Attribute number set" << std::endl;
                std::memcpy(&newComponent.attribute, drawable->getAttribute(), std::strlen(drawable->getAttribute()));
                std::cout << "Attribute cpy" << std::endl;
                memcpy(packet->data, &newComponent, packet->data_size);
                std::cout << "Attribute set" << std::endl;
                for (auto &[id, address, buffer] : _socket->getClients()) {
                    _socket->send(packet.get(), address);
                }
                free(packet->data);
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
