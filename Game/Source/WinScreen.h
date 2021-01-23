#ifndef __WIN_SCREEN_H__
#define __WIN_SCREEN_H__

#include "Module.h"

struct SDL_Texture;
struct SDL_Rect;

class WinScreen : public Module
{
public:

	WinScreen();
	virtual ~WinScreen();

	void Init();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

private:

	SDL_Texture* winScreen;
	SDL_Rect rect;
};

#endif // __WIN_SCREEN_H__