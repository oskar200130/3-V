#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <random>
#include <math.h>

using namespace physx;
using namespace std;
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
	// Accumulated force
	Vector3 force;

public:
	Particle() :pos(0, 0, 0), vel(0), a(0), color({ 0,0,0,1 }), damping(0), in_mas(0.1) { };
	Particle(PxTransform p, Vector3 v, Vector3 ac, Vector4 c = { 1,1,1,1 }, float dam = 0.999, float in_m = 5.0) :pos(p), vel(v), a(ac), color(c), damping(dam), in_mas(in_m) {
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(2.0)), &pos, color);
	};
	void init(Vector3 p, Vector3 v, Vector3 ac, Vector4 c = { 1,1,1,1 }, float dam = 0.999, float in_m = 5.0, float size = 2.0);
	~Particle();
	void integrate(double t);

	// Clears accumulated force
	void clearForce();
	// Add force to apply in next integration only
	void addForce(const Vector3& f);

	inline PxTransform getPosition() const { return pos; };
	inline int getMass() const { return in_mas; };
	inline Vector3 getVel() const { return vel; };
	inline bool isActive() const { return active; };

	inline void setInactive() { active = false; };
};

//--------------------------------------------------------------------------------------------

enum class FireWorkType { explosion, shoot, fireball };

class FireWork : public Particle {
public:
	FireWorkType type;
	float age;
	int expAge = 0;

	FireWork(FireWorkType t) : Particle(), type(t), age(0) {};
	~FireWork() {};
	bool update(float t);
};

//--------------------------------------------------------------------------------------------

struct Payload {
	FireWorkType type;
	int count;

	Payload(FireWorkType t, int c) {
		type = t;
		count = c;
	};
};

//--------------------------------------------------------------------------------------------

struct FireWorkRule {
	FireWorkType type;

	int minAge;
	int maxAge;

	float damping;

	float numH = 0;

	Vector3 minVelocity;
	Vector3 maxVelocity;
	Vector4 color;

	std::vector<Payload> payloads;
	void configType(FireWork* fir, Vector3& vel, float& size, Vector4& color);

	void setParameters(FireWorkType t, float minA, float maxA, Vector3 minV, Vector3 maxV, float dam) {
		type = t;
		minAge = minA * 100;
		maxAge = maxA * 100;
		minVelocity = minV * 10;
		maxVelocity = maxV * 10;
		damping = dam;
		color = { 1,1,1,1 };
	};

	void create(FireWork* fir, Vector3 pos, const FireWork* parent = NULL);
};