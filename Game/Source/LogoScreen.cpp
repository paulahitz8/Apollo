#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeScreen.h"
#include "LogoScreen.h"
#include "TitleScreen.h"
#include "DeathScreen.h"
#include "WinScreen.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"

LogoScreen::LogoScreen() : Module()
{
	name.Create("LogoScreen");
}

LogoScreen::~LogoScreen() {}

void LogoScreen::Init()
{
	active = true;
}

bool LogoScreen::Awake()
{
	LOG("Loading Logo Screen");
	bool ret = true;

	return ret;
}

bool LogoScreen::Start()
{
	bool ret = true;

	app->titleScreen->active = false;
	app->deathScreen->active = false;
	app->winScreen->active = false;

	logoScreen = app->tex->Load("Assets/Textures/logo_screen.png");

	logoMusicFx = app->audio->LoadFx("Assets/Audio/Fx/logo_music.wav");
	app->audio->PlayFx(logoMusicFx);
	
	timerLogo = 0;

	return ret;
}

bool LogoScreen::PreUpdate()
{
	return true;
}

bool LogoScreen::Update(float dt)
{
	rect = { 0, 0, 1200, 700 };
	app->render->DrawTexture(logoScreen, 0 - app->render->camera.x, 0, &rect);

	timerLogo++;

	return true;
}

bool LogoScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
	}

	if (timerLogo == 160) 
	{
		app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->titleScreen, 60.0f);
	}

	return ret;
}

bool LogoScreen::CleanUp()
{
	LOG("Freeing scene");

	active = false;
	app->tex->UnLoad(logoScreen);

	return true;
}