//
// Created by talleux on 1/4/24.
//

#pragma once

class IComponentRType {
    public:
        virtual ~IComponentRType() = default;

        virtual std::string getAttribute() const = 0;
        virtual void setAttribute(std::string attribute) = 0;

    protected:
        std::string _attribute;
};
