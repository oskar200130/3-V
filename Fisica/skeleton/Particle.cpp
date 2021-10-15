#include "Particle.h"

Particle::~Particle() {
	RegisterRenderItem(renderItem);
	renderItem = nullptr;
}

void Particle::update(double t) {

	if (in_mas <= 0.0f) return;
	// Update position
	pos.p += vel * t;
	// Update linear velocity
	vel += a * t;
	// Impose drag (damping)
	vel *= powf(damping, t);

}
