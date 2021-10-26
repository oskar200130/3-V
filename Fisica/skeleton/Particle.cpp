#include "Particle.h"
#include <iostream>

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
	renderItem = nullptr;
}
void Particle::init(Vector3 p, Vector3 v, Vector3 ac, Vector4 c, float dam, float in_m, float size) {
	pos.p = p;
	vel = v;
	a = ac;
	color = c;
	damping = dam;
	in_mas = in_m;
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(size)), &pos, color);
};

void Particle::integrate(double t) {

	if (in_mas <= 0.0f) return;
	// Update position
	pos.p += vel * t;
	// Update linear velocity
	vel += a * t;
	// Impose drag (damping)
	vel *= powf(damping, t);

}

//--------------------------------------------------------------------------------------------

bool FireWork::update(float t) {
	integrate(t);

	age -= t;
	return age < 0;
}

//--------------------------------------------------------------------------------------------

void FireWorkRule::configType(FireWork* fir, Vector3& vel, float& size, Vector4& color) {
	float x, y, z, div = 5.0;
	switch (type)
	{
	case FireWorkType::explosion:
		x = (rand() % 101 / 100.0);

		color = Vector4(x, x, x, 1);
		size = fir->expAge + 1.0f;

		vel += Vector3((rand() % (int)(maxVelocity.x - minVelocity.x) + minVelocity.x) / 10.0f, (rand() % (int)(maxVelocity.y - minVelocity.y) + minVelocity.y) / 10.0f,
			(rand() % (int)(maxVelocity.z - minVelocity.z) + minVelocity.z) / 10.0f);
		break;
	case FireWorkType::shoot:
		y = (rand() % 3) * 0.33;

		color = Vector4(1, y, 0, 1);
		size = fir->expAge + 2.0f;
		y = 0;

		if (fir->expAge != 0) {
			y = (rand() % 101 - 50) / 4;
			div *= 4;
		}
		vel = Vector3((rand() % (int)(maxVelocity.x - minVelocity.x) + minVelocity.x) / div, y,
			(rand() % (int)(maxVelocity.z - minVelocity.z) + minVelocity.z) / div);
		break;
	case FireWorkType::fireball:
		x = (rand() % 101 / 100.0);
		y = (rand() % 101 / 100.0);
		z = (rand() % 101 / 100.0);
		color = Vector4(x, y, z, 1);
		size = fir->expAge + 0.5f;

		if (numH == 0)
			vel += Vector3(0, (rand() % (int)(maxVelocity.y - minVelocity.y) + minVelocity.y) / 10.0, 0);

		numH++;
		if (numH >= 11) {
			numH -= 10;
		}
		div *= 6;

		vel += Vector3(-cos(360.0f / 9.0f * (numH)), sin(360.0f / 9.0f * (numH)), cos(360.0f / 9.0f * (numH)))*div;
		break;
	}
}

void FireWorkRule::create(FireWork* fir, Vector3 pos, const FireWork* parent) {
	fir->type = type;
	fir->age = (rand() % (maxAge - minAge) + minAge) / 100.0f;

	Vector3 vel = { 0,0,0 };
	if (parent != NULL) {
		pos = parent->getPosition().p;
		vel = parent->getVel();
	}

	float s = 0.0;
	configType(fir, vel, s, color);
	fir->init(pos, vel, { 0, -10, 0 }, color, damping, 0.1, 3.0f / s);
}