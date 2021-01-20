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


private:

};

#endif // __ASTEROID_H__