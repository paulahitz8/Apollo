#include "Fuel.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "FadeScreen.h"
#include "Point.h"
#include "Player.h"

Fuel::Fuel()
{
	name.Create("fuel");
}

Fuel::~Fuel() {}

bool Fuel::Awake(pugi::xml_node&)
{
	// Animation fuelAnim;
	fuelAnim.PushBack({ 29, 67, 101, 96 });
	fuelAnim.PushBack({ 168, 66, 101, 96 });
	fuelAnim.PushBack({ 308, 64, 101, 96 });
	fuelAnim.PushBack({ 168, 66, 101, 96 });
	fuelAnim.speed = 4.0f;

	return true;
}


bool Fuel::Start()
{
	LOG("Loading player textures");
	fuelTexture = app->tex->Load("Assets/Textures/Fuel.png");
	bottleTexture = app->tex->Load("Assets/Textures/Fuel_Bottle.png");

	currentAnimation = &fuelAnim;

	fuel1Pos = { 700, 500 };
	bottlePos = { 25, 15 };

	bottle_0 = { 31, 13, 77, 163 };
	bottle_25 = { 191, 19, 77, 163 };
	bottle_50 = { 364, 19, 77, 163 };
	bottle_75 = { 550, 14, 77, 163 };
	bottle_100 = { 727, 19, 77, 163 };

	fuel = 100;
	timer = 0;
	isPicked = false;

	fuel1Collider = app->collisions->AddCollider(fuel1Pos.x, fuel1Pos.y, 26, CircleCollider::Type::FUEL, this);

	return true;
}

bool Fuel::PreUpdate()
{
	return true;
}

bool Fuel::Update(float dt)
{
	if (fuel <= 10)
	{
		app->render->DrawTexture(bottleTexture, bottlePos.x - app->render->camera.x, bottlePos.y, &bottle_0);
	}

	else if (fuel > 10 && fuel <= 30)
	{
		app->render->DrawTexture(bottleTexture, bottlePos.x - app->render->camera.x, bottlePos.y, &bottle_25);
	}

	else if (fuel > 30 && fuel <= 60)
	{
		app->render->DrawTexture(bottleTexture, bottlePos.x - app->render->camera.x, bottlePos.y, &bottle_50);
	}

	else if (fuel > 60 && fuel <= 90)
	{
		app->render->DrawTexture(bottleTexture, bottlePos.x - app->render->camera.x, bottlePos.y, &bottle_75);
	}

	else if (fuel > 90 && fuel <= 100)
	{
		app->render->DrawTexture(bottleTexture, bottlePos.x - app->render->camera.x, bottlePos.y, &bottle_100);
	}

	if (fuel > 100) fuel = 100;
	if (fuel < 0) fuel = 0;


	if (timer > 30)
	{
		fuel -= 1;
		timer = 0;
	}
	timer++;

	currentAnimation->Update(dt);

	fuel1Collider->SetPos(fuel1Pos.x + 52, fuel1Pos.y + 48);

	if (!isPicked)
	{
		//Drawing the cubes
		SDL_Rect rect1 = currentAnimation->GetCurrentFrame();
		app->render->DrawTexture(fuelTexture, fuel1Pos.x, fuel1Pos.y, &rect1);
	}

	return true;
}

bool Fuel::PostUpdate()
{
	return true;
}

bool Fuel::CleanUp()
{
	//Unload the textures

	app->tex->UnLoad(fuelTexture);
	app->tex->UnLoad(bottleTexture);

	return true;
}
