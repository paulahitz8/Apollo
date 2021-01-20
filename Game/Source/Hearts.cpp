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
#include "Hearts.h"

Hearts::Hearts()
{
	name.Create("hearts");
}

Hearts::~Hearts() {}

bool Hearts::Awake(pugi::xml_node&)
{
	//animations
	
	// Red Heart
	redHeart.PushBack({6, 8, 50, 37});
	redHeart.PushBack({6, 49, 50, 37});
	redHeart.speed = 0.7f;

	// Gray Heart
	grayHeart.PushBack({67, 31, 50, 37});

	return true;
}


bool Hearts::Start()
{
	LOG("Loading player textures");

	heartTexture = app->tex->Load("Assets/Textures/heart_sprites.png");

	currentAnimation1 = &redHeart;
	currentAnimation2 = &redHeart;
	currentAnimation3 = &redHeart;

	heart1Pos = { 155, 20 };
	heart2Pos = { 210, 20 };
	heart3Pos = { 265, 20 };

	return true;
}

bool Hearts::PreUpdate()
{
	return true;
}

bool Hearts::Update(float dt)
{
	currentAnimation1->Update(dt);
	currentAnimation2->Update(dt);
	currentAnimation3->Update(dt);

	SDL_Rect rect1 = currentAnimation1->GetCurrentFrame();
	SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
	SDL_Rect rect3 = currentAnimation3->GetCurrentFrame();

	if (app->player->lives == 2)
	{
		currentAnimation3 = &grayHeart;
	}

	else if (app->player->lives == 1)
	{
		currentAnimation2 = &grayHeart;
	}

	else if (app->player->lives == 0)
	{
		currentAnimation1 = &grayHeart;
	}

	//Drawing the hearts
	app->render->DrawTexture(heartTexture, heart1Pos.x - app->render->camera.x, heart1Pos.y, &rect1);
	app->render->DrawTexture(heartTexture, heart2Pos.x - app->render->camera.x, heart2Pos.y, &rect2);
	app->render->DrawTexture(heartTexture, heart3Pos.x - app->render->camera.x, heart3Pos.y, &rect3);

	return true;
}

bool Hearts::PostUpdate()
{

	return true;
}

bool Hearts::CleanUp()
{
	//Unload the textures
	app->tex->UnLoad(heartTexture);

	return true;
}
