#include "SolidBody.h"

BodySystem::~BodySystem(){
	for (int i = bodies.size() - 1; i >= 0; i--) {
		delete bodies.at(i);
		bodies.erase(bodies.begin() + i);
	}
	gPhysics = nullptr;
	gScene = nullptr;
}

void BodySystem::addBody() {
	if (colorR) {
		color = Vector4(float((rand() % 10) / 10.0), float((rand() % 10) / 10.0), float((rand() % 10) / 10.0), 1.0);
	}
	SolidBody* body = nullptr;
	body = new SolidBody;
	//rigid
	PxRigidDynamic* rigid = gPhysics->createRigidDynamic(p);
	// shape
	PxShape* shape = CreateShape(PxBoxGeometry(size, size, size));
	rigid->attachShape(*shape);
	//Cinetica
	Vector3 vel = { -5.0f + rand() / (RAND_MAX / (10.0f)), -5.0f + rand() / (RAND_MAX / (10.0f)), -5.0f + rand() / (RAND_MAX / (10.0f)) };
	rigid->setLinearVelocity(vel);
	rigid->setLinearDamping(0.0);
	rigid->setAngularVelocity({ 0,2,0 });
	rigid->setAngularDamping(0.05);
	//Dinámica
	rigid->setMass(4);
	rigid->setMassSpaceInertiaTensor(PxVec3(0.f, 0.0f, 1.0f));
	gScene->addActor(*rigid);
	// complete body struct
	body->rigid = rigid;
	body->life = life;
	body->force = { 0.0f, 0.0f, 0.0f };
	body->torque = { 0.0f, 0.0f, 0.0f };
	body->renderItem = new RenderItem(shape, rigid, color);
	bodies.push_back(body);
	timeSinceAdding = 0;
	numParticles++;
}

void BodySystem::integrate(float t) {
	timeSinceAdding += t;
	if (numParticles < maxParticles && timeSinceAdding > step) {
		addBody();
	}
	for (int i = bodies.size() - 1; i >= 0; i--) {
		bodies.at(i)->rigid->addForce(bodies.at(i)->force, PxForceMode::eFORCE);
		bodies.at(i)->force = { 0.0f, 0.0f, 0.0f };
		bodies.at(i)->rigid->addTorque(bodies.at(i)->torque);
		bodies.at(i)->torque = { 0.0f, 0.0f, 0.0f };
		bodies.at(i)->life -= t;
		if (bodies.at(i)->life < 0) {
			delete bodies.at(i);
			bodies.erase(bodies.begin() + i);
		}
	}
}

SolidBody::~SolidBody(){
	DeregisterRenderItem(renderItem);
	delete renderItem;
	renderItem = nullptr;
}
