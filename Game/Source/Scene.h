#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

struct SDL_Texture;

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
	fPoint homePos;
	Collider* homeCol;

	// HomeMoon planet
	Planet* moon;
	fPoint moonPos;
	Collider* moonCol;

	// Blue planet
	Planet* blue;
	fPoint bluePos;
	Collider* blueCol;

	// GasBoy planet
	Planet* gasBoy;
	fPoint gasBoyPos;
	Collider* gasBoyCol;

	// Giant planet
	Planet* giant;
	fPoint giantPos;
	Collider* giantCol;

	// AquaBoy planet
	Planet* aquaBoy;
	fPoint aquaBoyPos;
	Collider* aquaBoyCol;

	// newMoon planet
	Planet* newMoon;
	fPoint newMoonPos;
	Collider* newMoonCol;

	// newHome planet
	Planet* newHome;
	fPoint newHomePos;
	Collider* newHomeCol;


private:

	SDL_Texture* background;
	SDL_Texture* debugPath;

	bool boolPath = false;
};

#endif // __SCENE_H__