#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;
using namespace std;

class SolidBody {
public:
	~SolidBody();
	PxRigidDynamic* rigid = nullptr;
	bool isNew;
	float life;
	RenderItem* renderItem = nullptr;
	PxVec3 force;
	PxVec3 torque;

	Vector3 vel;
	Vector3 a;
	Vector4 color;
	float damping;
	float in_mas;

	bool active = true;
};

//----------------------------------------------------------------------

class BodySystem{
public:
	BodySystem(PxPhysics* _gPhysics, PxScene* _gScene, PxTransform pSet, float stepSet = 1.5, bool _colorR = true, float lifeSet = 20, float sizeSet = 1,
		int max = 10, Vector4 colorSet = { 1, 0, 0, 1.0 }) : gPhysics(_gPhysics), gScene(_gScene), p(pSet), step(stepSet), colorR(_colorR), life(lifeSet),
		size(sizeSet), maxParticles(max), color(colorSet), numParticles(0), timeSinceAdding(0) {};
	~BodySystem();
	SolidBody* addBody();
	void integrate(float t);
	vector<SolidBody*> bodies;
	inline int getNumPar() { return numParticles; };
	inline int getMaxPar() { return maxParticles; };
	inline float getTimeSinceAdding() { return timeSinceAdding; };
	inline float getStep() { return step; };
private:
	PxPhysics* gPhysics;
	PxScene* gScene;
	PxTransform p;
	Vector4 color;
	bool colorR;
	float step;
	float size;
	int maxParticles;
	int numParticles;
	float life;
	float timeSinceAdding;
};