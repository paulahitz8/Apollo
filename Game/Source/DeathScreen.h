#ifndef __DEATH_SCREEN_H__
#define __DEATH_SCREEN_H__

#include "Module.h"

struct SDL_Texture;
class Font;

class DeathScreen : public Module
{
public:

	DeathScreen();
	virtual ~DeathScreen();

	void Init();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

private:

	SDL_Texture* deathScreen;
	SDL_Rect rect;
	Font* font;
};

#endif // __DEATH_SCREEN_H__