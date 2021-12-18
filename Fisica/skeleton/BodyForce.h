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
	RenderItem* renderItem = nullptr;
	bool activated;
public:
	PxTransform* pos = nullptr;
	BodyWind(const Vector3 wind, float rad = 40.0) : w(wind), radius(rad), activated(false) {};
	virtual void updateForce(SolidBody* particle, float t);
	void activateBodWind(Vector3 p);
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

public:
	BodyExplosion(Vector3 x, float rad) : g(x), radius(rad), renderItem(nullptr), activated(false), lastIni(0.0), duration(0.05) {};
	~BodyExplosion() { deactivateExplosion(); };
	virtual void updateForce(SolidBody* particle, float t);
	void update(float t);
	void activateExplosion(Vector3 p = Vector3(-78, -9, 31));
	void deactivateExplosion();
	inline void setPosition(Vector3 nP) { pos->p = nP; };
};
//--------------------------------------------------------------------------------------------

class BodyBuoyancy : public BodyForceGenerator {
private:
	float maxDepth;
	float volume;

	float waterHeight;

	float liquidDensity;

public:
	BodyBuoyancy(float mxDepth, float vol, float watHeight, float liqDensity = 1000.0f) : maxDepth(mxDepth), volume(vol), waterHeight(watHeight), liquidDensity(liqDensity) {};
	virtual void updateForce(SolidBody* particle, float t);
	inline void changeVol(float v) { volume = v; maxDepth = v; };
};