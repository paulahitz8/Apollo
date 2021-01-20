#include "Asteroid.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Collisions.h"
#include "FadeScreen.h"
#include "Point.h"
#include "Player.h"

Asteroid::Asteroid()
{
	name.Create("asteroid");
}

Asteroid::~Asteroid() {}

bool Asteroid::Awake(pugi::xml_node&)
{
	//animations

	return true;
}


bool Asteroid::Start()
{
	LOG("Loading player textures");

	
	return true;
}

bool Asteroid::PreUpdate()
{
	return true;
}

bool Asteroid::Update(float dt)
{

	return true;
}

bool Asteroid::PostUpdate()
{
	return true;
}

bool Asteroid::CleanUp()
{
	//Unload the textures

	return true;
}
