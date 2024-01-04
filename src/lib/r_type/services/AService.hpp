//
// Created by talleux on 1/4/24.
//

#pragma once

#include "IService.hpp"
#include "IComponent.hpp"

class AService : public IService {
    public:
        explicit AService(std::shared_ptr<ServerSocket> serverSocket);
        ~AService() override = default;

        virtual void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) = 0;

};
