#pragma once

#include "Particle.h"

class ParticleForceGenerator
{
public:
	// Overload to provide functionality
	virtual void updateForce(Particle* particle, float t) = 0;
};

//--------------------------------------------------------------------------------------------

class ParticleForceRegistry
{
protected:
	// Storage for generator-particle entry
	struct ParticleForceRegistration
	{
		Particle* particle;
		ParticleForceGenerator* fg;
	};
	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;
public:
	// Associate generator with a particle
	void add(Particle* particle, ParticleForceGenerator* fg);
	// Remove association
	void remove(Particle* particle, ParticleForceGenerator* fg);
	void removePartInstance(Particle* particle);
	// Removes all associations. Particle and Generators won't be deleted
	void clear() ;
	// Update all the generators in the registry
	void updateForces(float t);
};

//--------------------------------------------------------------------------------------------

class ParticleGravity : public ParticleForceGenerator
{
private:
	// Acceleration for gravity
	Vector3 g;
public:
	ParticleGravity(const Vector3& gravity) : g(gravity) {};
	virtual void updateForce(Particle* particle, float t);
};

//--------------------------------------------------------------------------------------------

class Wind : public ParticleForceGenerator
{
private:
	Vector3 g;
	float radius;
	RenderItem* renderItem;
	bool activated;
public:
	Wind(const Vector3& force, float rad) : g(force), radius(rad), renderItem(nullptr), activated(false) {};
	~Wind() { deactivateWind(); };
	virtual void updateForce(Particle* particle, float t);
	void activateWind();
	void deactivateWind();
};

//--------------------------------------------------------------------------------------------

class Explosion : public ParticleForceGenerator
{
private:
	Vector3 g;
	float radius;
	RenderItem* renderItem;
	bool activated;
	float lastIni;
	float duration;
	
	void deactivateExplosion();
public:
	Explosion(Vector3 x, float rad) : g(x), radius(rad), renderItem(nullptr), activated(false), lastIni(0.0), duration(0.25) {};
	~Explosion() { deactivateExplosion(); };
	virtual void updateForce(Particle* particle, float t);
	void update(float t);
	void activateExplosion();
};

//--------------------------------------------------------------------------------------------