//
// Created by talleux on 1/4/24.
//

#include "Lobby.hpp"
#include "Collision.hpp"

LobbyScene::LobbyScene(std::shared_ptr<ServerSocket> serverSocket) : AScene(std::move(serverSocket))
{
    gettimeofday(&_chrono, nullptr);
    initScene();
}

void LobbyScene::initScene()
{
    initEntities();
    initServices();
}

void LobbyScene::initEntities()
{
    std::shared_ptr<IEntity> enemy1 = std::make_shared<IEntity>();
    std::shared_ptr<Drawable> sprite = std::make_shared<Drawable>();
    sprite->setRect({0, 0, 33, 36});
    sprite->setSize({533 * 10, 36 * 10});
    sprite->setPosition({50, 50});
    sprite->setAttribute("sprite enemy");
    sprite->_textureId = ENEMY;
    enemy1->setAttribute("sprite enemy");
    enemy1->addComponent(sprite);

    addEntity(enemy1);

    // addEntity(enemy1);

    // std::shared_ptr<IEntity> player = std::make_shared<IEntity>();
    // std::shared_ptr<IEntity> background = std::make_shared<IEntity>();

    // std::shared_ptr<Drawable> sprite = std::make_shared<Drawable>();
    // sprite->setPosition({50, 50});
    // sprite->setAttribute("Player");
    // player->setAttribute("Player");
    // player->addComponent(sprite);

    // std::shared_ptr<Drawable> backgroundSprite = std::make_shared<Drawable>();
    // backgroundSprite->setPosition({0, 0});
    // background->setAttribute("Background");
    // background->addComponent(backgroundSprite);

    // addEntity(player);
    // addEntity(background);
}

void LobbyScene::initServices()
{
    std::shared_ptr<Graphic> graphic = std::make_shared<Graphic>(_serverSocket);
    std::shared_ptr<Collision> collision = std::make_shared<Collision>(_serverSocket);

    addService(graphic);
    addService(collision);
}

void LobbyScene::update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet, int id)
{
    timeval now{};
    timeval diff{};
    gettimeofday(&now, nullptr);
    timersub(&now, &_chrono, &diff);

    if (event != nullptr)
        _lastEvent = event;

    if (diff.tv_usec >= 25000) {
        for (auto &entity : _entities) {
            for (auto &component : entity->getComponents()) {
                for (auto &service : _services) {
                    service->update(_lastEvent, component);
                }
            }
        }
        _lastEvent = nullptr;
        _chrono = now;
    }

    if (packet != nullptr) {
        if (packet->code == MESSAGE) {
            if (std::string(static_cast<char *>(packet->data)) == "enter game") {
                std::cout << "enter game player id " << id << std::endl;
                std::shared_ptr<IEntity> entity = std::make_shared<IEntity>();
                std::shared_ptr<Drawable> drawable = std::make_shared<Drawable>();

                drawable->setAttribute("player " + std::to_string(id));
                drawable->setPosition({100 * id, 100 * id});
                drawable->setHasChanged(true);
                drawable->_textureId = PLAYER;
                for (const auto& e: getEntities()) {
                    for (const auto& component: e->getComponents()) {
                        std::string attribute = component->getAttribute();
                        auto drawablePlayer = std::dynamic_pointer_cast<Drawable>(component);
                        bool isPlayer = attribute.substr(0, 6) == "player";
                        if (isPlayer && drawablePlayer) {
                            drawable->addDrawableCollision(drawablePlayer);
                            drawablePlayer->addDrawableCollision(drawable);
                        }
                    }
                }
                entity->addComponent(drawable);
                entity->setAttribute("player " + std::to_string(id));
                addEntity(entity);
                std::cout << "Entity added" << std::endl;



                std::shared_ptr<Packet> sendpacket = std::make_shared<Packet>();
                sendpacket->code = NEW_COMPONENT;
                sendpacket->data_size = sizeof(NewComponent);
                sendpacket->data = malloc(sendpacket->data_size);
                NewComponent newComponent{};
                newComponent.type = ComponentTypeSocket ::SPRITESOCKET;
                newComponent.id = PLAYER;
                std::cout << "attribute: " << drawable->getAttribute() << std::endl;
                std::memcpy(&newComponent.attribute, entity->getAttribute().c_str(), 8);
                std::memcpy(&newComponent.attribute2, entity->getAttribute().c_str() + 8, 8);
                memcpy(sendpacket->data, &newComponent, sendpacket->data_size);
                _serverSocket->broadcast(sendpacket.get());
                free(sendpacket->data);

                sendGameState(id);
                broadcastGameState();
            }
            if (std::string(static_cast<char *>(packet->data)) == "exit game") {
                std::cout << "exit game player id " << id << std::endl;
                //delete Entity("player " + std::to_string(id));
                for (auto &entity : _entities) {
                    if (entity->getAttribute() == "player " + std::to_string(id)) {
                        _entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
                        break;
                    }
                }
                std::shared_ptr<Packet> sendpacket = std::make_shared<Packet>();
                sendpacket->code = DELETE_COMPONENT;
                sendpacket->data_size = ("player " + std::to_string(id)).size();
                sendpacket->data = malloc(sendpacket->data_size);
                std::memcpy(sendpacket->data, ("player " + std::to_string(id)).c_str(), sendpacket->data_size);
                _serverSocket->broadcast(sendpacket.get());
                free(sendpacket->data);
            }
        }
    }

    int clientIdDisconnected = _serverSocket->checkClientsDeconnection();

    if (clientIdDisconnected != -1) {
        std::cout << "Client " << clientIdDisconnected << " disconnected" << std::endl;
        for (auto &entity : _entities) {
            if (entity->getAttribute() == "player " + std::to_string(clientIdDisconnected)) {
                _entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
                break;
            }
        }
        std::shared_ptr<Packet> sendpacket = std::make_shared<Packet>();
        sendpacket->code = DELETE_COMPONENT;
        sendpacket->data_size = ("player " + std::to_string(_serverSocket->checkClientsDeconnection())).size();
        sendpacket->data = malloc(sendpacket->data_size);
        std::memcpy(sendpacket->data, ("player " + std::to_string(_serverSocket->checkClientsDeconnection())).c_str(), sendpacket->data_size);
        _serverSocket->broadcast(sendpacket.get());
        free(sendpacket->data);
    }

    if (event == nullptr)
        return;

    if (event->key == sf::Keyboard::Key::Up) {
        for (const auto& entity : getEntities())
            for (const auto& component : entity->getComponents()) {
                if (component->getAttribute() == "player " + std::to_string(id)) {
                    auto draw = std::dynamic_pointer_cast<Drawable>(component);
                    auto [x, y] = draw->getPosition();
                    if (draw)
                        draw->setPosition({x, y - 5});
                }
            }
    }
    if (event->key == sf::Keyboard::Key::Down) {
        for (const auto& entity : getEntities())
            for (const auto& component : entity->getComponents()) {
                if (component->getAttribute() == "player " + std::to_string(id)) {
                    auto draw = std::dynamic_pointer_cast<Drawable>(component);
                    auto [x, y] = draw->getPosition();
                    if (draw)
                        draw->setPosition({x, y + 5});
                }
            }
    }

    if (event->key == sf::Keyboard::Key::Left) {
        for (const auto& entity : getEntities())
            for (const auto& component : entity->getComponents()) {
                if (component->getAttribute() == "player " + std::to_string(id)) {
                    auto draw = std::dynamic_pointer_cast<Drawable>(component);
                    auto [x, y] = draw->getPosition();
                    if (draw)
                        draw->setPosition({x - 5, y});
                }
            }
    }

    if (event->key == sf::Keyboard::Key::Right) {
        for (const auto& entity : getEntities())
            for (const auto& component : entity->getComponents()) {
                if (component->getAttribute() == "player " + std::to_string(id)) {
                    auto draw = std::dynamic_pointer_cast<Drawable>(component);
                    auto [x, y] = draw->getPosition();
                    if (draw)
                        draw->setPosition({x + 5, y});
                }
            }
    }

    if (event->key == sf::Keyboard::Key::Space) {
        std::shared_ptr<IEntity> entity = std::make_shared<IEntity>();
        std::shared_ptr<Drawable> drawable = std::make_shared<Drawable>();

        drawable->setAttribute("test");
        drawable->setPosition({100, 100});
        entity->addComponent(drawable);
        addEntity(entity);
        std::cout << "Entity added" << std::endl;

        std::shared_ptr<Packet> packet = std::make_shared<Packet>();
        packet->code = NEW_COMPONENT;
        packet->data_size = sizeof(NewComponent);
        packet->data = malloc(packet->data_size);
        NewComponent newComponent{};
        newComponent.type = ComponentTypeSocket ::SPRITESOCKET;
        newComponent.id = 0;
        std::memcpy(&newComponent.attribute, drawable->getAttribute(), std::strlen(drawable->getAttribute()));
        memcpy(packet->data, &newComponent, packet->data_size);
        _serverSocket->broadcast(packet.get());
        free(packet->data);
    }

    // if (event->key == sf::Keyboard::Key::Enter) {
    //     pauseScene();
    // }
}
