#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Collisions.h"
#include "FadeScreen.h"
#include "Window.h"

Player::Player()
{
	name.Create("player");
}

Player::~Player() {}

bool Player::Awake(pugi::xml_node&)
{
	//animations

	return true;
}

bool Player::Start()
{
	LOG("Loading player textures");

	int timer = 0;

	playerTexture = app->tex->Load("Assets/Textures/ApolloPlayer.png");
	life = app->tex->Load("Assets/Textures/Life.png");
	lifeGrey = app->tex->Load("Assets/Textures/LifeGrey.png");
	//currentAnimation = &rightIdle;
	playerPos = { 100.0f, 350.0f };
	playerAcceleration = { 0.0f, 0.0f };
	playerFuel = 100;
	playerRotation = 0;
	propForce = 15.0f;
	pi = 3.1416f;
	turnAngle = 4.0f;

	ovni = new Spaceship(playerPos, 5.0f, playerCollider, playerAcceleration, 2.0f, playerFuel, playerRotation);
	playerCollider = app->collisions->AddCollider(ovni->position.x + 33, ovni->position.y + 33, 33, CircleCollider::Type::PLAYER, this);

	playerRect = { 78,132,112,67 };

	return true;
}

bool Player::PreUpdate()
{
	return true;
}


bool Player::Update(float dt)
{
	//bla bla bla

	//currentAnimation->Update(dt);

	//Drawing the player
	//SDL_Rect rect = currentAnimation->GetCurrentFrame();

	//if (timer < 500)
	//{
	//	timer++;
	//	return true;
	//}

	app->render->DrawTexture(playerTexture, ovni->position.x, ovni->position.y, &playerRect, 1.0f, ovni->rotation);

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		ovni->rotation += turnAngle;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		ovni->rotation += -turnAngle;
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		fPoint direction = { 0.0f, 0.0f };
		float rads = ovni->rotation * pi / 180;

		// first quadrant
		if (rads >= 0 && rads <= 90)
		{
			direction.x = ovni->position.x * cos(rads) * propForce;
			direction.y = ovni->position.y * sin(rads) * propForce;
		}

		// second quadrant
		if (rads > 90 && rads <= 180)
		{
			direction.x = ovni->position.x * cos(rads) * propForce;
			direction.y = ovni->position.y * -sin(rads) * propForce;
		}

		// third quadrant
		if (rads > 180 && rads <= 270)
		{
			direction.x = ovni->position.x * -cos(rads) * propForce;
			direction.y = ovni->position.y * -sin(rads) * propForce;
		}

		// fourth quadrant
		if (rads > 270 && rads <= 360)
		{
			direction.x = ovni->position.x * -cos(rads) * propForce;
			direction.y = ovni->position.y * sin(rads) * propForce;
		}

		direction.x = -direction.x;
		direction.y = -direction.y;

		ovni->ApplyForce(direction);
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		fPoint direction = { 0.0f, 0.0f };
		float rads = ovni->rotation * pi / 180;

		// first quadrant
		if (rads >= 0 && rads <= 90)
		{
			direction.x = ovni->position.x * cos(rads) * propForce;
			direction.y = ovni->position.y * sin(rads) * propForce;
		}

		// second quadrant
		if (rads > 90 && rads <= 180)
		{
			direction.x = ovni->position.x * cos(rads) * propForce;
			direction.y = ovni->position.y * -sin(rads) * propForce;
		}

		// third quadrant
		if (rads > 180 && rads <= 270)
		{
			direction.x = ovni->position.x * -cos(rads) * propForce;
			direction.y = ovni->position.y * -sin(rads) * propForce;
		}

		// fourth quadrant
		if (rads > 270 && rads <= 360)
		{
			direction.x = ovni->position.x * -cos(rads) * propForce;
			direction.y = ovni->position.y * sin(rads) * propForce;
		}

		ovni->ApplyForce(direction);
	}


	playerCollider->SetPos(ovni->position.x + 55, ovni->position.y + 33);

	return true;
}


bool Player::PostUpdate()
{
	// Map Limits
	if (ovni->position.x <= 0) ovni->position.x = 0;
	if (ovni->position.y <= 0) ovni->position.y = 0;
	if (ovni->position.x > 9870) ovni->position.x = 9870;
	if (ovni->position.y > 630) ovni->position.y = 630;

	//if ((playerPos.x + playerRect.x) > (app->map->data.width * app->map->data.tileWidth)) --playerPos.x;

	//In case of godmode on
	//if (playerPos.y <= 0) playerPos.y = 0;

	//if ((playerPos.y + playerRect.y) > (app->map->data.height * app->map->data.tileHeight)) --playerPos.y;

	return true;
}

bool Player::CleanUp()
{
	//Unload the audios
	app->tex->UnLoad(playerTexture);

	return true;
}

bool Player::LoadState(pugi::xml_node& data)
{
	ovni->position.x = data.child("player").attribute("x").as_int();
	ovni->position.y = data.child("player").attribute("y").as_int();

	return true;
}

bool Player::SaveState(pugi::xml_node& data)
{
	pugi::xml_node player = data.append_child("player");

	player.append_attribute("x") = ovni->position.x;
	player.append_attribute("y") = ovni->position.y;

	return true;
}