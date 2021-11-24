#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;

class SolidBody {
public:
	PxRigidDynamic* rigid = nullptr;
	bool isNew;
	float life;
	RenderItem* renderItem = nullptr;
	PxVec3 force;
	PxVec3 torque;
};

//----------------------------------------------------------------------

class BodySystem {
public:
	BodySystem(PxPhysics* _gPhysics, PxScene* _gScene, PxTransform pSet,
		float stepSet = 1.5, bool colorR = true, float lifeSet = 20, float sizeSet = 1,
		int max = 10, Vector4 colorSet = { 1, 0, 0, 1.0 });
	~BodySystem();
	void addBody();
	void integrate(float t);
	vector<SolidBody*> bodies;
};