#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;
class Font;

class Battery : public Module
{
public:

	Battery();

	void Init();

	virtual ~Battery();
	
	bool Awake(pugi::xml_node& conf);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	SDL_Texture* batteryTexture;

	SDL_Rect battery_100;
	SDL_Rect battery_75;
	SDL_Rect battery_50;
	SDL_Rect battery_25;
	SDL_Rect battery_0;

	int battery;

	iPoint batteryPos;

private:

	int timer;
	Font* font;

};

#endif // __BATTERY_H__