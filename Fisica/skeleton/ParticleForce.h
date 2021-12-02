#pragma once

#include "Particle.h"
#include "BodyForce.h"

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
	// Storage for generator-particle entry
	struct ParticleForceRegistration
	{
		Particle* particle;
		ParticleForceGenerator* fg;
	};

	struct BodyForceRegistration {
		SolidBody* body;
		BodyForceGenerator* fg;
	};

	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;

	typedef std::vector<BodyForceRegistration> Registry_rigid;
	Registry_rigid registrations_rigid;
public:
	// Associate generator with a particle
	void add(Particle* particle, SolidBody* body, ParticleForceGenerator* fg, BodyForceGenerator* bf);
	// Remove association
	void remove(Particle* particle, SolidBody* body, ParticleForceGenerator* fg, BodyForceGenerator* bf);
	void removePartInstance(Particle* particle, SolidBody* body);
	// Removes all associations. Particle and Generators won't be deleted
	void clear();
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
	PxTransform* pos;
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
	PxTransform* pos;
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

class ParticleSpring : public ParticleForceGenerator {
	//The other part the string is attached to
	Particle* other;

	float k;
	float restLenght;

public:
	ParticleSpring(Particle* _other, float _k, float restL) :other(_other), k(_k), restLenght(restL) {};
	inline void changeK(float _k) { k = _k; };
	virtual void updateForce(Particle* particle, float t);
};

//--------------------------------------------------------------------------------------------

class ParticleBuoyancy : public ParticleForceGenerator {
private:
	float maxDepth;
	float volume;

	float waterHeight;

	float liquidDensity;

public:
	ParticleBuoyancy(float mxDepth, float vol, float watHeight, float liqDensity = 1000.0f) : maxDepth(mxDepth), volume(vol), waterHeight(watHeight), liquidDensity(liqDensity) {};
	virtual void updateForce(Particle* particle, float t);
	inline void changeVol(float v) { volume = v; };
};