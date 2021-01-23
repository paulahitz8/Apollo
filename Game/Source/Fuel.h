#ifndef __FUEL_H__
#define __FUEL_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;

class Fuel : public Module
{
public:

	Fuel();

	void Init();

	virtual ~Fuel();

	bool Awake(pugi::xml_node& conf);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	SDL_Texture* fuelTexture;
	SDL_Texture* bottleTexture;

	SDL_Rect bottle_0;
	SDL_Rect bottle_25;
	SDL_Rect bottle_50;
	SDL_Rect bottle_75;
	SDL_Rect bottle_100;

	int fuel;

	bool isPicked;

	iPoint bottlePos;

	iPoint fuel1Pos;

private:

	Animation* currentAnimation = &fuelAnim;
	Animation fuelAnim;

	CircleCollider* fuel1Collider = nullptr;
};

#endif // __FUEL_H__