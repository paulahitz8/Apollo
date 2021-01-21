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
#include "Fuel.h"

Player::Player()
{
	name.Create("player");


}

Player::~Player() {}

bool Player::Awake(pugi::xml_node&)
{
	//animations

	// Animation idle;
	idle.PushBack({ 78, 132, 112, 68 });
	idle.PushBack({ 231, 131, 112, 68 });
	idle.PushBack({ 385, 130, 112, 68 });
	idle.PushBack({ 538, 129, 112, 68 });
	idle.PushBack({ 682, 128, 112, 68 });
	idle.PushBack({ 835, 127, 112, 68 });
	idle.speed = 5.0f;

	// Animation scanPlanet;
	scanPlanet.PushBack({ 77, 221, 112, 68 });
	scanPlanet.PushBack({ 231, 217, 112, 68 });
	scanPlanet.PushBack({ 385, 216, 112, 68 });
	scanPlanet.PushBack({ 538, 215, 112, 68 });
	scanPlanet.PushBack({ 682, 215, 112, 68 });
	scanPlanet.PushBack({ 835, 213, 112, 68 });
	scanPlanet.speed = 5.0f;

	// Animation scanNo;
	scanNo.PushBack({ 77, 221, 112, 68 });

	// Animation scanYes;
	scanYes.PushBack({ 1098, 207, 112, 68 });

	// Animation impulse;
	impulse.PushBack({ 77, 47, 112, 68 });
	impulse.PushBack({ 221, 46, 112, 68 });
	impulse.speed = 10.0f;

	// Animation getFuel;
	getFuel.PushBack({ 77, 221, 112, 68 });

	return true;
}

bool Player::Start()
{
	LOG("Loading player textures");

	int timer = 0;

	playerTexture = app->tex->Load("Assets/Textures/ApolloPlayer.png");

	lives = 3;

	currentAnimation = &idle;

	playerPos = { 700.0f, 350.0f };
	playerAcceleration = { 0.0f, 0.0f };
	playerFuel = 100;
	playerRotation = 0;
	propForce = 30.0f;
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
	//if (timer < 500)
	//{
	//	timer++;
	//	return true;
	//}

	
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		ovni->rotation += turnAngle;
		if (ovni->rotation > 360)
		{
			ovni->rotation = ovni->rotation / 360;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		ovni->rotation -= turnAngle;
		if (ovni->rotation > 360)
		{
			ovni->rotation = ovni->rotation / 360;
		}
	}

	if (ovni->rotation < 0)
	{
		ovni->rotation = 360 + ovni->rotation;
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
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
			direction.x = ovni->position.x * -cos(rads) * propForce;
			direction.y = ovni->position.y * sin(rads) * propForce;
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
			direction.x = ovni->position.x * cos(rads) * propForce;
			direction.y = ovni->position.y * -sin(rads) * propForce;
		}

		ovni->ApplyForce(direction);
	}

	currentAnimation->Update(dt);
	
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(playerTexture, ovni->position.x, ovni->position.y, &rect, 1.0, ovni->rotation);

	playerCollider->SetPos(ovni->position.x + 55, ovni->position.y + 33);

	if (ovni->velocity.x > 500) ovni->velocity.x = 500;
	if (ovni->velocity.x < -500) ovni->velocity.x = -500;
	if (ovni->velocity.y > 500) ovni->velocity.y = 500;
	if (ovni->velocity.y < -500) ovni->velocity.y = -500;

	return true;
}


bool Player::PostUpdate()
{
	 //Map Limits
	if (ovni->position.x < 0)
	{
		ovni->velocity.x = 0;
		ovni->ApplyForce({ 25000, 0 });
	}

	if (ovni->position.y < 0)
	{
		ovni->velocity.y = 0;
		ovni->ApplyForce({ 0, 25000 });
	}
	if (ovni->position.x > 9870)
	{
		ovni->velocity.x = 0;
		ovni->ApplyForce({ -25000, 0 });
	}

	if (ovni->position.y > 630)
	{
		ovni->velocity.y = 0;
		ovni->ApplyForce({ 0, -25000 });
	}



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

void Player::OnCollision(CircleCollider* c1, CircleCollider* c2)
{
	if (c1->type == CircleCollider::Type::PLAYER)
	{
		if (c2->type == CircleCollider::Type::FUEL)
		{
			app->fuel->isPicked = true;
			c2->pendingToDelete = true;
			app->fuel->fuel += 20;
		}

		else if (c2->type == CircleCollider::Type::PLANET)
		{
			if (c1->x < c2->x)
			{
				ovni->velocity.x = -ovni->velocity.x;
			}
			else
			{
				ovni->velocity.x = -ovni->velocity.x;
			}

			if (c1->y < c2->y)
			{
				ovni->velocity.y = -ovni->velocity.y;
			}
			else
			{
				ovni->velocity.y = -ovni->velocity.y;
			}
		}
	}
}