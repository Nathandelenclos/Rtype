//
// Created by nathan on 1/10/24.
//

#pragma once

#include "AService.hpp"
#include "Drawable.hpp"
#include <utility>
#include <vector>

class Collision : public AService
{
  public:

    /**
     * @brief Construct a new Collision:: Collision object
     * @param serverSocket
     */
    explicit Collision(std::shared_ptr<ServerSocket> serverSocket) :
        AService(std::move(serverSocket)){};

    /**
     * @brief update, update the collision
     *
     * @param event
     * @param component
     */
    void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) override;

    /**
     * @brief checkCollision, check the collision
     *
     * @param drawable
     * @param other
     * @return bool (true or false) if there is a collision
     */
    static bool checkCollision(const std::shared_ptr<Drawable> &drawable, const std::shared_ptr<Drawable> &other);

    /**
     * @brief cancelMove, cancel the move
     *
     * @param event
     * @param drawable
     */
    static void cancelMove(const std::shared_ptr<Event> &event, const std::shared_ptr<Drawable> &drawable);
    int _score = 0;
};
