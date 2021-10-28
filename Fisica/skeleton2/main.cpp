#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Particle.h"
#include "ParticleForce.h"

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;

std::vector<FireWork*> fireworks;
FireWorkRule* rules[4];

ParticleForceRegistry* forceReg;
ParticleForceGenerator* pForces[4];


void initFireworkRules() {
	rules[0] = new FireWorkRule();
	rules[0]->setParameters(FireWorkType::explosion, 1.3, 2.7, Vector3(-1, 6, -1), Vector3(-9, 9, -8), 0.999);
	for (int i = 0; i < 15; i++)
		rules[0]->payloads.push_back(Payload(FireWorkType::explosion, 3));

	rules[1] = new FireWorkRule();
	rules[1]->setParameters(FireWorkType::shoot, 0.4, 1.0, Vector3(-350, 0, -350), Vector3(-400, 0, -400), 0.999);
	for (int i = 0; i < 20; i++)
		rules[1]->payloads.push_back(Payload(FireWorkType::shoot, 2));

	rules[2] = new FireWorkRule();
	rules[2]->setParameters(FireWorkType::fireball, 2.7, 2.8, Vector3(0, 80, 0), Vector3(0, 90, 0), 0.999);
	for (int i = 0; i < 10; i++)
		rules[2]->payloads.push_back(Payload(FireWorkType::fireball, 2));

	rules[3] = new FireWorkRule();
	rules[3]->setParameters(FireWorkType::particle, 6.0, 7.0, Vector3(0, 10, 0), Vector3(0, 11, 0), 0.999);
}

void initForces() {
	forceReg = new ParticleForceRegistry();

	pForces[0] = new ParticleGravity(Vector3(0.0, -10.0, 0.0));
	pForces[1] = new ParticleGravity(Vector3(0.0, -2.5, 0.0));
	pForces[2] = new Wind(Vector3(-10.0, 8.0, 2.0), 50.0);
	pForces[3] = new Explosion(Vector3(160.0, 160.0, 160.0), 80.0);
}

void fireWorksUpdate(float t) {
	forceReg->updateForces(t);
	vector<FireWork*> add;
	for (auto it = fireworks.begin(); it != fireworks.end(); ++it) {
		FireWork* firework = *it;
		if (firework->isActive() && firework->update(t)) {
			FireWorkRule* rule = rules[(int)firework->type];
			firework->setInactive();
			if (rule->payloads.size() > 0 && firework->expAge < rule->payloads[1].count) {
				for (auto itP = rule->payloads.begin(); itP != rule->payloads.end(); ++itP) {
					Payload payload = (*itP);

					FireWork* newF = new FireWork(payload.type);
					newF->expAge = firework->expAge + 1;
					rule->create(newF, { 0, 0, 0 }, firework);
					add.push_back(newF);
					forceReg->add(newF, pForces[0]);
					forceReg->add(newF, pForces[2]);
					forceReg->add(newF, pForces[3]);
				}
			}
		}
	}
	for (FireWork* f : fireworks) {
		if (!f->isActive()) {
			forceReg->removePartInstance(f);
			delete f;
			fireworks.erase(std::remove(fireworks.begin(), fireworks.end(), f), fireworks.end());
		}
	}
	for (auto i = add.begin(); i != add.end(); ++i)
		fireworks.push_back(*i);

	static_cast<Explosion*>(pForces[3])->update(t);
}

// Initialize physics engine
void initPhysics(bool interactive)
{
	initFireworkRules();
	initForces();
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	// ------------------------------------------------------
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	gScene->simulate(t);
	gScene->fetchResults(true);

	fireWorksUpdate(t);
}
// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	Vector3 position = {
			GetCamera()->getTransform().p.x + GetCamera()->getDir().x * 400,
			GetCamera()->getTransform().p.y + GetCamera()->getDir().y * 400,
			GetCamera()->getTransform().p.z + GetCamera()->getDir().z * 400 };
	switch (toupper(key))
	{
	case ' ':
	{
		FireWork* f = new FireWork(FireWorkType::particle);
		PxTransform pos = GetCamera()->getTransform();
		rules[3]->create(f, pos.p);
		fireworks.push_back(f);
		forceReg->add(f, pForces[0]);
		forceReg->add(f, pForces[2]);
		forceReg->add(f, pForces[3]);
		break;
	}
	case 'M':
	{
		FireWork* f = new FireWork(FireWorkType::particle);
		PxTransform pos = GetCamera()->getTransform();
		rules[3]->create(f, pos.p);
		fireworks.push_back(f);
		forceReg->add(f, pForces[1]);
		forceReg->add(f, pForces[2]);
		forceReg->add(f, pForces[3]);
		break;
	}
	case 'C':
	{
		FireWork* f = new FireWork(FireWorkType::explosion);
		rules[0]->create(f, position);
		fireworks.push_back(f);
		forceReg->add(f, pForces[0]);
		forceReg->add(f, pForces[2]);
		forceReg->add(f, pForces[3]);
		break;
	}
	case 'V':
	{
		FireWork* f = new FireWork(FireWorkType::shoot);
		position.x += 200;
		position.z += 200;
		rules[1]->create(f, position);
		fireworks.push_back(f);
		forceReg->add(f, pForces[0]);
		forceReg->add(f, pForces[2]);
		forceReg->add(f, pForces[3]);
		break;
	}
	case 'B':
	{
		FireWork* f = new FireWork(FireWorkType::fireball);
		position.x -= 300;
		position.y -= 300;
		position.z -= 300;
		rules[2]->create(f, position);
		fireworks.push_back(f);
		forceReg->add(f, pForces[0]);
		forceReg->add(f, pForces[2]);
		forceReg->add(f, pForces[3]);
		break;
	}
	case 'E':
	{
		static_cast<Wind*>(pForces[2])->activateWind();
		break;
	}
	case 'R':
	{
		static_cast<Wind*>(pForces[2])->deactivateWind();
		break;
	}
	case 'T':
	{
		static_cast<Explosion*>(pForces[3])->activateExplosion();
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif
	for (int i = 0; i < fireworks.size(); i++) delete fireworks.front();
	return 0;
}
