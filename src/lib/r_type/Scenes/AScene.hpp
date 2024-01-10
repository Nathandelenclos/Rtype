//
// Created by talleux on 1/4/24.
//

#pragma once

#include "IScene.hpp"
#include "../components/IComponent.hpp"
#include "../components/Drawable.hpp"

class AScene : public ISceneRType {
    public:
        explicit AScene(std::shared_ptr<ServerSocket> serverSocket);
        ~AScene() override = default;

        void addEntity(std::shared_ptr<IEntity> entity) override;
        std::vector<std::shared_ptr<IEntity>> getEntities() override;

        void addService(std::shared_ptr<IService> service) override;
        std::vector<std::shared_ptr<IService>> getServices() override;

        void display() override;

        void pauseScene() override;
        void resumeScene() override;
        void stopScene() override;
        void restartScene() override;

        void sendGameState(int clientID) override;
        void broadcastGameState() override;

    protected:
};
