/*
** EPITECH PROJECT, 2023
** RType
** File description:
** GameScene.cpp
*/

#include "GameScene.hpp"
#include "ClientCore.hpp"
#include <utility>

GameScene::GameScene(ClientCore *clientCore, std::shared_ptr<ClientSocket> socket) : AScene(clientCore),
                                                                                     _socket(std::move(socket)) {
//    initTextures();
    init_scene();
}

void GameScene::init_scene()
{
    std::shared_ptr<TextComponent> text_ping = std::make_shared<TextComponent>(_clientCore, _socket);
    std::shared_ptr<SpriteComponent> sprite = std::make_shared<SpriteComponent>(_clientCore, _socket);
    std::shared_ptr<MusicComponent> music = std::make_shared<MusicComponent>(_clientCore, _socket);

    music->setSound("../src/client/assets/musics/thisgirl.ogg");
    music->setVolume(10);

    text_ping->setAttribute("text ping");
    text_ping->setText("");
    text_ping->setPosition(sf::Vector2f(0, 550));

    sprite->setAttribute("sprite player");

    addComponent(text_ping);
    addComponent(sprite);
    addComponent(music);
}

void GameScene::receiveData() {
    std::tuple<std::unique_ptr<Packet>, int> packet = _socket->receive();
    std::unique_ptr<Packet> p = std::move(std::get<0>(packet));

    if (p != nullptr) {
        if (p->code == ELEMENT) {
            auto *drawable = static_cast<DrawablePacket *>(p->data);
            //std::cout << "element: " << drawable->x << " " << drawable->y << std::endl;
            for (auto &component: _components) {
                if (component->getType() == ComponentType::SPRITE) {
                    if (component->getAttribute() == "sprite player") {
                        //sprite->setTexture(getTextureByType(element->type));
                        auto *sprite = dynamic_cast<SpriteComponent *>(component.get());
                        sprite->setPosition({drawable->x, drawable->y});
                        sprite->setSize({drawable->sizeHorizontal, drawable->sizeVertical});
                        sprite->setRect({drawable->rectLeft, drawable->rectTop, drawable->rectWidth, drawable->rectHeight});
                    }
                    if (component->getAttribute() == "sprite enemy") {
                        dynamic_cast<SpriteComponent *>(component.get())->setTexture(getTextureByType(Type::ENEMY));
                    }
                    if (component->getAttribute() == "sprite bullet") {
                        dynamic_cast<SpriteComponent *>(component.get())->setTexture(getTextureByType(Type::BULLET));
                    }
                }
            }
        }
        if (p->code == HEARTBEAT) {
            timeval timerecv{};
            timeval now{};
            gettimeofday(&now, nullptr);
            timerecv = *static_cast<timeval *>(p->data);
            timersub(&now, &timerecv, &_pingTime);

            for (auto &component: _components) {
                if (component->getType() == ComponentType::TEXT) {
                    if (component->getAttribute() == "text ping") {
                        dynamic_cast<TextComponent *>(component.get())->setText(
                                "Ping: " + std::to_string(_pingTime.tv_sec * 1000 + _pingTime.tv_usec / 1000) + ", " +
                                std::to_string(_pingTime.tv_usec % 1000) + "ms");
                    }
                }
            }
        }
        if (p->code == NEW_COMPONENT) {
            auto *newComponent = static_cast<NewComponent *>(p->data);
            std::cout << "new component: " << newComponent->type << std::endl;
            std::cout << "new component: " << reinterpret_cast<char *>(&newComponent->attribute) << std::endl;
            if (newComponent->type == ComponentType::SPRITE) {
                auto sprite = std::make_shared<SpriteComponent>(_clientCore, _socket);
                addComponent(sprite);
            }
            if (newComponent->type == ComponentType::TEXT) {
                auto text = std::make_shared<TextComponent>(_clientCore, _socket);
                addComponent(text);
            }
            if (newComponent->type == ComponentType::MUSIC) {
                auto music = std::make_shared<MusicComponent>(_clientCore, _socket);
                addComponent(music);
            }
        }
        free(p->data);
    }
}

sf::Texture GameScene::getTextureByType(Type type) const {
    return _textures.at(type);
}

void GameScene::initTextures() {
    _textures[Type::PLAYER] = sf::Texture();
    _textures[Type::PLAYER].loadFromFile("assets/sprite/player.png");
    _textures[Type::ENEMY] = sf::Texture();
    _textures[Type::ENEMY].loadFromFile("assets/sprite/enemy.png");
    _textures[Type::BULLET] = sf::Texture();
    _textures[Type::BULLET].loadFromFile("assets/sprite/bullet.png");
    _textures[Type::BACKGROUND] = sf::Texture();
    _textures[Type::BACKGROUND].loadFromFile("assets/sprite/background.png");
}

void GameScene::handleEvent(const sf::Event &event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            _clientCore->setCurrentScene("main");
            for (auto &component: _clientCore->getCurrentScene()->getComponents()) {
                if (component->getType() == ComponentType::MUSIC) {
                    dynamic_cast<MusicComponent *>(component.get())->action();
                }
            }
            return;
        }
        if (event.key.code == sf::Keyboard::Up) {
            std::cout << "Up" << std::endl;
            Packet packet{};
            Event event1{};
            packet.code = CODE::EVENT;
            packet.data_size = sizeof(Event);
            packet.data = malloc(packet.data_size);
            event1.key = static_cast<int>(sf::Keyboard::Up);
            event1.eventType = static_cast<int>(sf::Event::KeyPressed);
            memcpy(packet.data, &event1, packet.data_size);
            _socket->send(&packet, _socket->serv_addr);
            free(packet.data);
        }
        if (event.key.code == sf::Keyboard::Down) {
            std::cout << "Down" << std::endl;
            Packet packet{};
            Event event1{};
            packet.code = CODE::EVENT;
            packet.data_size = sizeof(Event);
            packet.data = malloc(packet.data_size);
            event1.key = static_cast<int>(sf::Keyboard::Down);
            event1.eventType = static_cast<int>(sf::Event::KeyReleased);
            memcpy(packet.data, &event1, packet.data_size);
            _socket->send(&packet, _socket->serv_addr);
            free(packet.data);
        }
        if (event.key.code == sf::Keyboard::Space) {
            std::cout << "Space" << std::endl;
            Packet packet{};
            Event event1{};
            packet.code = CODE::EVENT;
            packet.data_size = sizeof(Event);
            packet.data = malloc(packet.data_size);
            event1.key = static_cast<int>(sf::Keyboard::Space);
            event1.eventType = static_cast<int>(sf::Event::KeyPressed);
            memcpy(packet.data, &event1, packet.data_size);
            _socket->send(&packet, _socket->serv_addr);
            free(packet.data);
        }
    }
    for (auto &component: _components) {
        component->handleEvent(event, window);
    }
}
