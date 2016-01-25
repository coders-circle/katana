#include <stdinc.h>
#include <ecs/System.h>


bool System::Add(Entity* entity)
{
    // Add only if the entity contains
    // all components that the system is tied to
    for (auto id: m_components)
        if (!entity->Has(id))
            return false;


    m_entities.push_back(entity);
    return true;
}


bool System::Remove(Entity* entity)
{
    // Return false when entity isn't contained in the system
    if (!Has(entity))
        return false;


    RemoveValue(m_entities, entity);
    return true;
}
