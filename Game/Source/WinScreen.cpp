#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeScreen.h"
#include "WinScreen.h"
#include "TitleScreen.h"
#include "Scene.h"
#include "Player.h"
#include "Font.h"

#include "Defs.h"
#include "Log.h"


WinScreen::WinScreen() : Module()
{
	name.Create("winscreen");
}

WinScreen::~WinScreen() {}

void WinScreen::Init()
{
	active = false;
}

bool WinScreen::Awake()
{
	LOG("Loading Win Screen");
	bool ret = true;

	return ret;
}

bool WinScreen::Start()
{
	bool ret = true;
	app->scene->active = false;
	app->render->camera.x = 0;
	font = new Font("Assets/Fonts/pixel_digivolve.xml", app->tex);

	//app->audio->PlayMusic("Assets/Audio/Music/title_music.ogg", 0.0f);

	winScreen = app->tex->Load("Assets/Textures/WinScreen.png");

	return ret;
}

bool WinScreen::PreUpdate()
{
	return true;
}

bool WinScreen::Update(float dt)
{
	rect = { 0, 0, 1200, 700 };
	app->render->DrawTexture(winScreen, 0, 0, &rect);

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		//app->player->timer = 500;
		app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->scene, 100.0f);
	}

	app->render->DrawText(font, "YOU WON!", 400, 80, 100, 4, { 255, 255, 255, 255 });
	app->render->DrawText(font, "PRESS SPACE TO PLAY AGAIN", 320, 200, 40, 4, { 255, 255, 255, 255 });

	return true;
}

bool WinScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
	}

	return ret;
}

bool WinScreen::CleanUp()
{
	LOG("Freeing scene");
	
	app->tex->UnLoad(winScreen);

	return true;
}

