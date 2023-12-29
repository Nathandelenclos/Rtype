//
// Created by talleux on 12/29/23.
//

#include "MainScene.hpp"

MainScene::MainScene(ClientCore* clientCore, std::shared_ptr<ClientSocket> socket) : AScene(clientCore)
{
    _socket = std::move(socket);
    init_scene();
}

void MainScene::init_scene()
{
    std::shared_ptr<MusicComponent> music = std::make_shared<MusicComponent>(_clientCore, _socket);
    std::shared_ptr<SpriteComponent> background = std::make_shared<SpriteComponent>(_clientCore, _socket);
    std::shared_ptr<TextComponent> text = std::make_shared<TextComponent>(_clientCore, _socket);
    std::shared_ptr<SoundComponent> sound = std::make_shared<SoundComponent>(_clientCore, _socket);
    std::shared_ptr<ButtonComponent> button_init_serv = std::make_shared<ButtonComponent>(_clientCore, _socket);
    std::shared_ptr<TextComponent> text_button_init_serv = std::make_shared<TextComponent>(_clientCore, _socket);

    music->setVolume(25);

    background->setSize(sf::Vector2f (800, 600));

    text->setText("R Type");
    text->setPosition(sf::Vector2f(275, 150));
    text->setSize(100);
    text->setColor(sf::Color::Green);

    button_init_serv->setPosition(sf::Vector2f(150, 300));
    button_init_serv->setSize(sf::Vector2f(0.75, 0.50));
    button_init_serv->setCallback(std::bind(&ButtonComponent::handleClickMainScene, button_init_serv));
    button_init_serv->addActionTarget(sound);

    text_button_init_serv->setText("Init Server Connection");
    text_button_init_serv->setPosition(sf::Vector2f(190, 340));
    text_button_init_serv->setSize(50);
    text_button_init_serv->setColor(sf::Color::White);


    addComponent(background);
    addComponent(music);
    addComponent(sound);
    addComponent(text);
    addComponent(button_init_serv);
    addComponent(text_button_init_serv);
}

void MainScene::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    for (auto &component : _components) {
        if (!continueScene)
            return;
        component->handleEvent(event, window);
    }
}

void MainScene::receiveData()
{
}
