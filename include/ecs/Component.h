#pragma once


// Component base class
class Component
{
public:
    virtual ~Component() {}
    virtual int GetId() = 0;
};


// A more helpful base class for creating
// new component classes, that automatically
// creates helpful functions
template <typename T>
class ComponentBase : public Component
{
public:
    virtual int GetId() { return typeid(T).hash_code(); }
    static int GetStaticId() { return typeid(T).hash_code(); }
};
