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
public:
	BodyWind(const Vector3 wind) : w(wind) {};
	virtual void updateForce(SolidBody* particle, float t);
};
//--------------------------------------------------------------------------------------------

class BodyTorque : public BodyForceGenerator
{
	Vector3 torque;
public:
	BodyTorque(const Vector3 _torque) : torque(_torque) {};
	virtual void updateForce(SolidBody* particle, float t);
};