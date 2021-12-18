#include "SolidBody.h"
#include "SceneManager.h"

BodySystem::~BodySystem() {
	for (int i = bodies.size() - 1; i >= 0; i--) {
		delete bodies.at(i);
		bodies.erase(bodies.begin() + i);
	}
	gPhysics = nullptr;
	gScene = nullptr;
}

SolidBody* BodySystem::addBody(PxTransform pos, bool posP, bool velR, Vector3 vel, Vector3 dim) {
	if (colorR) {
		color = Vector4(1.0, 0.0, 0.0, 1.0);
	}
	SolidBody* body;
	body = new SolidBody;
	//rigid
	if (posP)
		p = pos;

	PxRigidDynamic* rigid = gPhysics->createRigidDynamic(p);

	// shape
	PxShape* shape;
	if (dim.x > 0)
		shape = CreateShape(PxBoxGeometry(dim.x, dim.y, dim.z));
	else {
		float x = (rand() % 9 + 1);
		shape = CreateShape(PxBoxGeometry(PxVec3(x, x, x)));
	}
	rigid->attachShape(*shape);

	//Cinetica
	if (velR)
		vel = { 0, 0, 0 };
	rigid->setLinearVelocity(vel);
	rigid->setLinearDamping(0.0);
	rigid->setAngularVelocity({ 0,0,0 });
	rigid->setAngularDamping(0.05);

	//Din�mica
	rigid->setMass(rand() % 50);
	rigid->setMassSpaceInertiaTensor(PxVec3(rand() % 6, rand() % 6, rand() % 6));
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
	return body;
}

void BodySystem::integrate(float t) {
	timeSinceAdding += t;
	for (int i = bodies.size() - 1; i >= 0; i--) {
		bodies.at(i)->rigid->addForce(bodies.at(i)->force, PxForceMode::eFORCE);
		bodies.at(i)->force = { 0.0f, 0.0f, 0.0f };
		bodies.at(i)->rigid->addTorque(bodies.at(i)->torque);
		bodies.at(i)->torque = { 0.0f, 0.0f, 0.0f };
		bodies.at(i)->life -= t;
		if (bodies.at(i)->life != -8 && bodies.at(i)->life < 0) {
			bodies.at(i)->active = false;
			numParticles--;
		}
	}
}

SolidBody::~SolidBody() {
	DeregisterRenderItem(renderItem);
	delete renderItem;
	renderItem = nullptr;
}

//---------------------------------------------------------------------------------

SoloBodySystem::~SoloBodySystem() {
	delete body;
	body = nullptr;
	gPhysics = nullptr;
	gScene = nullptr;
}

void SoloBodySystem::integrate(float t) {
	body->rigid->setLinearVelocity(body->vel + body->rigid->getLinearVelocity());
	body->rigid->addForce(body->force, PxForceMode::eFORCE);
	body->force = { 0.0f, 0.0f, 0.0f };
	body->rigid->addTorque(body->torque);
	body->torque = { 0.0f, 0.0f, 0.0f };
}