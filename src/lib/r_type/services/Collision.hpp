//
// Created by nathan on 1/10/24.
//

#pragma once

#include "AService.hpp"
#include "Drawable.hpp"
#include <utility>
#include <vector>

class Collision : public AService {
public:
    explicit Collision(std::shared_ptr<ServerSocket> serverSocket) : AService(std::move(serverSocket)) {};
    void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) override;
    static bool checkCollision(const std::shared_ptr<Drawable>& drawable, const std::shared_ptr<Drawable>& other);
    static void cancelMove(const std::shared_ptr<Event>& event, const std::shared_ptr<Drawable>& drawable);
};
