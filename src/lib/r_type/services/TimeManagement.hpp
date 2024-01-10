//
// Created by talleux on 1/10/24.
//

#pragma once

#include <utility>
#include <vector>
#include "AService.hpp"
#include "IComponent.hpp"

class TimeManagement : public AService {
    public:
        explicit TimeManagement(std::shared_ptr<ServerSocket> serverSocket) : AService(std::move(serverSocket)) {};

        void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) override;

};

