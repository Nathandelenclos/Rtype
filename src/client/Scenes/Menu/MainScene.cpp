/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#include "MainScene.hpp"

/**
 * @brief Construct a new Main Scene:: Main Scene object
 *
 * @param clientCore
 * @param socket
 */
MainScene::MainScene(ClientCore *clientCore, std::shared_ptr<ClientSocket> socket) :
    AScene(clientCore)
{
    _socket = std::move(socket);
    init_scene();
}

/**
 * @brief init_scene,  initialize the scene
 *
 */
void MainScene::init_scene()
{
    std::shared_ptr<MusicComponent> music = std::make_shared<MusicComponent>(_clientCore, _socket);
    std::shared_ptr<SpriteComponent> background = std::make_shared<SpriteComponent>(_clientCore, _socket);
    std::shared_ptr<TextComponent> text = std::make_shared<TextComponent>(_clientCore, _socket);
    std::shared_ptr<SoundComponent> sound = std::make_shared<SoundComponent>(_clientCore, _socket);
    std::shared_ptr<ButtonComponent> button_init_serv = std::make_shared<ButtonComponent>(_clientCore, _socket);
    std::shared_ptr<TextComponent> text_button_init_serv = std::make_shared<TextComponent>(_clientCore, _socket);
    std::shared_ptr<TextComponent> text_ping = std::make_shared<TextComponent>(_clientCore, _socket);
    std::shared_ptr<ButtonComponent> button_access_game = std::make_shared<ButtonComponent>(_clientCore, _socket);
    std::shared_ptr<TextComponent> text_button_access_game = std::make_shared<TextComponent>(_clientCore, _socket);
    std::shared_ptr<TextComponent> text_error_not_init = std::make_shared<TextComponent>(_clientCore, _socket);

    music->setVolume(10);
    music->setPersistant(true);

    background->setRect(sf::IntRect(0, 0, 800, 600));
    sf::Texture texture = sf::Texture();
    texture.loadFromFile("../testsprites/bg_800_600/background_1.png");
    background->setTexture(texture);

    text->setText("R Type");
    text->setPosition(sf::Vector2f(275, 100));
    text->setSize(100);
    text->setColor(sf::Color::White);

    button_init_serv->setPosition(sf::Vector2f(150, 250));
    button_init_serv->setSize(sf::Vector2f(0.75, 0.50));
    button_init_serv->setCallback(std::bind(&ButtonComponent::handleClickMainScene, button_init_serv));
    button_init_serv->addActionTarget(sound);
    button_init_serv->addActionTarget(music);

    text_button_init_serv->setText("Init Server Connection");
    text_button_init_serv->setPosition(sf::Vector2f(190, 290));
    text_button_init_serv->setSize(50);
    text_button_init_serv->setColor(sf::Color::White);

    button_access_game->setPosition(sf::Vector2f(150, 425));
    button_access_game->setSize(sf::Vector2f(0.75, 0.50));
    button_access_game->setCallback(std::bind(&ButtonComponent::handleClickAccessGame, button_access_game));
    button_access_game->addActionTarget(sound);
    button_access_game->addActionTarget(music);
    button_access_game->addActionTarget(text_error_not_init);

    text_button_access_game->setText("Access Game");
    text_button_access_game->setPosition(sf::Vector2f(250, 465));
    text_button_access_game->setSize(50);
    text_button_access_game->setColor(sf::Color::White);

    text_ping->setAttribute("text ping");
    text_ping->setText("");
    text_ping->setPosition(sf::Vector2f(0, 550));

    text_error_not_init->setText("");
    text_error_not_init->setAttribute("text error not init");
    text_error_not_init->setPosition(sf::Vector2f(105, 0));
    text_error_not_init->setSize(50);
    text_error_not_init->setColor(sf::Color::Red);

    addComponent(background);
   addComponent(music);
   addComponent(sound);
    addComponent(text);
    addComponent(button_init_serv);
    addComponent(text_button_init_serv);
    addComponent(text_ping);
    addComponent(button_access_game);
    addComponent(text_button_access_game);
    addComponent(text_error_not_init);
}

/**
 * @brief handleEvent, handle the event
 * @param event
 * @param window
 */
void MainScene::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    while (window.pollEvent(const_cast<sf::Event &>(event))) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }
        for (auto &component : _components) {
            if (!continueScene)
                return;
            component->handleEvent(event, window);
        }
    }
}

/**
 * @brief receiveData, receive the data
 */
void MainScene::receiveData()
{
    std::tuple<std::unique_ptr<Packet>, int> packet = _socket->receive();
    std::unique_ptr<Packet> p = std::move(std::get<0>(packet));

    if (p != nullptr) {
        if (p->code == HEARTBEAT) {
            if (_socket->isInit()) {
                timeval timerecv{};
                timeval now{};
                gettimeofday(&now, nullptr);
                timerecv = *static_cast<timeval *>(p->data);
                timersub(&now, &timerecv, &_pingTime);

                for (auto &component : _components) {
                    if (component->getType() == ComponentType::TEXT) {
                        if (component->getAttribute() == "text ping") {
                            dynamic_cast<TextComponent *>(component.get())
                                ->setText(
                                    "Ping: " + std::to_string(_pingTime.tv_sec * 1000 + _pingTime.tv_usec / 1000) +
                                    ", " + std::to_string(_pingTime.tv_usec % 1000) + "ms");
                        }
                        if (component->getAttribute() == "text error not init") {
                            dynamic_cast<TextComponent *>(component.get())->setText("");
                        }
                    }
                }
            }
        }
        free(p->data);
    }
}
