#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Particle.h"

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

Particle* font = nullptr;
std::vector<FireWork*> fireworks;
FireWorkRule* rules[3];

void initFireworkRules() {
	rules[0] = new FireWorkRule();
	rules[0]->setParameters(FireWorkType::explosion, 1.3, 2.7, Vector3(-1, 12, -1), Vector3(-9, 17, -8), 0.999);
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
}

void fireWorksUpdate(float t) {
	vector<FireWork*> add;
	for (auto it = fireworks.begin(); it != fireworks.end(); ++it) {
		FireWork* firework = *it;
		if (firework->isActive() && firework->update(t)) {
			FireWorkRule* rule = rules[(int)firework->type];
			firework->setInactive();
			if (firework->expAge < rule->payloads[1].count) {
				for (auto itP = rule->payloads.begin(); itP != rule->payloads.end(); ++itP) {
					Payload payload = (*itP);

					FireWork* newF = new FireWork(payload.type);
					newF->expAge = firework->expAge + 1;
					rule->create(newF, { 0, 0, 0 }, firework);
					add.push_back(newF);
				}
			}
		}
	}
	for (FireWork* f : fireworks) {
		if (!f->isActive()) {
			delete f;
			fireworks.erase(std::remove(fireworks.begin(), fireworks.end(), f), fireworks.end());
		}
	}
	for (auto i = add.begin(); i != add.end(); ++i)
		fireworks.push_back(*i);
}

void initObjects() {
	PxTransform p = GetCamera()->getTransform();
	p.p += Vector3(-200, 10, -200);
	int max = 200;
	int min = 150;
	Vector3 dir = Vector3{ (float)(rand() % max + min) / 100,  (float)(rand() % max + min) / 100, (float)(rand() % max + min) / 100 };
	font = new Particle(p, dir * 50, { 0,-10,0 }, { 1,1,0,1 }, 0.7);
}
// Initialize physics engine
void initPhysics(bool interactive)
{
	initFireworkRules();
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
	//initObjects();
	gScene->simulate(t);
	gScene->fetchResults(true);
	if (font != nullptr) font->integrate(t);
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
		//case 'B': break;
		//case ' ':	break;
	case ' ':
	{
		initObjects();
		break;
	}
	case 'C':
	{
		FireWork* f = new FireWork(FireWorkType::explosion);
		rules[0]->create(f, position);
		fireworks.push_back(f);
		break;
	}
	case 'V':
	{
		FireWork* f = new FireWork(FireWorkType::shoot);
		position.x += 200;
		position.z += 200;
		rules[1]->create(f, position);
		fireworks.push_back(f);
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
