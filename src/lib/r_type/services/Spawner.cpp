/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Spawner.cpp
*/

#include "Spawnable.hpp"
#include "Spawner.hpp"
#include "Lobby.hpp"

void Spawner::update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component)
{
    timeval randomtime;
    auto spawnable = std::dynamic_pointer_cast<Spawnable>(component);
    if (spawnable && spawnable) {
        gettimeofday(&spawnable->_now, NULL);
        timersub(&spawnable->_now, &spawnable->_chrono, &spawnable->_diff);
        int time1 = std::get<0>(spawnable->getTimeBetweenWave());
        int time2 = std::get<1>(spawnable->getTimeBetweenWave());
        randomtime = {rand() % time1 + time2, 0};
        if (spawnable->_diff.tv_sec >= randomtime.tv_sec && spawnable->_diff.tv_usec >= randomtime.tv_usec) {
            int nbEntityToSpawn = rand() % std::get<0>(spawnable->_numberEntityWave) + std::get<1>(spawnable->_numberEntityWave);
            // auto spriteSpawn = spawnable->getTarget();
            for (int i = 0; i < nbEntityToSpawn; ++i) {
                // Créez une nouvelle entité ici
                std::shared_ptr<IEntity> enemy1 = std::make_shared<Enemy>();

                // Ajoutez la nouvelle entité à votre système de gestion des entités (ou faites ce qui est nécessaire)
                addEntity(newEntity);
            }
            
            spawnable->_chrono = spawnable->_now;
        }
    }
}
