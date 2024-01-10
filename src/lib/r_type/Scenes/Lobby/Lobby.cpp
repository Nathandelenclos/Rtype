//
// Created by talleux on 1/4/24.
//

#include "Lobby.hpp"

LobbyScene::LobbyScene(std::shared_ptr<ServerSocket> serverSocket) : AScene(std::move(serverSocket))
{
    initScene();
    gettimeofday(&_chrono, nullptr);
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
    std::shared_ptr<Timer> timer = std::make_shared<Timer>();
    gettimeofday(&timer->_startTime, nullptr);
    timer->_targetTime.tv_sec = 1;
    timer->_targetTime.tv_usec = 0;
    timer->setTarget(sprite);
    timer->setActive(true);
    std::shared_ptr<Animatable> animation = std::make_shared<Animatable>();
    animation->setTarget(sprite);
    animation->setTime({0, 200000});
    animation->_frameIndex = 0;
    animation->_numberFrameToAnim = 8;
    animation->_numberFrame = 8;
    animation->_startFrameIndex = 0;
    gettimeofday(&animation->_chrono, nullptr);
    sprite->setRect({0, 0, 33, 36});
    sprite->setSize({263 * 5, 36 * 5});
    sprite->setScale(5);
    sprite->setPosition({50, 50});
    sprite->setAttribute("sprite enemy");
    sprite->_textureId = ENEMY;
    enemy1->setAttribute("sprite enemy");
    enemy1->addComponent(sprite);
    enemy1->addComponent(timer);
    enemy1->addComponent(animation);

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
    std::shared_ptr<TimeManagement> timeManagement = std::make_shared<TimeManagement>(_serverSocket);
    std::shared_ptr<Animation> animation = std::make_shared<Animation>(_serverSocket);

    addService(graphic);
    addService(animation);
    addService(timeManagement);
}

void LobbyScene::update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet, int id)
{
    timeval now{};
    timeval diff{};
    gettimeofday(&now, nullptr);
    timersub(&now, &_chrono, &diff);

    if (diff.tv_usec >= 25000) {
        for (auto &entity : _entities) {
            for (auto &component : entity->getComponents()) {
                for (auto &service : _services) {
                    service->update(event, component);
                }
            }
        }
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
        std::shared_ptr<IEntity> bullet = std::make_shared<IEntity>();
        std::shared_ptr<Drawable> bullet_sprite = std::make_shared<Drawable>();
        std::shared_ptr<Timer> timer = std::make_shared<Timer>();

        std::shared_ptr<IEntity> player = nullptr;

        for (const auto& entity : getEntities())
            for (const auto& component : entity->getComponents()) {
                if (component->getAttribute() == "player " + std::to_string(id)) {
                    player = entity;
                    break;
                }
            }

        if (player == nullptr)
            return;

        auto draw = std::dynamic_pointer_cast<Drawable>(player->getComponents()[0]);

        if (draw == nullptr)
            return;

        auto [x, y] = draw->getPosition();

        bullet_sprite->setPosition({x, y});
        bullet_sprite->setAttribute("bullet");
        bullet_sprite->_textureId = BULLET;
        bullet_sprite->setSize({200, 200});
        bullet_sprite->setScale(0.5);
        bullet->addComponent(bullet_sprite);
        bullet->setAttribute("bullet");
        timer->_targetTime.tv_sec = 0;
        timer->_targetTime.tv_usec = 500000;
        timer->setTarget(bullet_sprite);
        timer->setActive(true);
        bullet->addComponent(timer);
        addEntity(bullet);

        std::shared_ptr<Packet> sendpacket = std::make_shared<Packet>();
        sendpacket->code = NEW_COMPONENT;
        sendpacket->data_size = sizeof(NewComponent);
        sendpacket->data = malloc(sendpacket->data_size);
        NewComponent newComponent{};
        newComponent.type = ComponentTypeSocket ::SPRITESOCKET;
        newComponent.id = BULLET;
        std::memcpy(&newComponent.attribute, bullet->getAttribute().c_str(), 16);
        memcpy(sendpacket->data, &newComponent, sendpacket->data_size);
        _serverSocket->broadcast(sendpacket.get());
        free(sendpacket->data);

        broadcastGameState();
    }

    // if (event->key == sf::Keyboard::Key::Enter) {
    //     pauseScene();
    // }
}
