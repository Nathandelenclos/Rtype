//
// Created by talleux on 1/4/24.
//

#include "Lobby.hpp"
#include "Collision.hpp"
#include "Graphic.hpp"
#include "Move.hpp"

LobbyScene::LobbyScene(std::shared_ptr<ServerSocket> serverSocket) : AScene(std::move(serverSocket))
{
    initScene();
    gettimeofday(&_chrono, nullptr);
    _bulletTriggerLimiter = {0, 0};
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
    timer->_targetTime.tv_sec = 0;
    timer->_targetTime.tv_usec = 50000;
    timer->setTarget(sprite);
    timer->setActive(true);
    std::shared_ptr<Animatable> animation = std::make_shared<Animatable>();
    animation->setTarget(sprite);
    animation->setTime({0, 200000});
    animation->_frameIndex = 0;
    animation->_numberFrameToAnim = 8;
    animation->_numberFrame = 8;
    animation->_startFrameIndex = 0;
    animation->_frameForOnePicture = 1;
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

    std::shared_ptr<IEntity> floor_bg = std::make_shared<IEntity>();
    std::shared_ptr<Drawable> sprite_floor_bg = std::make_shared<Drawable>();
    std::shared_ptr<Animatable> animation_floor_bg = std::make_shared<Animatable>();
    sprite_floor_bg->setRect({0, 0, 800, 30});
    sprite_floor_bg->setSize({1600 * 4, 30 * 4});
    sprite_floor_bg->setScale(4);
    sprite_floor_bg->setPosition({0, 480});
    sprite_floor_bg->setAttribute("sprite floor bg");
    sprite_floor_bg->_textureId = FLOOR_BACKGROUND;
    gettimeofday(&animation_floor_bg->_chrono, nullptr);
    animation_floor_bg->setTarget(sprite_floor_bg);
    animation_floor_bg->setTime({0, 10000});
    animation_floor_bg->_frameIndex = 0;
    animation_floor_bg->_numberFrameToAnim = 800 * 4;
    animation_floor_bg->_numberFrame = 1600 * 4;
    animation_floor_bg->_startFrameIndex = 0;
    animation_floor_bg->_frameForOnePicture = 800 * 4;
    floor_bg->setAttribute("sprite floor bg");
    floor_bg->addComponent(sprite_floor_bg);
    floor_bg->addComponent(animation_floor_bg);

    std::shared_ptr<IEntity> roof_bg = std::make_shared<IEntity>();
    std::shared_ptr<Drawable> sprite_roof_bg = std::make_shared<Drawable>();
    std::shared_ptr<Animatable> animation_roof_bg = std::make_shared<Animatable>();
    sprite_roof_bg->setRect({0, 0, 800, 30});
    sprite_roof_bg->setSize({1600 * 4, 30 * 4});
    sprite_roof_bg->setScale(4);
    sprite_roof_bg->setPosition({0, 0});
    sprite_roof_bg->setAttribute("sprite roof bg");
    sprite_roof_bg->_textureId = ROOF_BACKGROUND;
    gettimeofday(&animation_roof_bg->_chrono, nullptr);
    animation_roof_bg->setTarget(sprite_roof_bg);
    animation_roof_bg->setTime({0, 10000});
    animation_roof_bg->_frameIndex = 0;
    animation_roof_bg->_numberFrameToAnim = 800 * 4;
    animation_roof_bg->_numberFrame = 1600 * 4;
    animation_roof_bg->_startFrameIndex = 0;
    animation_roof_bg->_frameForOnePicture = 800 * 4;
    roof_bg->setAttribute("sprite roof bg");
    roof_bg->addComponent(sprite_roof_bg);
    roof_bg->addComponent(animation_roof_bg);

    std::shared_ptr<IEntity> bg1 = std::make_shared<IEntity>();
    std::shared_ptr<Drawable> sprite_bg1 = std::make_shared<Drawable>();
    std::shared_ptr<Animatable> animation_bg1 = std::make_shared<Animatable>();
    sprite_bg1->setRect({0, 0, 800, 600});
    sprite_bg1->setSize({1600, 600});
    sprite_bg1->setScale(1);
    sprite_bg1->setPosition({0, 0});
    sprite_bg1->setAttribute("sprite bg1");
    sprite_bg1->_textureId = BACKGROUND1;
    gettimeofday(&animation_bg1->_chrono, nullptr);
    animation_bg1->setTarget(sprite_bg1);
    animation_bg1->setTime({0, 10000});
    animation_bg1->_frameIndex = 0;
    animation_bg1->_numberFrameToAnim = 800;
    animation_bg1->_numberFrame = 1600;
    animation_bg1->_startFrameIndex = 0;
    animation_bg1->_frameForOnePicture = 800;
    bg1->setAttribute("sprite bg1");
    bg1->addComponent(sprite_bg1);
    bg1->addComponent(animation_bg1);

    std::shared_ptr<IEntity> bg2 = std::make_shared<IEntity>();
    std::shared_ptr<Drawable> sprite_bg2 = std::make_shared<Drawable>();
    std::shared_ptr<Animatable> animation_bg2 = std::make_shared<Animatable>();
    sprite_bg2->setRect({0, 0, 800, 600});
    sprite_bg2->setSize({1600, 600});
    sprite_bg2->setScale(1);
    sprite_bg2->setPosition({0, 0});
    sprite_bg2->setAttribute("sprite bg2");
    sprite_bg2->_textureId = BACKGROUND1;
    gettimeofday(&animation_bg2->_chrono, nullptr);
    animation_bg2->setTarget(sprite_bg2);
    animation_bg2->setTime({0, 30000});
    animation_bg2->_frameIndex = 0;
    animation_bg2->_numberFrameToAnim = 800;
    animation_bg2->_numberFrame = 1600;
    animation_bg2->_startFrameIndex = 0;
    animation_bg2->_frameForOnePicture = 800;
    bg2->setAttribute("sprite bg2");
    bg2->addComponent(sprite_bg2);
    bg2->addComponent(animation_bg2);

    std::shared_ptr<IEntity> bg3 = std::make_shared<IEntity>();
    std::shared_ptr<Drawable> sprite_bg3 = std::make_shared<Drawable>();
    std::shared_ptr<Animatable> animation_bg3 = std::make_shared<Animatable>();
    sprite_bg3->setRect({0, 0, 800, 600});
    sprite_bg3->setSize({1600, 600});
    sprite_bg3->setScale(1);
    sprite_bg3->setPosition({0, 0});
    sprite_bg3->setAttribute("sprite bg3");
    sprite_bg3->_textureId = BACKGROUND1;
    gettimeofday(&animation_bg3->_chrono, nullptr);
    animation_bg3->setTarget(sprite_bg3);
    animation_bg3->setTime({0, 5000});
    animation_bg3->_frameIndex = 0;
    animation_bg3->_numberFrameToAnim = 800;
    animation_bg3->_numberFrame = 1600;
    animation_bg3->_startFrameIndex = 0;
    animation_bg3->_frameForOnePicture = 800;
    bg3->setAttribute("sprite bg3");
    bg3->addComponent(sprite_bg3);
    bg3->addComponent(animation_bg3);

    std::shared_ptr<IEntity> bg4 = std::make_shared<IEntity>();
    std::shared_ptr<Drawable> sprite_bg4 = std::make_shared<Drawable>();
    std::shared_ptr<Animatable> animation_bg4 = std::make_shared<Animatable>();
    sprite_bg4->setRect({0, 0, 800, 600});
    sprite_bg4->setSize({1600, 600});
    sprite_bg4->setScale(1);
    sprite_bg4->setPosition({0, 0});
    sprite_bg4->setAttribute("sprite bg4");
    sprite_bg4->_textureId = BACKGROUND1;
    gettimeofday(&animation_bg4->_chrono, nullptr);
    animation_bg4->setTarget(sprite_bg4);
    animation_bg4->setTime({0, 50000});
    animation_bg4->_frameIndex = 0;
    animation_bg4->_numberFrameToAnim = 800;
    animation_bg4->_numberFrame = 1600;
    animation_bg4->_startFrameIndex = 0;
    animation_bg4->_frameForOnePicture = 800;
    bg4->setAttribute("sprite bg4");
    bg4->addComponent(sprite_bg4);
    bg4->addComponent(animation_bg4);

    addEntity(bg1);
    addEntity(bg2);
    addEntity(bg3);
    addEntity(bg4);
    addEntity(floor_bg);
    addEntity(roof_bg);
    addEntity(enemy1);

    // std::shared_ptr<Drawable> sprite_bg2 = std::make_shared<Drawable>();
    // std::shared_ptr<Timer> timer_bg2 = std::make_shared<Timer>();
    // sprite_bg2->setAttribute("sprite bg2");

    // std::shared_ptr<Drawable> sprite_bg3 = std::make_shared<Drawable>();
    // std::shared_ptr<Timer> timer_bg3 = std::make_shared<Timer>();
    // sprite_bg3->setAttribute("sprite bg3");

    // std::shared_ptr<Drawable> sprite_bg4 = std::make_shared<Drawable>();
    // std::shared_ptr<Timer> timer_bg4 = std::make_shared<Timer>();
    // sprite_bg4->setAttribute("sprite bg4");

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
    std::shared_ptr<Collision> collision = std::make_shared<Collision>(_serverSocket);
    std::shared_ptr<Move> move = std::make_shared<Move>(_serverSocket);

    addService(graphic);
    addService(collision);
    addService(move);
    addService(animation);
    addService(timeManagement);

}

void LobbyScene::update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet)
{
    timeval now{};
    timeval diff{};
    gettimeofday(&now, nullptr);
    timersub(&now, &_chrono, &diff);

    if (event->key != sf::Keyboard::Key::Unknown)
        _lastEvent = event;

    if (diff.tv_usec >= 5000) {
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

    checkBulletDeletion();

    if (packet != nullptr) {
        int id = event->id;
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
                drawable->setRect({101, 0, 33, 17});
                drawable->setScale(2);
                drawable->setSize({532 * drawable->getScale(), 372 * drawable->getScale()});
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

    if (event->key == sf::Keyboard::Key::Space) {
        timeval nowbullet{};
        timeval diffbullet{};
        gettimeofday(&nowbullet, nullptr);
        timersub(&nowbullet, &_bulletTriggerLimiter, &diffbullet);

        if (_bulletTriggerLimiter.tv_sec != 0 && _bulletTriggerLimiter.tv_usec != 0)
            if (diffbullet.tv_sec <= 0 && diffbullet.tv_usec < 500000)
                return;

        _bulletTriggerLimiter = {0, 0};

        gettimeofday(&_bulletTriggerLimiter, nullptr);

        std::shared_ptr<IEntity> bullet = std::make_shared<IEntity>();
        std::shared_ptr<Drawable> bullet_sprite = std::make_shared<Drawable>();
        std::shared_ptr<Timer> timer = std::make_shared<Timer>();

        std::shared_ptr<IEntity> player = nullptr;

        for (const auto& entity : getEntities())
            for (const auto& component : entity->getComponents()) {
                if (component->getAttribute() == "player " + std::to_string(event->id)) {
                    player = entity;
                    break;
                }
            }

        if (player != nullptr) {

            auto draw = std::dynamic_pointer_cast<Drawable>(player->getComponents()[0]);

            if (draw != nullptr) {
                auto [x, y] = draw->getPosition();

                bullet_sprite->setPosition({x, y});
                bullet_sprite->setAttribute("bullet" + std::to_string(_nbBullets));
                _nbBullets++;
                bullet_sprite->_textureId = BULLET;
                bullet_sprite->setRect({233, 120, 32, 12});
                bullet_sprite->setScale(3);
                bullet_sprite->setSize({532 * bullet_sprite->getScale(), 372 * bullet_sprite->getScale()});
                bullet->addComponent(bullet_sprite);
                bullet->setAttribute("bullet" + std::to_string(_nbBullets));
                timer->_targetTime.tv_sec = 0;
                timer->_targetTime.tv_usec = 25000;
                timer->setTarget(bullet_sprite);
                timer->setActive(true);
                bullet->addComponent(timer);
                addEntity(bullet);

                std::shared_ptr<Packet> sendpacket = std::make_shared<Packet>();
                sendpacket->code = NEW_COMPONENT;
                sendpacket->data_size = sizeof(NewComponent);
                sendpacket->data = malloc(sendpacket->data_size);
                NewComponent newComponent{};
                newComponent.type = ComponentTypeSocket::SPRITESOCKET;
                newComponent.id = BULLET;
                std::memcpy(&newComponent.attribute, bullet->getAttribute().c_str(), 16);
                memcpy(sendpacket->data, &newComponent, sendpacket->data_size);
                _serverSocket->broadcast(sendpacket.get());
                free(sendpacket->data);

                broadcastGameState();
            }
        }
    }

}

void LobbyScene::checkBulletDeletion()
{
    for (auto &entity : getEntities()) {
        for (auto &component : entity->getComponents()) {
            //std::cout << "component: " << component->getAttribute() << std::endl;
            if (std::string(component->getAttribute()).find("bullet") != std::string::npos) {
                //std::cout << "bullet x position: " << std::get<0>(std::dynamic_pointer_cast<Drawable>(component)->getPosition()) << " y position: " << std::get<1>(std::dynamic_pointer_cast<Drawable>(component)->getPosition()) << std::endl;
                auto draw = std::dynamic_pointer_cast<Drawable>(component);
                auto [x, y] = draw->getPosition();
                if (x > 900) {
                    std::cout << "delete " << component->getAttribute() << std::endl;
                    _entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
                    _nbBullets--;
                    std::shared_ptr<Packet> sendpacket = std::make_shared<Packet>();
                    sendpacket->code = DELETE_COMPONENT;
                    sendpacket->data_size = std::string(component->getAttribute()).size();
                    sendpacket->data = malloc(sendpacket->data_size);
                    std::memcpy(sendpacket->data, component->getAttribute(), sendpacket->data_size);
                    _serverSocket->broadcast(sendpacket.get());
                    free(sendpacket->data);
                }
            }
        }
    }
}
