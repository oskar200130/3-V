#pragma once
#include "SolidBody.h"

class BodyForceGenerator
{
public:
	// Overload to provide functionality
	virtual void updateForce(SolidBody* body, float t) = 0;
};
//--------------------------------------------------------------------------------------------

class BodyWind : public BodyForceGenerator
{
	Vector3 w;
	float radius;
	PxTransform* pos = nullptr;
	RenderItem* renderItem = nullptr;
	bool activated;
public:
	BodyWind(const Vector3 wind) : w(wind), radius(20.0), activated(false) {};
	virtual void updateForce(SolidBody* particle, float t);
	void activateBodWind();
	void deactivateBodWind();
};
//--------------------------------------------------------------------------------------------

class BodyTorque : public BodyForceGenerator
{
	Vector3 torque;
	float radius;
	PxTransform* pos = nullptr;
	RenderItem* renderItem = nullptr;
	bool activated;
public:
	BodyTorque(const Vector3 _torque) : torque(_torque), radius(20.0), activated(false) {};
	~BodyTorque() { deactivateTorque(); };
	virtual void updateForce(SolidBody* particle, float t);
	void activateTorque();
	void deactivateTorque();
};
//--------------------------------------------------------------------------------------------

class BodyExplosion : public BodyForceGenerator
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
	BodyExplosion(Vector3 x, float rad) : g(x), radius(rad), renderItem(nullptr), activated(false), lastIni(0.0), duration(0.25) {};
	~BodyExplosion() { deactivateExplosion(); };
	virtual void updateForce(SolidBody* particle, float t);
	void update(float t);
	void activateExplosion();
};