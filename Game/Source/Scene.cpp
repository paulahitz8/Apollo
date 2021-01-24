#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Asteroid.h"
#include "Battery.h"
#include "Fuel.h"
#include "Collisions.h"
#include "Physics.h"
#include "TitleScreen.h"
#include "Hearts.h"
#include "Font.h"

#include "Defs.h"
#include "Log.h"


Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene() {}

void Scene::Init()
{
	active = false;
}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;


	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	font = new Font("Assets/Fonts/pixel_digivolve.xml", app->tex);

	app->battery->Enable();
	app->fuel->Enable();
	app->asteroid->Enable();
	app->player->Enable();
	app->physics->Enable();
	app->hearts->Enable();
	app->collisions->Enable();

	//Home Planet
	homePos = { 340.0f, 419.0f };
	homeCol = app->collisions->AddCollider(homePos.x, homePos.y, 229, CircleCollider::Type::PLANET, this);
	planetHome = new Planet(homePos, 250.0f, 1, homeCol, { 9.8f, 9.8f }, 381, 229, 526, 0.1f, 0.1f);

	//Home Moon
	moonPos = { 963.0f, 154.0f };
	moonCol = app->collisions->AddCollider(moonPos.x, moonPos.y, 87, CircleCollider::Type::PLANET, this);
	moon = new Planet(moonPos, 150.0f, 2, moonCol, { 2.0f, 2.0f }, 200, 87, 290, 0.1f, 0.1f);

	// Blue
	bluePos = { 2718.0f, 332.0f };
	blueCol = app->collisions->AddCollider(bluePos.x, bluePos.y, 144, CircleCollider::Type::PLANET, this);
	blue = new Planet(bluePos, 300.0f, 3, blueCol, { 2.0f, 2.0f }, 365, 144, 500, 0.1f, 0.1f);

	// GasBoy
	gasBoyPos = { 4006.0f, 201.0f };
	gasBoyCol = app->collisions->AddCollider(gasBoyPos.x, gasBoyPos.y, 115, CircleCollider::Type::PLANET, this);
	gasBoy = new Planet(gasBoyPos, 170.0f, 4, gasBoyCol, { 2.0f, 2.0f }, 485, 115, 605, 0.6f, 0.1f);

	// Giant
	giantPos = { 5425.0f, 940.0f };
	giantCol = app->collisions->AddCollider(giantPos.x, giantPos.y, 442, CircleCollider::Type::PLANET, this);
	giant = new Planet(giantPos, 400.0f, 5, giantCol, { 2.0f, 2.0f }, 862, 442, 1062, 0.1f, 0.1f);

	// AquaBoy
	aquaBoyPos = { 7558.0f, 335.0f };
	aquaBoyCol = app->collisions->AddCollider(aquaBoyPos.x, aquaBoyPos.y, 69, CircleCollider::Type::PLANET, this);
	aquaBoy = new Planet(aquaBoyPos, 160.0f, 6, aquaBoyCol, { 2.0f, 2.0f }, 400, 69, 570, 0.1f, 0.8f);

	// newMoon
	newMoonPos = { 8902.0f, 578.0f };
	newMoonCol = app->collisions->AddCollider(newMoonPos.x, newMoonPos.y, 61, CircleCollider::Type::PLANET, this);
	newMoon = new Planet(newMoonPos, 150.0f, 7, newMoonCol, { 2.0f, 2.0f }, 211, 61, 261, 0.1f, 0.1f);

	// newHome
	newHomePos = { 9581.0f, 360.0f };
	newHomeCol = app->collisions->AddCollider(newHomePos.x, newHomePos.y, 231, CircleCollider::Type::PLANET, this);
	newHome = new Planet(newHomePos, 270.0f, 8, newHomeCol, { 2.0f, 2.0f }, 471, 231, 631, 0.1f, 0.1f);

	planetList.Add(planetHome);
	planetList.Add(moon);
	planetList.Add(blue);
	planetList.Add(gasBoy);
	planetList.Add(giant);
	planetList.Add(aquaBoy);
	planetList.Add(newMoon);
	planetList.Add(newHome);

	background = app->tex->Load("Assets/Textures/Apollo.png");
	gui = app->tex->Load("Assets/Textures/Interface.png");

	guiRect = { 0, 0, 395, 220 };
	timerText = 0;

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) app->LoadGameRequest();
	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) app->SaveGameRequest();

	//Camera: follow the player
	if (app->player->ovni->position.x >= 500 && app->player->ovni->position.x < 9290) app->render->camera.x = -(app->player->ovni->position.x - 500);

	// Draw background
	app->render->DrawTexture(background, 0, 0);
	app->render->DrawTexture(gui, 0 - app->render->camera.x, 0, &guiRect);

	if (app->collisions->debug)
	{
		//orbitRad Debug
		app->render->DrawCircle(homePos.x, homePos.y, 526, 255, 255, 255);
		app->render->DrawCircle(moonPos.x, moonPos.y, 290, 255, 255, 255);
		app->render->DrawCircle(bluePos.x, bluePos.y, 500, 255, 255, 255);
		app->render->DrawCircle(gasBoyPos.x, gasBoyPos.y, 605, 255, 255, 255);
		app->render->DrawCircle(giantPos.x, giantPos.y, 1062, 255, 255, 255);
		app->render->DrawCircle(aquaBoyPos.x, aquaBoyPos.y + 40, 570, 255, 255, 255);
		app->render->DrawCircle(newMoonPos.x, newMoonPos.y, 261, 255, 255, 255);
		app->render->DrawCircle(newHomePos.x, newHomePos.y, 631, 255, 255, 255);

		//fluidRad Debug
		app->render->DrawCircle(homePos.x, homePos.y, 381, 255, 0, 255);
		app->render->DrawCircle(moonPos.x, moonPos.y, 200, 255, 0, 255);
		app->render->DrawCircle(bluePos.x, bluePos.y, 365, 255, 0, 255);
		app->render->DrawCircle(gasBoyPos.x, gasBoyPos.y, 485, 255, 0, 255);
		app->render->DrawCircle(giantPos.x, giantPos.y, 862, 255, 0, 255);
		app->render->DrawCircle(aquaBoyPos.x, aquaBoyPos.y + 40, 400, 255, 0, 255);
		app->render->DrawCircle(newMoonPos.x, newMoonPos.y, 211, 255, 0, 255);
		app->render->DrawCircle(newHomePos.x, newHomePos.y + 15, 471, 255, 0, 255);
	}

	if (timerText < 1000)
	{
		app->render->DrawRectangle({ 240 - app->render->camera.x, 80, 750, 160 }, 0, 0, 0, 100);
		app->render->DrawText(font, "OH NO, YOUR PLANET HAS BEEN DESTROYED...", 290, 100, 30, 4, { 255, 255, 255, 255 });
		app->render->DrawText(font, "SCAN EVERY PLANET TO FIND YOUR NEW HOME", 277, 150, 30, 4, { 255, 255, 255, 255 });
		app->render->DrawText(font, "PRESS SPACE TO MOVE AROUND", 420, 200, 20, 4, { 255, 255, 255, 255 });
	}

	timerText++;

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->tex->UnLoad(background);
	active = false;

	return true;
}