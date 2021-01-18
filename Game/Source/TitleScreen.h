#ifndef __TITLE_SCREEN_H__
#define __TITLE_SCREEN_H__

#include "Module.h"

struct SDL_Texture;

class TitleScreen : public Module
{
public:

	TitleScreen();
	virtual ~TitleScreen();

	void Init();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

private:

	SDL_Texture* titleScreen;
	SDL_Rect rect;
};

#endif // __TITLE_SCREEN_H__