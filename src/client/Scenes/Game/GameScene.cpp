/*
** EPITECH PROJECT, 2023
** RType
** File description:
** GameScene.cpp
*/

#include "GameScene.hpp"
#include "ClientCore.hpp"
#include <utility>

/**
 * @brief Construct a new Game Scene:: Game Scene object
 *
 * @param clientCore
 * @param socket
 */
GameScene::GameScene(ClientCore *clientCore, std::shared_ptr<ClientSocket> socket) :
    AScene(clientCore),
    _socket(std::move(socket))
{
    initTextures();
    init_scene();
}

/**
 * @brief init_scene, init the scene
 */
void GameScene::init_scene()
{
    std::shared_ptr<TextComponent> text_ping = std::make_shared<TextComponent>(_clientCore, _socket);
    // std::shared_ptr<SpriteComponent> sprite = std::make_shared<SpriteComponent>(_clientCore, _socket);
    std::shared_ptr<MusicComponent> music = std::make_shared<MusicComponent>(_clientCore, _socket);
    std::shared_ptr<SoundComponent> sound_new_player = std::make_shared<SoundComponent>(_clientCore, _socket);
    std::shared_ptr<SoundComponent> sound_player_left = std::make_shared<SoundComponent>(_clientCore, _socket);

    music->setSound("../src/client/assets/musics/thisgirl.ogg");
    music->setVolume(10);

    text_ping->setAttribute("text ping");
    text_ping->setText("");
    text_ping->setPosition(sf::Vector2f(0, 550));

    // sprite->setAttribute("Player");

    sound_new_player->setAttribute("new player");

    sound_player_left->setAttribute("player left");

    // addComponent(sprite);
    addComponent(music);
    addComponent(text_ping);
    addComponent(sound_new_player);
    addComponent(sound_player_left);
}

/**
 * @brief receiveData, receive data from the server
 */
void GameScene::receiveData()
{
    std::tuple<std::unique_ptr<Packet>, int> packet = _socket->receive();
    std::unique_ptr<Packet> p = std::move(std::get<0>(packet));
    while (p != nullptr) {
        if (p->code == ELEMENT) {
            auto *drawable = static_cast<DrawablePacket *>(p->data);
            for (auto &component : _components) {
                if (component->getType() == ComponentType::SPRITE) {
                    char *attributechar = static_cast<char *>(malloc(16));
                    std::memset(attributechar, 0, 16);
                    std::memcpy(attributechar, &drawable->attribute, 8);
                    std::memcpy(attributechar + 8, &drawable->attribute2, 8);
                    std::string attributeString(attributechar);
                    std::string componentAttribute = component->getAttribute();
                    if (component->getAttribute() == attributeString) {
                        std::cout << "element: " << drawable->rectLeft << " " << drawable->rectTop << " "
                                  << drawable->rectWidth << " " << drawable->rectHeight << std::endl;
                        // sprite->setTexture(getTextureByType(element->type));
                        auto *sprite = dynamic_cast<SpriteComponent *>(component.get());
                        sprite->setPosition({drawable->x, drawable->y});
                        sprite->setSize({drawable->sizeHorizontal, drawable->sizeVertical});
                        sprite->setRect(
                            {drawable->rectLeft, drawable->rectTop, drawable->rectWidth, drawable->rectHeight});
                    }
                    if (component->getAttribute() == "sprite enemy") {
                        dynamic_cast<SpriteComponent *>(component.get())->setTexture(getTextureByType(Type::ENEMY));
                    }
                    if (component->getAttribute() == "sprite bullet") {
                        dynamic_cast<SpriteComponent *>(component.get())->setTexture(getTextureByType(Type::BULLET));
                    }
                    if (component->getAttribute() == "sprite bg1") {
                        dynamic_cast<SpriteComponent *>(component.get())
                            ->setTexture(getTextureByType(Type::BACKGROUND1));
                    }
                    // if (component->getAttribute() == "sprite bg2") {
                    //     dynamic_cast<SpriteComponent
                    //     *>(component.get())->setTexture(getTextureByType(Type::BACKGROUND2));
                    // }
                    // if (component->getAttribute() == "sprite bg3") {
                    //     dynamic_cast<SpriteComponent
                    //     *>(component.get())->setTexture(getTextureByType(Type::BACKGROUND3));
                    // }
                    // if (component->getAttribute() == "sprite bg4") {
                    //     dynamic_cast<SpriteComponent
                    //     *>(component.get())->setTexture(getTextureByType(Type::BACKGROUND4));
                    // }
                }
            }
        }
        if (p->code == HEARTBEAT) {
            timeval timerecv{};
            timeval now{};
            gettimeofday(&now, nullptr);
            timerecv = *static_cast<timeval *>(p->data);
            timersub(&now, &timerecv, &_pingTime);

            for (auto &component : _components) {
                if (component->getType() == ComponentType::TEXT) {
                    if (component->getAttribute() == "text ping") {
                        dynamic_cast<TextComponent *>(component.get())
                            ->setText("Ping: " + std::to_string(_pingTime.tv_sec * 1000 + _pingTime.tv_usec / 1000) +
                                      ", " + std::to_string(_pingTime.tv_usec % 1000) + "ms");
                    }
                }
            }
        }
        if (p->code == NEW_COMPONENT) {
            auto *newComponent = static_cast<NewComponent *>(p->data);
            newComponent->type = static_cast<ComponentTypeSocket>(ComponentType::SPRITE);
            char *attributechar = static_cast<char *>(malloc(16));
            std::memset(attributechar, 0, 16);
            std::memcpy(attributechar, &newComponent->attribute, 16);
            // std::memcpy(attributechar + 8, &newComponent->attribute2, 8);
            std::cout << "attribute: " << reinterpret_cast<char *>(&newComponent->attribute) << std::endl;
            std::cout << "attribute2: " << reinterpret_cast<char *>(&newComponent->attribute2) << std::endl;
            std::string attributeString(attributechar);
            attributeString = attributeString.substr(0, attributeString.find('\001'));
            std::cout << "newComponent: " << attributeString << " " << newComponent->x << " " << newComponent->y
                      << " id: " << newComponent->id << std::endl;
            for (auto &component : _components) {
                if (component->getType() == ComponentType::SPRITE) {
                    if (component->getAttribute() == reinterpret_cast<char *>(&newComponent->attribute)) {
                        _components.erase(std::remove(_components.begin(), _components.end(), component),
                                          _components.end());
                        break;
                    }
                }
            }

            if (newComponent->type == ComponentType::SPRITE) {
                auto sprite = std::make_shared<SpriteComponent>(_clientCore, _socket);
                sprite->setAttribute(attributeString);
                std::cout << "new component: " << newComponent->id << std::endl;
                sprite->setTexture(getTextureByType((Type)newComponent->id));
                sprite->setPosition({newComponent->x, newComponent->y});
                sprite->setSize({newComponent->sizeHorizontal, newComponent->sizeVertical});
                sprite->setRect(
                    {newComponent->rectLeft, newComponent->rectTop, newComponent->rectWidth, newComponent->rectHeight});
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
        if (p->code == DELETE_COMPONENT) {
            std::string attribute = static_cast<char *>(p->data);
            for (auto &component : _components) {
                if (component->getAttribute() == attribute) {
                    _components.erase(std::remove(_components.begin(), _components.end(), component),
                                      _components.end());
                    break;
                }
            }
            std::cout << "delete component: " << attribute << std::endl;
        }
        if (p->code == EVENT) {
            auto *data = static_cast<char *>(p->data);
            std::string message(data);
            if (message == "new player") {
                for (auto &component : _components) {
                    if (component->getType() == ComponentType::SOUND) {
                        if (component->getAttribute() == "new player") {
                            dynamic_cast<SoundComponent *>(component.get())->action();
                        }
                    }
                }
            } else if (message == "player left") {
                for (auto &component : _components) {
                    if (component->getType() == ComponentType::SOUND) {
                        if (component->getAttribute() == "player left") {
                            dynamic_cast<SoundComponent *>(component.get())->action();
                        }
                    }
                }
            }
        }
        free(p->data);
        packet = _socket->receive();
        p = std::move(std::get<0>(packet));
    }
}

/**
 * @brief getTextureByType, get the texture by type
 * @param type
 * @return texture of the type
 */
sf::Texture GameScene::getTextureByType(Type type) const
{
    return _textures.at(type);
}

/**
 * @brief initTextures, init the textures
 */
void GameScene::initTextures()
{
    _textures[Type::MISSINGTXT] = sf::Texture();
    _textures[Type::MISSINGTXT].loadFromFile("../src/client/assets/missing.png");
    _textures[Type::PLAYER] = sf::Texture();
    _textures[Type::PLAYER].loadFromFile("../sprites/r-typesheet1.gif");
    _textures[Type::ENEMY] = sf::Texture();
    _textures[Type::ENEMY].loadFromFile("../testsprites/r-typesheet5.png");
    _textures[Type::BULLET] = sf::Texture();
    _textures[Type::BULLET].loadFromFile("../sprites/r-typesheet1.gif");
    _textures[Type::BACKGROUND1] = sf::Texture();
    _textures[Type::BACKGROUND1].loadFromFile("../testsprites/bg_800_600/background_1.png");
    _textures[Type::BACKGROUND2] = sf::Texture();
    _textures[Type::BACKGROUND2].loadFromFile("../testsprites/bg_800_600/background_2.png");
    _textures[Type::BACKGROUND3] = sf::Texture();
    _textures[Type::BACKGROUND3].loadFromFile("../testsprites/bg_800_600/background_3.png");
    _textures[Type::BACKGROUND4] = sf::Texture();
    _textures[Type::BACKGROUND4].loadFromFile("../testsprites/bg_800_600/background_4.png");
}

/**
 * @brief handleEvent, handle the event
 * @param event
 * @param window
 */
void GameScene::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    while (window.pollEvent(const_cast<sf::Event &>(event))) {
        if (event.type == sf::Event::Closed) {
            window.close();
            Packet packet{};
            packet.code = MESSAGE;
            packet.data_size = 9;
            packet.data = malloc(packet.data_size);
            memcpy(packet.data, "exit game", packet.data_size);
            _socket->send(&packet, _socket->serv_addr);
            return;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
            _clientCore->setCurrentScene("main");
            for (auto &component : _clientCore->getCurrentScene()->getComponents()) {
                if (component->getType() == ComponentType::MUSIC) {
                    dynamic_cast<MusicComponent *>(component.get())->action();
                }
            }
            Packet packet{};
            packet.code = MESSAGE;
            packet.data_size = 9;
            packet.data = malloc(packet.data_size);
            memcpy(packet.data, "exit game", packet.data_size);
            _socket->send(&packet, _socket->serv_addr);
            return;
        }
    }

    if (!window.hasFocus())
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)) {
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
        Packet packet{};
        Event event1{};
        packet.code = CODE::EVENT;
        packet.data_size = sizeof(Event);
        packet.data = malloc(packet.data_size);
        event1.key = static_cast<int>(sf::Keyboard::Left);
        event1.eventType = static_cast<int>(sf::Event::KeyPressed);
        memcpy(packet.data, &event1, packet.data_size);
        _socket->send(&packet, _socket->serv_addr);
        free(packet.data);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
        Packet packet{};
        Event event1{};
        packet.code = CODE::EVENT;
        packet.data_size = sizeof(Event);
        packet.data = malloc(packet.data_size);
        event1.key = static_cast<int>(sf::Keyboard::Right);
        event1.eventType = static_cast<int>(sf::Event::KeyPressed);
        memcpy(packet.data, &event1, packet.data_size);
        _socket->send(&packet, _socket->serv_addr);
        free(packet.data);
    }

    for (auto &component : _components) {
        component->handleEvent(event, window);
    }
}
