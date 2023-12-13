#include <iostream>
#include <utility>
#include <vector>

enum class ComponentType {
    DRAW,
    NAME,
    PHYSICS,
    INPUT,
    NULL_COMPONENT,
};

class IComponent {
public:
    virtual ~IComponent() = default;
    virtual ComponentType getType() = 0;
};

class AComponent : public IComponent {
public:
    ComponentType getType() override {
        return type;
    };

protected:
    ComponentType type = ComponentType::NULL_COMPONENT;
};

class IEntity {
public:
    virtual ~IEntity() = default;
    virtual std::vector<IComponent*> getComponents() = 0;
    virtual void addComponent(IComponent* component) = 0;

};

class ISystem {
public:
    virtual ~ISystem() = default;
    virtual void exec(IComponent* component) = 0;
    virtual ComponentType getType() = 0;

};

class DrawComponent : public AComponent {
public:
    DrawComponent() {
        type = ComponentType::DRAW;
    }
    int x = 0;
};

class NameComponent : public AComponent {
public:
    NameComponent(std::string name) {
        type = ComponentType::DRAW;
        this->name = name;
    }
    std::string name;
};


class SystemManager {
    public:

    SystemManager() {
    }

    void exec(std::vector<IEntity*> entities) {
        for (auto entity : entities) {
            for (auto component : entity->getComponents()) {
                for (auto system : systems) {
                    if (component->getType() == system->getType()) {
                        system->exec(component);
                    }
                }
            }
        }
    }

    std::vector<ISystem*> systems;
};

class DrawSystem : public ISystem {
public:
    ComponentType getType() override {
        return ComponentType::DRAW;
    }

    void exec(IComponent* component) override {
        draw((DrawComponent*)component);
    }

    void draw(DrawComponent* component) {
        std::cout << "DrawSystem::draw("<< component->x <<")" << std::endl;
    }
};

class NameSystem : public ISystem {
public:
    ComponentType getType() override {
        return ComponentType::NAME;
    }

    void exec(IComponent* component) override {
        draw((NameComponent*)component);
    }

    void draw(NameComponent* component) {
        std::cout << "NameSystem::draw("<< component->name <<")" << std::endl;
    }
};

class Player : public IEntity {
public:
    explicit Player() {
        components.push_back(new DrawComponent());
    }
    std::vector<IComponent*> getComponents() override {
        return components;
    }
    void addComponent(IComponent* component) override {
        components.push_back(component);
    }
    std::vector<IComponent*> components;
};

class Entity : public IEntity {
public:
    explicit Entity() {
    }
    std::vector<IComponent*> getComponents() override {
    }
    void addComponent(IComponent* component) override {
        components.push_back(component);
    }
    std::vector<IComponent*> components;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<IComponent*> components = {new DrawComponent()};
    std::vector<IEntity*> entities;

    Entity player;
    player.addComponent(new NameComponent("player"));

    Entity ennemy;
    ennemy.addComponent(new NameComponent("enemy"));

    Player player2;
    entities.push_back(&player2);
    player2.addComponent(new NameComponent("player2"));

    entities.push_back(&player);
    entities.push_back(&ennemy);

    SystemManager systemManager;
    systemManager.systems.push_back(new DrawSystem());
    systemManager.systems.push_back(new NameSystem());
    systemManager.exec(entities);
    return 0;
}
