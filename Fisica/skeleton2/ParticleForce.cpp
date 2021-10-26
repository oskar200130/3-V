#include "ParticleForce.h"

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg){
	ParticleForceRegistration a;
	a.particle = particle;
	a.fg = fg;
	registrations.push_back(a);
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg){
	int i = 0;
	for (auto a : registrations) {
		if (a.particle == particle && a.fg == fg) {
			registrations.erase(registrations.begin()+i);
			return;
		}
		i++;
	}
}

void ParticleForceRegistry::clear(){
	registrations.clear();
}

void ParticleForceRegistry::updateForces(float t){
	for (auto it = registrations.begin(); it != registrations.end(); ++it)
	{
		it->fg->updateForce(it->particle, t);
	}
}
