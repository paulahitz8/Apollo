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

	asteroidTexture = app->tex->Load("Assets/Textures/Asteroids.png");
	asteroidTurnAngle = 4.0f;

	asteroid1Pos = { 1700.0f, 350.0f };
	asteroid1Col = app->collisions->AddCollider(asteroid1Pos.x + 33, asteroid1Pos.y + 33, 33, CircleCollider::Type::ASTEROID, this);
	asteroid1Rect = { 39, 25, 90, 88 };
	direction1 = true;
	as1Boom = false;

	asteroid2Pos = { 1800.0f, 350.0f };
	asteroid2Col = app->collisions->AddCollider(asteroid2Pos.x + 25, asteroid2Pos.y + 25, 25, CircleCollider::Type::ASTEROID, this);
	asteroid2Rect = { 278, 140, 53, 58 };
	direction2 = false;
	as2Boom = false;

	asteroid3Pos = { 6300.0f, 350.0f };
	asteroid3Col = app->collisions->AddCollider(asteroid3Pos.x + 33, asteroid3Pos.y + 33, 33, CircleCollider::Type::ASTEROID, this);
	asteroid3Rect = { 255, 27, 76, 69 };
	direction3 = true;
	as3Boom = false;

	asteroid4Pos = { 6400.0f, 350.0f };
	asteroid4Col = app->collisions->AddCollider(asteroid4Pos.x + 33, asteroid4Pos.y + 33, 33, CircleCollider::Type::ASTEROID, this);
	asteroid4Rect = { 458, 21, 80, 88 };
	direction4 = false;
	as4Boom = false;

	asteroid5Pos = { 1600.0f, 30.0f };
	asteroid5Col = app->collisions->AddCollider(asteroid5Pos.x + 33, asteroid5Pos.y + 33, 33, CircleCollider::Type::ASTEROID, this);
	asteroid5Rect = { 355, 33, 78, 69 };
	direction5 = true;
	as5Boom = false;

	asteroid6Pos = { 6200.0f, 50.0f };
	asteroid6Col = app->collisions->AddCollider(asteroid6Pos.x + 25, asteroid6Pos.y + 25, 25, CircleCollider::Type::ASTEROID, this);
	asteroid6Rect = { 473, 149, 45, 38 };
	direction6 = false;
	as6Boom = false;

	return true;
}

bool Asteroid::PreUpdate()
{
	return true;
}

bool Asteroid::Update(float dt)
{
	asteroidRotation += asteroidTurnAngle;
	if (asteroidRotation > 360)
	{
		asteroidRotation = asteroidRotation / 360;
	}

	if (asteroid1Pos.y > 630)
	{
		direction1 = false;
	}
	else if (asteroid1Pos.y < 10)
	{
		direction1 = true;
	}

	if (asteroid2Pos.y > 630)
	{
		direction2 = false;
	}
	else if (asteroid2Pos.y < 10)
	{
		direction2 = true;
	}

	if (asteroid3Pos.y > 630)
	{
		direction3 = false;
	}
	else if (asteroid3Pos.y < 10)
	{
		direction3 = true;
	}

	if (asteroid4Pos.y > 630)
	{
		direction4 = false;
	}
	else if (asteroid4Pos.y < 10)
	{
		direction4 = true;
	}

	if (asteroid5Pos.y > 630)
	{
		direction5 = false;
	}
	else if (asteroid5Pos.y < 10)
	{
		direction5 = true;
	}

	if (asteroid6Pos.y > 630)
	{
		direction6 = false;
	}
	else if (asteroid6Pos.y < 10)
	{
		direction6 = true;
	}

	if (direction1)
	{
		asteroid1Pos.y++;
	}
	else
	{
		asteroid1Pos.y--;
	}

	if (direction2)
	{
		asteroid2Pos.y++;
	}
	else
	{
		asteroid2Pos.y--;
	}

	if (direction3)
	{
		asteroid3Pos.y++;
	}
	else
	{
		asteroid3Pos.y--;
	}

	if (direction4)
	{
		asteroid4Pos.y++;
	}
	else
	{
		asteroid4Pos.y--;
	}

	if (direction5)
	{
		asteroid5Pos.y++;
	}
	else
	{
		asteroid5Pos.y--;
	}

	if (direction6)
	{
		asteroid6Pos.y++;
	}
	else
	{
		asteroid6Pos.y--;
	}

	asteroid1Col->SetPos(asteroid1Pos.x + 33, asteroid1Pos.y + 33);
	asteroid2Col->SetPos(asteroid2Pos.x + 25, asteroid2Pos.y + 25);
	asteroid3Col->SetPos(asteroid3Pos.x + 33, asteroid3Pos.y + 33);
	asteroid4Col->SetPos(asteroid4Pos.x + 33, asteroid4Pos.y + 33);
	asteroid5Col->SetPos(asteroid5Pos.x + 33, asteroid5Pos.y + 33);
	asteroid6Col->SetPos(asteroid6Pos.x + 25, asteroid6Pos.y + 25);

	if (!as1Boom)
	{
		app->render->DrawTexture(asteroidTexture, asteroid1Pos.x, asteroid1Pos.y, &asteroid1Rect, 1.0f, asteroidRotation);
	}

	if (!as2Boom)
	{
		app->render->DrawTexture(asteroidTexture, asteroid2Pos.x, asteroid2Pos.y, &asteroid2Rect, 1.0f, asteroidRotation);
	}

	if (!as3Boom)
	{
		app->render->DrawTexture(asteroidTexture, asteroid3Pos.x, asteroid3Pos.y, &asteroid3Rect, 1.0f, asteroidRotation);
	}

	if (!as4Boom)
	{
		app->render->DrawTexture(asteroidTexture, asteroid4Pos.x, asteroid4Pos.y, &asteroid4Rect, 1.0f, asteroidRotation);
	}

	if (!as5Boom)
	{
		app->render->DrawTexture(asteroidTexture, asteroid5Pos.x, asteroid5Pos.y, &asteroid5Rect, 1.0f, asteroidRotation);
	}

	if (!as6Boom)
	{
		app->render->DrawTexture(asteroidTexture, asteroid6Pos.x, asteroid6Pos.y, &asteroid6Rect, 1.0f, asteroidRotation);
	}

	return true;
}

bool Asteroid::PostUpdate()
{
	return true;
}

bool Asteroid::CleanUp()
{
	//Unload the textures
	app->tex->UnLoad(asteroidTexture);

	return true;
}
