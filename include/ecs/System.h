#pragma once
#include <ecs/Entity.h>


// System class
class System
{
public:
    System(int componentTypes...)
    {
        AddItems(m_components, componentTypes);
    }

    virtual ~System() {}

    // Add entity to the system
    bool Add(Entity* entity);
    // Remove entity from the system
    bool Remove(Entity* entity);
    // Check if entity is in the system
    bool Has(Entity* entity)
    {
        return HasValue(m_entities, entity);
    }

    virtual void Update(float dt) {}
    virtual void Draw() {}


private:
    // List of components that this system is tied to
    std::vector<int> m_components;

    // List of entities that this system processes
    std::vector<Entity*> m_entities;

};
