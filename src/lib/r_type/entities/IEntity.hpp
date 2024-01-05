//
// Created by talleux on 1/4/24.
//

#pragma once

#include <memory>
#include <vector>
#include "../components/IComponent.hpp"

class IEntity {
    public:
        IEntity() { setAttribute(""); }
        ~IEntity() = default;

        [[nodiscard]] std::vector<std::shared_ptr<IComponentRType>> getComponents() const { return _components; }

        void addComponent(const std::shared_ptr<IComponentRType>& component) { _components.push_back(component); }

        [[nodiscard]] std::string getAttribute() const { return _attribute; }
        void setAttribute(const std::string& attribute) { _attribute = attribute; }

    protected:
        std::vector<std::shared_ptr<IComponentRType>> _components;
        std::string _attribute;
};
