#ifndef MODULE_H
#define MODULE_H

#include "SString.h"

#include "PugiXml/src/pugixml.hpp"

class App;
struct CircleCollider;

class Module
{
public:

    Module() : active(false)
    {}

    void Init()
    {
        active = true;
    }

    // Called before render is available
    virtual bool Awake(pugi::xml_node&)
    {
        return true;
    }

    // Called before the first frame
    virtual bool Start()
    {
        return true;
    }

    // Called each loop iteration
    virtual bool PreUpdate()
    {
        return true;
    }

    // Called each loop iteration
    virtual bool Update(float dt)
    {
        return true;
    }

    // Called each loop iteration
    virtual bool PostUpdate()
    {
        return true;
    }

    // Called before quitting
    virtual bool CleanUp()
    {
        return true;
    }

    virtual bool LoadState(pugi::xml_node&)
    {
        return true;
    }

    virtual bool SaveState(pugi::xml_node&)
    {
        return true;
    }

    void Module::Enable()
    {
        if (!active)
        {
            active = true;
            Start();
        }
    }

    void Module::Disable()
    {
        if (active)
        {
            active = false;
            CleanUp();
        }

    }

    virtual void OnCollision(CircleCollider* c1, CircleCollider* c2) {};

public:

    SString name;
    bool active;

};

#endif // MODULE_H