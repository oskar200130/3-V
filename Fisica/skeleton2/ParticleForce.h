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
	// Removes all associations. Particle and Generators won't be deleted
	void clear();
	// Update all the generators in the registry
	void updateForces(float t);
};

//--------------------------------------------------------------------------------------------

class ParticleGravity : public ParticleForceGenerator
{
	// Acceleration for gravity
	Vector3 g;
public:
	ParticleGravity(const Vector3& gravity) : g(gravity) {}
	virtual void updateForce(Particle* particle, float t);
};

//--------------------------------------------------------------------------------------------