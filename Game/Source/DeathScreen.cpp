#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeScreen.h"
#include "Scene.h"
#include "DeathScreen.h"
#include "TitleScreen.h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"

DeathScreen::DeathScreen() : Module()
{
	name.Create("DeathScreen");
}

DeathScreen::~DeathScreen() {}

void DeathScreen::Init()
{
	active = false;
}

bool DeathScreen::Awake()
{
	LOG("Loading Death Screen");
	bool ret = true;

	return ret;
}

bool DeathScreen::Start()
{
	bool ret = true;
	app->scene->active = false;
	app->render->camera.x = 0;
	deathScreen = app->tex->Load("Assets/Textures/death_screen.png");

	//app->audio->PlayMusic("Assets/Audio/Music/death_music.ogg", 0.0f);

	return ret;
}

bool DeathScreen::PreUpdate()
{
	return true;
}

bool DeathScreen::Update(float dt)
{
	rect = { 0, 0, 1200, 700 };
	app->render->DrawTexture(deathScreen, 0, 0, &rect);

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		//app->player->timer = 500;
		app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->titleScreen, 100.0f);
	}

	return true;
}

// Called each loop iteration
bool DeathScreen::PostUpdate()
{
	bool ret = true;
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
	}

	return ret;
}

// Called before quitting
bool DeathScreen::CleanUp()
{
	LOG("Freeing scene");

	app->tex->UnLoad(deathScreen);

	return true;
}

