//
// Created by talleux on 1/4/24.
//

#pragma once

#include "../AScene.hpp"
#include "../components/Animatable.hpp"
#include "../components/Drawable.hpp"
#include "../components/Timer.hpp"
#include <SFML/Window/Keyboard.hpp>

class LobbyScene : public AScene
{
  public:
    explicit LobbyScene(std::shared_ptr<ServerSocket> serverSocket);
    ~LobbyScene() override = default;

    void initScene();

    void update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet) override;
        void checkBulletDeletion();
        void checkSpawnerActivation();
        bool allEnemiesLeftScreen();
        bool allBulletsLeftScreen();
        void spawnBoss();
        void shootBoss(int nb);
        void enemyDeletion();
        void bulletDeletion();

        void initEntities() override;
        void initServices() override;

    private:
        timeval _chrono;
        timeval _start;
        std::shared_ptr<Event> _lastEvent;
        timeval _bulletTriggerLimiter;
        int _nbBullets;
        int _nbBossBullets;
        int _lifeBoss;

        std::tuple<int, int> _speedWave;
        std::tuple<int, int> _numberEntityWave = {2, 5};
        std::tuple<int, int> _timeBetweenWave;
        bool _spawnerActive = true;
        bool _bossActive = false;
        int _timing = 0;

};
