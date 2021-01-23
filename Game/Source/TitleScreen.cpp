#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "TitleScreen.h"
#include "LogoScreen.h"
#include "FadeScreen.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"


TitleScreen::TitleScreen() : Module()
{
	name.Create("TitleScreen");
}

TitleScreen::~TitleScreen() {}

void TitleScreen::Init()
{
	active = false;
}

bool TitleScreen::Awake()
{
	LOG("Loading Title Screen");
	bool ret = true;

	return ret;
}

bool TitleScreen::Start()
{
	bool ret = true;

	timer = 0;
	app->audio->PlayMusic("Assets/Audio/Music/title_music.ogg");
	titleScreen = app->tex->Load("Assets/Textures/title_screen.png");

	return ret;
}

bool TitleScreen::PreUpdate()
{
	return true;
}

bool TitleScreen::Update(float dt)
{
	rect = { 0, 0, 1200, 700 };
	app->render->DrawTexture(titleScreen, 0 - app->render->camera.x, 0, &rect);

	timer++;

	return true;
}

// Called each loop iteration
bool TitleScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	if (timer == 250)
	{
		app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->scene, 50.0f);
	}

	return ret;
}

// Called before quitting
bool TitleScreen::CleanUp()
{
	LOG("Freeing scene");
	
	app->tex->UnLoad(titleScreen);
	
	return true;
}