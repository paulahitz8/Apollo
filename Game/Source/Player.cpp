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

	playerTexture = app->tex->Load("Assets/Textures/ApolloPlayer.png");
	//currentAnimation = &rightIdle;
	playerPos = { 100.0f, 350.0f };
	playerAcceleration = { 0.0f, 0.0f };
	playerFuel = 100;

	ovni = new Spaceship(playerPos, 5.0f, playerCollider, playerAcceleration, 2.0f, playerFuel);
	playerCollider = app->collisions->AddCollider(ovni->position.x + 33, ovni->position.y + 33, 33, CircleCollider::Type::PLAYER, this);

	playerRect = { 156,79,113,68 };

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
	app->render->DrawTexture(playerTexture, ovni->position.x, ovni->position.y, &playerRect);

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		ovni->position.x += 5;
	}


	return true;
}


bool Player::PostUpdate()
{
	// Map Limits
	if (ovni->position.x <= 0) ovni->position.x = 0;
	if (ovni->position.x > 9870) ovni->position.x = 9870;

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