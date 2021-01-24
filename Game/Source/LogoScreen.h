#ifndef __LOGO_SCREEN_H__
#define __LOGO_SCREEN_H__

#include "Module.h"

struct SDL_Texture;
struct SDL_Rect;

class LogoScreen : public Module
{
public:

	LogoScreen();
	virtual ~LogoScreen();

	void Init();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

private:

	SDL_Texture* logoScreen;
	SDL_Rect rect;
	int timer = 0;
	unsigned int logoMusicFx;
};

#endif // __LOGO_SCREEN_H__