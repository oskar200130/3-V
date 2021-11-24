#include "SolidBody.h"

void BodySystem::addBody() {
	if (colorR) {
		color = { float((rand() % 10) / 10.0), float((rand() % 10) / 10.0), float((rand() % 10) / 10.0), 1.0 };
	}
	SolidBody* body = nullptr;
	body = new SolidBody;
	//rigid
	PxRigidDynamic* rigid = gPhysics->createRigidDynamic(p);
	// shape
	PxShape* shape = CreateShape(PxBoxGeometry(size, size, size));
	rigid - attachShape(*shape);
	1 / Cinetica
		Vector3 vel = { -5.0f + rand() / (RAND_MAX / (10.0f)), -5.0f + rand() / (RAND_MAX / (10.0f)), -5.0f + rand() / (RAND_MAX / (10.0f)) };
	rigid->setLinearVelocity(vel);
	rigid->setLinearDamping(0.0);
	rigid->setAngularVelocity({ 0,2,0 });
	rigid->setAngularDamping(0.05);
	//Dinámica
	rigid->setMass(4);
	rigid->setMassSpaceInertiaTensor(PxVec3(0.f, o.f, 1.f));
	gScene->addActor(*rigid);
	// complete body struct
	body->rigid = rigid;
	body->isnew = true;
	body->life = life;
	body->force = { 0.0f, 0.0f, 0.0f };
	body->torque = { 0.0f, 0.0f, 0.0f };
	body->renderItem = new RenderItem(shape, rigid, color);
	bodies.push_back(body);
	timeSinceAdding = 0;
	numParticles++;
}