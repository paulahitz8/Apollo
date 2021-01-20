#ifndef __HEARTS_H__
#define __HEARTS_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;

class Hearts : public Module
{
public:

	Hearts();

	void Init();

	virtual ~Hearts();

	bool Awake(pugi::xml_node& conf);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	SDL_Texture* heartTexture;

	iPoint heart1Pos;
	iPoint heart2Pos;
	iPoint heart3Pos;

	bool isPicked = false;

private:

	Animation* currentAnimation1 = &redHeart;
	Animation* currentAnimation2 = &redHeart;
	Animation* currentAnimation3 = &redHeart;
	Animation redHeart;
	Animation grayHeart;

	unsigned int loseHeart;
};

#endif // __HEARTS_H__