#pragma once
#include <ecs/Component.h>


// Entity class storing a list of components
class Entity
{
public:
    
    // Create and add a new component
    template<class T, class... Args>
    T* Add(Args... args)
    {
        T* component = new T(args...);
        m_components[T::GetStaticId()] = component;
        return component;
    }

    // Check if entity has a component
    bool Has(int id)
    {
        return m_components.find(id) != m_components.end();
    }

    // On destruction, destroy all components
    ~Entity()
    {
        for (auto it = m_components.begin();
            it != m_components.end(); ++it)
        {
            delete it->second;
        }
    }

private:
    // Components are mapped to their ids for fast access
    std::map<int, Component*> m_components;

};
