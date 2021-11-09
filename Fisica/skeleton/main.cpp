#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "SceneManager.h"

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

SceneManager* sceneMng;

// Initialize physics engine
void initPhysics(bool interactive)
{
	sceneMng = new SceneManager(0);

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

	sceneMng->update(t);
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
	sceneMng->keyPressed(key, camera);
	/*PX_UNUSED(camera);
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
	}*/
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
	delete sceneMng;
	return 0;
}
