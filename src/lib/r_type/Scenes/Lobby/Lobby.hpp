//
// Created by talleux on 1/4/24.
//

#pragma once

#include "../AScene.hpp"
#include "../components/Drawable.hpp"
#include "../components/Timer.hpp"
#include "../components/Animatable.hpp"
#include <SFML/Window/Keyboard.hpp>


class LobbyScene : public AScene {
    public:
        explicit LobbyScene(std::shared_ptr<ServerSocket> serverSocket);
        ~LobbyScene() override = default;

        void initScene();

        void update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet) override;

        void checkBulletDeletion();
        void checkSpawnerActivation();
        bool allEnemiesLeftScreen();
        void enemyDeletion();

        void initEntities() override;
        void initServices() override;

    private:
        timeval _chrono;
        timeval _start;
        std::shared_ptr<Event> _lastEvent;
        timeval _bulletTriggerLimiter;
        int _nbBullets;

        std::tuple<int, int> _speedWave;
        std::tuple<int, int> _numberEntityWave = {2, 5};
        std::tuple<int, int> _timeBetweenWave;
        bool _spawnerActive = true;

};

class Enemy : public IEntity {
public:
    Enemy(std::tuple<int, int> speedMovement = {0, 100000},
        timeval speedAnimation = {0, 200000},
        Rect settingRect = {0, 0, 33, 36},
        Position settingSize = {263 * 2, 36 * 2},
        Position settingPosition = {1000, 50},
        int settingScale = 2,
        int frameIndex = 0,
        int numberFrameToAnim = 8,
        int numberFrame = 8,
        int startFrameIndex = 0,
        int frameForOnePicture = 1,
        Type type = ENEMY, 
        int direction = -1,
        bool isActive = true,
        std::string attributeDrawable = "sprite enemy1",
        std::string attributeEntity = "sprite enemy")
    {
        // Initialisation des composants pour l'ennemi
        timer = std::make_shared<Timer>();
        sprite = std::make_shared<Drawable>();
        animation = std::make_shared<Animatable>();

        // Initialisation du timer
        gettimeofday(&timer->_startTime, nullptr);
        timer->_targetTime.tv_sec = std::get<0>(speedMovement);
        timer->_targetTime.tv_usec = std::get<1>(speedMovement);
        timer->setTarget(sprite);
        timer->setActive(isActive);
        timer->setDirection(direction);

        // Initialisation de l'animation
        animation->setTarget(sprite);
        animation->setTime(speedAnimation);
        animation->_frameIndex = frameIndex;
        animation->_numberFrameToAnim = numberFrameToAnim;
        animation->_numberFrame = numberFrame;
        animation->_startFrameIndex = startFrameIndex;
        animation->_frameForOnePicture = frameForOnePicture;
        gettimeofday(&animation->_chrono, nullptr);

        // Initialisation du sprite
        sprite->setRect(settingRect);
        sprite->setSize(settingSize);
        sprite->setScale(settingScale);
        sprite->setPosition(settingPosition);
        sprite->setAttribute(attributeDrawable);
        sprite->_textureId = type;

        // Ajout des composants à l'ennemi
        addComponent(sprite);
        addComponent(timer);
        addComponent(animation);
        setAttribute(attributeEntity);
    }

    std::shared_ptr<Timer> timer;
    std::shared_ptr<Drawable> sprite;
    std::shared_ptr<Animatable> animation;
private:
};
