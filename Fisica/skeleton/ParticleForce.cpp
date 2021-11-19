#include "ParticleForce.h"

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg) {
	ParticleForceRegistration a;
	a.particle = particle;
	a.fg = fg;
	registrations.push_back(a);
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg) {
	int i = 0;
	for (auto a : registrations) {
		if (a.particle == particle && a.fg == fg) {
			registrations.erase(registrations.begin() + i);
			return;
		}
		i++;
	}
}

void ParticleForceRegistry::removePartInstance(Particle* particle) {
	for (int i = 0; i < registrations.size(); ++i) {
		if (registrations[i].particle == particle) {
			registrations.erase(registrations.begin() + i);
			i--;
		}
	}
}

void ParticleForceRegistry::clear() {
	registrations.clear();
}

void ParticleForceRegistry::updateForces(float t) {
	for (auto it = registrations.begin(); it != registrations.end(); ++it)
	{
		it->fg->updateForce(it->particle, t);
	}
}

//--------------------------------------------------------------------------------------------

void ParticleGravity::updateForce(Particle* particle, float t) {
	if (particle->getMass() == 1) return;
	particle->addForce(g * (1 / particle->getMass()));
}

//-------------------------------------------------------------------------------------------

void Wind::updateForce(Particle* particle, float t) {
	if (activated && (particle->getPosition().p - renderItem->transform->p).magnitude() < radius) {
		particle->addForce(g);
	}
}

void Wind::activateWind() {
	if (!activated) {
		pos = new PxTransform(0, 0, 0);

		pos->p = {
				GetCamera()->getTransform().p.x + (GetCamera()->getDir().x * 200),
				GetCamera()->getTransform().p.y + (GetCamera()->getDir().y * 200),
				GetCamera()->getTransform().p.z + (GetCamera()->getDir().z * 200) };

		Vector4 color = { 0.0, 0.0, 1.0, 0.0 };
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(radius)), pos, color);
		activated = true;
	}
}

void Wind::deactivateWind() {
	if (activated) {
		DeregisterRenderItem(renderItem);
		delete renderItem;
		delete pos;
		renderItem = nullptr;
		activated = false;
	}
}

//-------------------------------------------------------------------------------------------

void Explosion::updateForce(Particle* particle, float t) {
	if (activated && (particle->getPosition().p - renderItem->transform->p).magnitude() < radius) {
		Vector3 force = (particle->getPosition().p - renderItem->transform->p).getNormalized() * g.magnitude();
		particle->addForce(g);
	}
}

void Explosion::update(float t) {
	if (activated) {
		lastIni += t;
		if (lastIni >= duration) {
			deactivateExplosion();
			lastIni = 0;
		}
	}
}

void Explosion::activateExplosion() {
	if (!activated) {
		pos = new PxTransform(0, 0, 0);

		pos->p = {
				GetCamera()->getTransform().p.x + (GetCamera()->getDir().x * 200),
				GetCamera()->getTransform().p.y + (GetCamera()->getDir().y * 200),
				GetCamera()->getTransform().p.z + (GetCamera()->getDir().z * 200) };

		Vector4 color = { 1.0, 0.0, 0.0, 0.0 };
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(radius)), pos, color);
		activated = true;
	}
}

void Explosion::deactivateExplosion() {
	if (activated) {
		DeregisterRenderItem(renderItem);
		delete renderItem;
		delete pos;
		renderItem = nullptr;
		activated = false;
	}
}

//-------------------------------------------------------------------------------------------

void ParticleSpring::updateForce(Particle* particle, float t) {
	Vector3 f = particle->getPosition().p;
	f -= other->getPosition().p;

	float l = f.normalize();

	float deltaL = l - restLenght;
	float forceMagnitude = -k * deltaL;
	f *= forceMagnitude;
	particle->addForce(f);
}

//-------------------------------------------------------------------------------------------

void ParticleBuoyancy::updateForce(Particle* particle, float t) {
	float depth;
	depth = particle->getPosition().p.y;
	Vector3 f(0.0f, 0.0f, 0.0f);

	if (depth > (waterHeight + maxDepth)) {
		particle->setColor({ 1,0,0,1 });
		return;
	}

	if (depth < (waterHeight - maxDepth)) {
		particle->setColor({ 1,0,1,1 });
		f.y = liquidDensity * volume;
	}
	else {
		float depthExt = waterHeight + maxDepth;
		float volFactor = (depthExt - depth) / (2 * maxDepth);
		f.y = liquidDensity * volume * volFactor;
		particle->setColor({ 0.5,0,1,1 });
	}
	particle->addForce(f);
}
