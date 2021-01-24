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
#include "Asteroid.h"
#include "Font.h"
#include "Battery.h"
#include "Hearts.h"

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
	scanPlanet.speed = 2.0f;

	// Animation scanNo;
	scanNo.PushBack({ 1098, 207, 112, 68 });

	// Animation scanYes;
	scanYes.PushBack({ 971, 208, 112, 68 });

	// Animation impulse;
	impulse.PushBack({ 77, 47, 112, 68 });

	// Animation getFuel;
	getFuel.PushBack({ 77, 221, 112, 68 });

	return true;
}

bool Player::Start()
{
	LOG("Loading player textures");

	playerTexture = app->tex->Load("Assets/Textures/ApolloPlayer.png");

	lives = 3;

	currentAnimation = &idle;

	playerPos = { 700.0f, 350.0f };
	playerAcceleration = { 0.0f, 0.0f };
	playerVelocity = { 0.0f, 0.0f };
	playerFuel = 100;
	playerRotation = 0;
	propForce = 30.0f;
	pi = 3.1416f;
	turnAngle = 4.0f;
	
	//Scan
	scan = false;
	colliding = false;
	weAreIn = nullptr;
	scanTimer = 0;

	timer = 0;
	spaceTimer = 0;

	if (isWon || isLose)
	{
		timer = 500;
	}

	isWon = false;
	isLose = false;

	ovni = new Spaceship(playerPos, 5.0f, playerCollider, playerVelocity, playerAcceleration, 2.0f, playerFuel, playerRotation);
	playerCollider = app->collisions->AddCollider(ovni->position.x + 33, ovni->position.y + 33, 33, CircleCollider::Type::PLAYER, this);

	playerRect = { 78,132,112,67 };

	font = new Font("Assets/Fonts/pixel_digivolve.xml", app->tex);

	return true;
}

bool Player::PreUpdate()
{
	colliding = false;

	return true;
}


bool Player::Update(float dt)
{
	if (timer < 500)
	{
		timer++;
		return true;
	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		isWon = true;
		app->collisions->debug = false;
		app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->winScreen, 60.0f);
		lives = 3;
		app->battery->Disable();
		app->fuel->Disable();
		app->asteroid->Disable();
		app->hearts->Disable();
		app->collisions->Disable();
	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		lives = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && colliding == true)
	{
		scan = true;
		currentAnimation = &scanPlanet;
		float dist = 1500000;

		for (int i = 0; i < app->scene->planetList.Count(); i++)
		{
			fPoint auxVec = app->scene->planetList[i]->position - ovni->position;
			float newDist = sqrt(auxVec.x * auxVec.x + auxVec.y * auxVec.y);

			if (newDist < dist)
			{
				dist = newDist;
				weAreIn = app->scene->planetList[i];
			}
		}
	}

	if (colliding && !scan) app->render->DrawText(font, "PRESS S TO SCAN", 450, 620, 35, 4, { 255, 255, 255, 255 });

	if (scan && scanTimer < 150) app->render->DrawText(font, "SCANNING...", 480, 600, 60, 4, { 255, 255, 255, 255 });

	if (!scan)
	{
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
			spaceTimer = 0;
			currentAnimation = &impulse;
			app->fuel->fuel -= 1;

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
	}
	else 
	{
		if (scanTimer > 150)
		{
			if (weAreIn->id == 8)
			{
				app->render->DrawText(font, "SUCCESS: this planet is habitable", 300, 620, 35, 4, { 160, 255, 179, 255 });
				currentAnimation = &scanYes;
				isWon = true;
			}
			else
			{
				app->render->DrawText(font, "ERROR: this planet is not habitable", 300, 620, 35, 4, { 194, 42, 51, 255 });
				currentAnimation = &scanNo;
			}
			
			if (scanTimer > 280)
			{
				scan = false;
				scanTimer = 0;
				if (isWon)
				{
					app->collisions->debug = false;
					app->fadeScreen->active = true;
					app->fadeScreen->FadeToBlack(this, (Module*)app->winScreen, 60.0f);
					lives = 3;
					app->battery->Disable();
					app->fuel->Disable();
					app->asteroid->Disable();
					app->hearts->Disable();
					app->collisions->Disable();
				}
				currentAnimation = &idle;
			}
		}
		scanTimer++;
	}

	if (app->fuel->fuel == 0)
	{
		lives--;
		app->fuel->fuel = 100;
	}

	if (lives == 0)
	{
		app->collisions->debug = false;
		app->fadeScreen->active = true;
		isLose = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->deathScreen, 60.0f);
		lives = 3;
		app->battery->Disable();
		app->fuel->Disable();
		app->asteroid->Disable();
		app->hearts->Disable();
		app->collisions->Disable();
	}

	currentAnimation->Update(dt);
	
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(playerTexture, ovni->position.x, ovni->position.y, &rect, 1.0f, ovni->rotation);

	playerCollider->SetPos(ovni->position.x + 55, ovni->position.y + 33);

	if (ovni->velocity.x > 500) ovni->velocity.x = 500;
	if (ovni->velocity.x < -500) ovni->velocity.x = -500;
	if (ovni->velocity.y > 500) ovni->velocity.y = 500;
	if (ovni->velocity.y < -500) ovni->velocity.y = -500;
	
	if (spaceTimer == 20)
	{
		currentAnimation = &idle;
	}

	spaceTimer++;

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
			if (c2->x == 3200 + 52)
			{
				app->fuel->isPicked1 = true;
			}
			else if (c2->x == 6000 + 52)
			{
				app->fuel->isPicked2 = true;
			}
			else if (c2->x == 8200 + 52)
			{
				app->fuel->isPicked3 = true;
			}

			c2->pendingToDelete = true;
			app->fuel->fuel += 20;
		}

		else if (c2->type == CircleCollider::Type::PLANET)
		{
			colliding = true;

			if (c1->x < c2->x)
			{
				ovni->velocity.x = -ovni->velocity.x/2;
			}
			else
			{
				ovni->velocity.x = -ovni->velocity.x/2;
			}

			if (c1->y < c2->y)
			{
				ovni->velocity.y = -ovni->velocity.y/2;
			}
			else
			{
				ovni->velocity.y = -ovni->velocity.y/2;
			}
		}

		else if (c2->type == CircleCollider::Type::ASTEROID)
		{
			if (c1->x < c2->x)
			{
				ovni->velocity.x = -ovni->velocity.x / 2;
			}
			else
			{
				ovni->velocity.x = -ovni->velocity.x / 2;
			}

			if (c1->y < c2->y)
			{
				ovni->velocity.y = -ovni->velocity.y / 2;
			}
			else
			{
				ovni->velocity.y = -ovni->velocity.y / 2;
			}
			lives--;
			c2->pendingToDelete = true;

			if (c2->x == 1700 + 33)
			{
				app->asteroid->as1Boom = true;
			}

			if (c2->x == 1800 + 25)
			{
				app->asteroid->as2Boom = true;
			}

			if (c2->x == 6300 + 33)
			{
				app->asteroid->as3Boom = true;
			}

			if (c2->x == 6400 + 33)
			{
				app->asteroid->as4Boom = true;
			}

			if (c2->x == 1600 + 33)
			{
				app->asteroid->as5Boom = true;
			}

			if (c2->x == 6200 + 25)
			{
				app->asteroid->as6Boom = true;
			}
		}
	}
}