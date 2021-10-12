#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <random>

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

public:
	Particle() :pos(0, 0, 0), vel(0), a(0), color({ 0,0,0,1 }), damping(0), in_mas(0) { renderItem = nullptr; };
	Particle(PxTransform p, Vector3 v, Vector3 ac, Vector4 c = { 1,1,1,1 }, float dam = 0.999, float in_m = 5.0) :pos(p), vel(v), a(ac), color(c), damping(dam), in_mas(in_m) {
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(2.0)), &pos, color);
	};
	void init(PxTransform p, Vector3 v, Vector3 ac, Vector4 c = { 1,1,1,1 }, float dam = 0.999, float in_m = 5.0) {
		pos = p; 
		vel = v; 
		a = ac; 
		color = c; 
		damping = dam; 
		in_mas = in_m;
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(2.0)), &pos, color);
	};
	~Particle();
	void integrate(double t);

	inline float getY() const { return pos.p.y; };
	inline PxTransform getPosition() const { return pos; };
	inline Vector3 getVel() const { return vel; };
	inline bool isActive() const { return active; };

	inline void setInactive() { active = false; };
	inline void setPosition(PxTransform p) { pos = p; };
	inline void setVel(Vector3 v) { vel = v; };
};

enum class FireWorkType { fire };

class FireWork : public Particle {
private:
	FireWorkType type;
	float age;
public:
	FireWork(FireWorkType t) : Particle(), type(t), age(0) {};
	bool update(float t) {
		integrate(t);

		age -= t;
		return age < 0;
	}
	inline void setAge(int a) { age = a; };
};

struct FireWorkRule {
	FireWorkType type;

	float minAge;
	float maxAge;

	int count;
	int children;
	float damping;
	Vector4 color;

	Vector3 minVelocity;
	Vector3 maxVelocity;

	std::vector<FireWork*> fires;

	void set(FireWorkType t, int c, int ch) {
		type = t;
		count = c;
		children = ch;
	};

	void create(Vector3 pos, const FireWork* parent = NULL) {
		FireWork* firework = new FireWork(type);
		fires.push_back(firework);
		firework->setAge(rand() % static_cast<int>(maxAge + minAge));

		Vector3 vel{ 0,0,0 };
		if (parent != NULL) {
			firework->setPosition(parent->getPosition());
			vel += parent->getVel();

			vel += Vector3(rand() % static_cast<int>(maxVelocity.x + minVelocity.x), 
				rand() % static_cast<int>(maxVelocity.y + minVelocity.y), rand() % static_cast<int>(maxVelocity.z + minVelocity.z));
			firework->setVel(vel);
		}
		else {
			Vector3 start = pos;
			int x = rand() % 2;
			start.x = 5.0f * x;
			firework->init(PxTransform(start), vel, Vector3(0, -10, 0), color, damping, 1);
		}
	}

	void update(float t) {
		for (auto fireW = fires.begin(); fireW != fires.end(); fireW++) {
			FireWork* f = *fireW;
			if (f->update(t)) {
				for (int i = 0; i < children; i++) 
					create(f->getPosition().p,f);
				delete f;
			}
		}
	}
};

