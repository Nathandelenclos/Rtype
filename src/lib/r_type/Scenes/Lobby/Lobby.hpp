/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "../AScene.hpp"
#include "../components/Animatable.hpp"
#include "../components/Drawable.hpp"
#include "../components/Timer.hpp"
#include <SFML/Window/Keyboard.hpp>

class LobbyScene : public AScene
{
  public:

    /**
     * @brief Construct a new LobbyScene object
     * @param serverSocket
     */
    explicit LobbyScene(std::shared_ptr<ServerSocket> serverSocket);

    /**
     * @brief Destroy the LobbyScene object
     */
    ~LobbyScene() override = default;


    /**
     * @brief initScene, init the scene
     */
    void initScene();


    /**
     * @brief display, display the scene
     *
     * @param event
     * @param window
     */
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
