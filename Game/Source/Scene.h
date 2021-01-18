#ifndef SCENE_H
#define SCENE_H

#include "Module.h"

struct SDL_Texture;

class Planet;
class CircleCollider;

class Scene : public Module
{
public:

    Scene();

    // Destructor
    virtual ~Scene();

    void Init();

    // Called before render is available
    bool Awake();

    // Called before the first frame
    bool Start();

    // Called before all Updates
    bool PreUpdate();

    // Called each loop iteration
    bool Update(float dt);

    // Called before all Updates
    bool PostUpdate();

    // Called before quitting
    bool CleanUp();

    // Home planet
    Planet* planetHome;
    iPoint homePos;
    CircleCollider* homeCol;

    // HomeMoon planet
    Planet* moon;
    iPoint moonPos;
    CircleCollider* moonCol;

    // Blue planet
    Planet* blue;
    iPoint bluePos;
    CircleCollider* blueCol;

    // GasBoy planet
    Planet* gasBoy;
    iPoint gasBoyPos;
    CircleCollider* gasBoyCol;

    // Giant planet
    Planet* giant;
    iPoint giantPos;
    CircleCollider* giantCol;

    // AquaBoy planet
    Planet* aquaBoy;
    iPoint aquaBoyPos;
    CircleCollider* aquaBoyCol;

    // newMoon planet
    Planet* newMoon;
    iPoint newMoonPos;
    CircleCollider* newMoonCol;

    // newHome planet
    Planet* newHome;
    iPoint newHomePos;
    CircleCollider* newHomeCol;


private:

    SDL_Texture* background;
    SDL_Texture* debugPath;

    bool boolPath = false;
};

#endif // SCENE_H