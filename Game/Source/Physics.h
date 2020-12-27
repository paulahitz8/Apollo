#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Module.h"
#include "List.h"
#include "Collisions.h"
#include "Point.h"
#include "SString.h"

struct SDL_Texture;

class Body
{
public:

	fPoint position;
	float mass;
	
	SString name;
	//BodyType bodyType;
	Collider* collider;
	SDL_Texture* texture;

public:
	//make angulos positivos
};

class Spaceship : public Body
{
public:

	fPoint velocity, acceleration;
	List<fPoint> forces;
	fPoint totalForce;

	float health;
	float fuel; 
	int ammo;
	float frontalArea;


public:

	void Shoot();
};

class Planet : public Body
{
	fPoint gravity;
	fPoint groundFriction = { 0.0f, 0.0f };
	fPoint airFriction = { 0.0f, 0.0f };
	float radius;
	float density;
};


class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

public:
	Spaceship apollo;
	Planet saturn;
	Planet mercury;

public:
	fPoint ForceGravity(float shipMass, float planetMass, iPoint shipPos, iPoint planetPos);
	fPoint ForceAeroDrag();
	fPoint ForceHydroDrag();
	fPoint ForceHydroBuoy();
	void ApplyForce(Spaceship body, fPoint force);
	void Rotate(Spaceship body, float angle);
	void OnCollision(Collider* c1, Collider* c2);
	void SolveCollision();
	void NewtonLaw(); // f = ma
	// void NewtonThirdLaw(); si añadimos otros dynamic bodies
};

class Physics : public Module
{
public:

	Physics();
	virtual ~Physics();

	void Init();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

public:

	void Step(float dt);
	void Integrate(Spaceship* value, float dt);

};

#endif
