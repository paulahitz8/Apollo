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

	List<Planet*> planetList;

    // Home planet
    Planet* planetHome;
    fPoint homePos;
    CircleCollider* homeCol;

    // HomeMoon planet
    Planet* moon;
    fPoint moonPos;
    CircleCollider* moonCol;

    // Blue planet
    Planet* blue;
    fPoint bluePos;
    CircleCollider* blueCol;

    // GasBoy planet
    Planet* gasBoy;
    fPoint gasBoyPos;
    CircleCollider* gasBoyCol;

    // Giant planet
    Planet* giant;
    fPoint giantPos;
    CircleCollider* giantCol;

    // AquaBoy planet
    Planet* aquaBoy;
    fPoint aquaBoyPos;
    CircleCollider* aquaBoyCol;

    // newMoon planet
    Planet* newMoon;
    fPoint newMoonPos;
    CircleCollider* newMoonCol;

    // newHome planet
    Planet* newHome;
    fPoint newHomePos;
    CircleCollider* newHomeCol;


private:

    SDL_Texture* background;
    SDL_Texture* debugPath;

    bool boolPath = false;
};

#endif // SCENE_H