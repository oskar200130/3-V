#include "Particle.h"

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
	renderItem = nullptr;
}

void Particle::integrate(double t) {

	if (in_mas <= 0.0f) return;
	// Update position
	pos.p += vel * t;
	// Update linear velocity
	vel += a * t;
	// Impose drag (damping)
	vel *= powf(damping, t);

}
