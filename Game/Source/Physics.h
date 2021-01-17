#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Module.h"
#include "List.h"
#include "Collisions.h"
#include "Point.h"
#include "SString.h"

struct SDL_Texture;


class Spaceship
{
public:

	fPoint position;
	float mass;

	SString name;
	//BodyType bodyType;
	Collider* collider;
	SDL_Texture* texture;

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

class Planet
{
public:
	Planet(fPoint position, float mass, int id, Collider* collider, fPoint gravity, float fluidRad, float planetRad, float density);
	~Planet();

	fPoint position;
	float mass;

	int id;
	//BodyType bodyType;
	Collider* collider;
	SDL_Texture* texture;

	fPoint gravity;
	float fluidRad;
	float orbitRad;
	float planetRad;
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
	fPoint ForceAeroDrag(float density, fPoint shipVel, float frontalArea, float dragCoefficient);
	fPoint ForceHydroDrag(fPoint shipVel);
	fPoint ForceHydroBuoy(float density, fPoint gravity, float fluidVolume, float shipMass);
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

	List<Planet*> planetList;

public:

	void Step(float dt);
	void Integrate(Spaceship* value, float dt);

};

#endif
