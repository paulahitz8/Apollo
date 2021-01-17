#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

struct SDL_Texture;

class Planet;

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
	Collider* homeCol;

	// HomeMoon planet
	Planet* moon;
	iPoint moonPos;
	Collider* moonCol;

	// Blue planet
	Planet* blue;
	iPoint bluePos;
	Collider* blueCol;

	// GasBoy planet
	Planet* gasBoy;
	iPoint gasBoyPos;
	Collider* gasBoyCol;

	// Giant planet
	Planet* giant;
	iPoint giantPos;
	Collider* giantCol;

	// AquaBoy planet
	Planet* aquaBoy;
	iPoint aquaBoyPos;
	Collider* aquaBoyCol;

	// newMoon planet
	Planet* newMoon;
	iPoint newMoonPos;
	Collider* newMoonCol;

	// newHome planet
	Planet* newHome;
	iPoint newHomePos;
	Collider* newHomeCol;


private:

	SDL_Texture* background;
	SDL_Texture* debugPath;

	bool boolPath = false;
};

#endif // __SCENE_H__