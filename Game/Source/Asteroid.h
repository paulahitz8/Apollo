#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;

class Asteroid : public Module
{
public:

	Asteroid();

	void Init();

	virtual ~Asteroid();

	bool Awake(pugi::xml_node& conf);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	bool as1Boom;
	bool as2Boom;
	bool as3Boom;
	bool as4Boom;

private:

	fPoint asteroid1Pos;
	fPoint asteroid2Pos;
	fPoint asteroid3Pos;
	fPoint asteroid4Pos;
	CircleCollider* asteroid1Col;
	CircleCollider* asteroid2Col;
	CircleCollider* asteroid3Col;
	CircleCollider* asteroid4Col;
	SDL_Texture* asteroidTexture;
	SDL_Rect asteroid1Rect;
	SDL_Rect asteroid2Rect;
	SDL_Rect asteroid3Rect;
	SDL_Rect asteroid4Rect;
	float asteroidRotation;
	float asteroidTurnAngle;
	bool direction1;
	bool direction2;
	bool direction3;
	bool direction4;
};

#endif // __ASTEROID_H__