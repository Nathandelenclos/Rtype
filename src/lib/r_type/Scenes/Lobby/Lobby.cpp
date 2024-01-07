//
// Created by talleux on 1/4/24.
//

#include "Lobby.hpp"

LobbyScene::LobbyScene(std::shared_ptr<ServerSocket> serverSocket) : AScene(std::move(serverSocket))
{
    initScene();
}

void LobbyScene::initScene()
{
    initEntities();
    initServices();
}

void LobbyScene::initEntities()
{
    std::shared_ptr<IEntity> player = std::make_shared<IEntity>();
    std::shared_ptr<IEntity> background = std::make_shared<IEntity>();

    std::shared_ptr<Drawable> sprite = std::make_shared<Drawable>();
    sprite->setPosition({50, 50});
    sprite->setAttribute("Player");
    player->setAttribute("Player");
    player->addComponent(sprite);

    std::shared_ptr<Drawable> backgroundSprite = std::make_shared<Drawable>();
    backgroundSprite->setPosition({0, 0});
    background->setAttribute("Background");
    background->addComponent(backgroundSprite);

    addEntity(player);
    addEntity(background);
}

void LobbyScene::initServices()
{
    std::shared_ptr<Graphic> graphic = std::make_shared<Graphic>(_serverSocket);

    addService(graphic);
}

void LobbyScene::update(std::shared_ptr<Event> event)
{
    timeval now{};
    timeval diff{};
    gettimeofday(&now, nullptr);
    timersub(&now, &_chrono, &diff);

    if (diff.tv_usec >= 1000) {
        for (auto &entity : _entities) {
            for (auto &component : entity->getComponents()) {
                for (auto &service : _services) {
                    service->update(event, component);
                }
            }
        }
        _chrono = now;
    }

    if (event == nullptr)
        return;

    if (event->key == sf::Keyboard::Key::Up) {
        for (const auto& entity : getEntities())
            for (const auto& component : entity->getComponents()) {
                auto draw = std::dynamic_pointer_cast<Drawable>(component);
                auto [x, y] = draw->getPosition();
                if (draw)
                    draw->setPosition({x, y - 0.5});
            }
    }
    if (event->key == sf::Keyboard::Key::Down) {
        for (const auto& entity : getEntities())
            for (const auto& component : entity->getComponents()) {
                auto draw = std::dynamic_pointer_cast<Drawable>(component);
                auto [x, y] = draw->getPosition();
                if (draw)
                    draw->setPosition({x, y + 0.5});
            }
    }

    if (event->key == sf::Keyboard::Key::Space) {
        std::shared_ptr<IEntity> entity = std::make_shared<IEntity>();
        std::shared_ptr<Drawable> drawable = std::make_shared<Drawable>();

        drawable->setAttribute("test");
        std::cout << "Attribute set" << std::endl;
        drawable->setPosition({100, 100});
        std::cout << "Position set" << std::endl;
        entity->addComponent(drawable);
        std::cout << "Component added" << std::endl;
        addEntity(entity);
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
        _serverSocket->broadcast(packet.get());
        free(packet->data);
    }
}
