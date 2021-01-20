#ifndef __ITEM_H__
#define __ITEM_H__

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
	int timer;

	iPoint bottlePos;

	iPoint fuelPos;

private:

	Animation* currentAnimation = &fuelAnim;
	Animation fuelAnim;
};

#endif // __ITEM_H__