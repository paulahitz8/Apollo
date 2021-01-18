#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Collisions.h"
#include "Physics.h"

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
	int w, h;
	uchar* data = NULL;

	RELEASE_ARRAY(data);

	//Home Planet
	homePos = { 340, 421 };
	homeCol = app->collisions->AddCollider(homePos.x, homePos.y, 231, CircleCollider::Type::PLANET, this);
	planetHome = new Planet(homePos, 50.0f, 1, homeCol, { 9.8f, 9.8f }, 0.0, 231, 0.1f);

	//Home Moon
	moonPos = { 963, 155 };
	moonCol = app->collisions->AddCollider(moonPos.x, moonPos.y, 87, CircleCollider::Type::PLANET, this);
	planetHome = new Planet(moonPos, 50.0f, 2, moonCol, { 2.0f, 2.0f }, 0.0, 87, 0.1f);

	// Blue
	bluePos = { 2720, 338 };
	blueCol = app->collisions->AddCollider(bluePos.x, bluePos.y, 145, CircleCollider::Type::PLANET, this);
	blue = new Planet(bluePos, 50.0f, 3, blueCol, { 2.0f, 2.0f }, 0.0, 145, 0.1f);

	// GasBoy
	gasBoyPos = { 4007, 202 };
	gasBoyCol = app->collisions->AddCollider(gasBoyPos.x, gasBoyPos.y, 115, CircleCollider::Type::PLANET, this);
	gasBoy = new Planet(gasBoyPos, 50.0f, 4, gasBoyCol, { 2.0f, 2.0f }, 506, 115, 0.1f);

	// Giant
	giantPos = { 5455, 800 };
	giantCol = app->collisions->AddCollider(giantPos.x, giantPos.y, 442, CircleCollider::Type::PLANET, this);
	giant = new Planet(giantPos, 50.0f, 5, giantCol, { 2.0f, 2.0f }, 0.0f, 442, 0.1f);

	// AquaBoy
	aquaBoyPos = { 7558, 340 };
	aquaBoyCol = app->collisions->AddCollider(aquaBoyPos.x, aquaBoyPos.y, 70, CircleCollider::Type::PLANET, this);
	aquaBoy = new Planet(aquaBoyPos, 50.0f, 6, aquaBoyCol, { 2.0f, 2.0f }, 412.0f, 70, 0.1f);

	// newMoon
	newMoonPos = { 8902, 578 };
	newMoonCol = app->collisions->AddCollider(newMoonPos.x, newMoonPos.y, 61, CircleCollider::Type::PLANET, this);
	newMoon = new Planet(newMoonPos, 50.0f, 7, newMoonCol, { 2.0f, 2.0f }, 0.0f, 61, 0.1f);

	// newHome
	newHomePos = { 9586, 356 };
	newHomeCol = app->collisions->AddCollider(newHomePos.x, newHomePos.y, 231, CircleCollider::Type::PLANET, this);
	newHome = new Planet(newHomePos, 50.0f, 8, newHomeCol, { 2.0f, 2.0f }, 0.0f, 231, 0.1f);


	background = app->tex->Load("Assets/Textures/Apollo.png");

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
	/*if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		app->map->ChangePropertyOfLayer("Collisions", "Drawable", 1);
		boolPath = !boolPath;
	}*/

	//Camera: follow the player
	if (app->player->playerPos.x >= 500 && app->player->playerPos.x < 9320) app->render->camera.x = -(app->player->playerPos.x - 500);

	// Camera limits
	//if (app->render->camera.x > 0) app->render->camera.x--;

	// Draw background
	app->render->DrawTexture(background, 0, 0);

	//for (int i = 0; (wmb * i) <= (w - app->render->camera.x); i++) app->render->DrawTexture(background, wmb * i, app->map->data.tileHeight * 2, false, 0.4f);

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