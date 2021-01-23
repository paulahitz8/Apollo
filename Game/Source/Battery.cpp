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

	batteryTexture = app->tex->Load("Assets/Textures/Battery.png");
	font = new Font("Assets/Fonts/pixel_digivolve.xml", app->tex);

	batteryPos = { 100, 100 };

	battery_0 = { 0, 0, 0, 0 };
	battery_25 = { 0, 0, 0, 0 };
	battery_50 = { 0, 0, 0, 0 };
	battery_75 = { 0, 0, 0, 0 };
	battery_100 = { 0, 0, 0, 0 };

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
	if (battery < 5)
	{
		app->render->DrawTexture(batteryTexture, batteryPos.x - app->render->camera.x, batteryPos.y, &battery_0);
	}

	else if (battery >= 5 && battery < 30)
	{
		app->render->DrawTexture(batteryTexture, batteryPos.x - app->render->camera.x, batteryPos.y, &battery_25);
	}

	else if (battery >= 30 && battery < 60)
	{
		app->render->DrawTexture(batteryTexture, batteryPos.x - app->render->camera.x, batteryPos.y, &battery_50);
	}

	else if (battery > 60 && battery <= 90)
	{
		app->render->DrawTexture(batteryTexture, batteryPos.x - app->render->camera.x, batteryPos.y, &battery_75);
	}
	
	else if (battery > 90 && battery <= 100)
	{
		app->render->DrawTexture(batteryTexture, batteryPos.x - app->render->camera.x, batteryPos.y, &battery_100);
	}

	if (battery > 100) battery = 100;
	if (battery <= 0) battery = 0;

	if (timer > 200)
	{
		battery -= 1;
		timer = 0;
	}
	timer++;

	// Battery on screen
	char batteryC[16] = { 0 };
	sprintf_s(batteryC, 16, "%d", battery);
	app->render->DrawText(font, batteryC, 550, 15, 30, 4, { 255,255,255,255 });

	return true;
}

bool Battery::PostUpdate()
{
	return true;
}

bool Battery::CleanUp()
{
	//Unload the textures
	app->tex->UnLoad(batteryTexture);

	return true;
}
