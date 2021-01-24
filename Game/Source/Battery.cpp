#include "Battery.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Collisions.h"
#include "FadeScreen.h"
#include "WinScreen.h"
#include "Point.h"
#include "Player.h"
#include "Font.h"

Battery::Battery()
{
	name.Create("battery");
}

Battery::~Battery() {}

bool Battery::Awake(pugi::xml_node&)
{
	//animations

	return true;
}


bool Battery::Start()
{
	LOG("Loading player textures");

	batteryTexture0 = app->tex->Load("Assets/Textures/Battery0.png");
	batteryTexture25 = app->tex->Load("Assets/Textures/Battery25.png");
	batteryTexture50 = app->tex->Load("Assets/Textures/Battery50.png");
	batteryTexture75 = app->tex->Load("Assets/Textures/Battery75.png");
	batteryTexture100 = app->tex->Load("Assets/Textures/Battery.png");

	font = new Font("Assets/Fonts/pixel_digivolve.xml", app->tex);

	batteryPos = { 1050, 20 };

	battery_0 = { 84, 28, 127, 69 };
	battery_25 = { 121, 32, 128, 69 };
	battery_50 = { 112, 40, 127, 69 };
	battery_75 = { 151, 40, 127, 69 };
	battery_100 = { 134, 40, 127, 69 };

	battery = 100;
	timer = 0;

	return true;
}

bool Battery::PreUpdate()
{
	return true;
}

bool Battery::Update(float dt)
{
	if (battery == 0)
	{
		app->player->lives = 0;
	}

	if (battery < 5)
	{
		app->render->DrawTexture(batteryTexture0, batteryPos.x - app->render->camera.x, batteryPos.y, &battery_0);
	}
	else if (battery >= 5 && battery < 30)
	{
		app->render->DrawTexture(batteryTexture25, batteryPos.x - app->render->camera.x, batteryPos.y, &battery_25);
	}
	else if (battery >= 30 && battery < 60)
	{
		app->render->DrawTexture(batteryTexture50, batteryPos.x - app->render->camera.x, batteryPos.y, &battery_50);
	}
	else if (battery >= 60 && battery <= 90)
	{
		app->render->DrawTexture(batteryTexture75, batteryPos.x - app->render->camera.x, batteryPos.y, &battery_75);
	}
	else if (battery > 90 && battery <= 100)
	{
		app->render->DrawTexture(batteryTexture100, batteryPos.x - app->render->camera.x, batteryPos.y, &battery_100);
	}

	if (battery > 100) battery = 100;
	if (battery <= 0) battery = 0;

	if (timer > 100)
	{
		battery -= 1;
		timer = 0;
	}
	timer++;

	// Battery on screen
	char batteryC[16] = { 0 };
	sprintf_s(batteryC, 16, "%d", battery);
	app->render->DrawText(font, batteryC, 1000, 35, 30, 4, { 255, 255, 255, 255 });

	return true;
}

bool Battery::PostUpdate()
{
	return true;
}

bool Battery::CleanUp()
{
	//Unload the textures
	app->tex->UnLoad(batteryTexture0);
	app->tex->UnLoad(batteryTexture25);
	app->tex->UnLoad(batteryTexture50);
	app->tex->UnLoad(batteryTexture75);
	app->tex->UnLoad(batteryTexture100);

	return true;
}
