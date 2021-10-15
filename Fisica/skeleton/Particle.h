#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;
class Particle
{
private:
	PxTransform pos;
	Vector3 vel;
	Vector3 a;
	Vector4 color;
	float damping;
	float in_mas;

	bool active = true;

	RenderItem* renderItem;

public:
	Particle() :pos(0, 0, 0), vel(0), a(0), color({0,0,0,1}), damping(0), in_mas(0) { renderItem = nullptr; };
	Particle(PxTransform p, Vector3 v, Vector3 ac, Vector4 c = { 1,1,1,1}, float dam = 0.999, float in_m = 5.0) :pos(p), vel(v), a(ac), color(c), damping(dam), in_mas(in_m) {
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(2.0)), &pos, color);
	};
	~Particle();
	inline float getY() const { return pos.p.y; };
	void update(double t);
	inline void setInactive() { active = false; };
	inline bool isActive() const { return active; };
};

