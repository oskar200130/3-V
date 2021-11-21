#pragma once
#include "Particle.h"
#include "ParticleForce.h"

class Scene {
public:
	Scene() { initForces(); };
	virtual ~Scene();
	virtual void update(float t) { forceReg->updateForces(t); };
	virtual void keyPressed(unsigned char key, const PxTransform& camera) {};
protected:
	ParticleForceRegistry* forceReg;
	ParticleForceGenerator* pForces[4];

	void initForces();
};

//-------------------------------------------------------

class FireworkScene : public Scene {
public:
	FireworkScene();
	virtual ~FireworkScene();

private:

	void initFireworkRules();
	void fireWorksUpdate(float t);

protected:
	std::vector<FireWork*> fireworks;
	FireWorkRule* rules[4];

	virtual void update(float t);
	void keyPressed(unsigned char key, const PxTransform& camera);
};

//-------------------------------------------------------

class SpringScene : public Scene {
public:
	SpringScene();
	virtual ~SpringScene();
private:
	Particle* p1, *p2;
	ParticleSpring* sp1, * sp2;
	float k;
protected:
	virtual void update(float t);
	void keyPressed(unsigned char key, const PxTransform& camera);
	void changeAnchor();
};

//-------------------------------------------------------

class BuoyancyScene : public Scene {
public:
	BuoyancyScene();
	virtual ~BuoyancyScene();
private:
	Particle* p, * floor;
	ParticleBuoyancy* by;
	float vol, mass;
protected:
	virtual void update(float t);
	void keyPressed(unsigned char key, const PxTransform& camera);
};
//-------------------------------------------------------

class RigidSolidScene : public Scene {
public:
	RigidSolidScene(PxPhysics* _gPhysics, PxScene* _gScene);
	virtual ~RigidSolidScene();
private:
	PxPhysics* gPhysics;
	PxScene* gScene;
	BodySystem* bodySys;
};
//-------------------------------------------------------

class SceneManager {
private:
	Scene* actualScene;
	int numScene;
public:
	SceneManager(int scene);
	void changeScene(int scene);
	void sceneSelector(int scene);
	~SceneManager();
	void update(float t) { actualScene->update(t); };
	void keyPressed(unsigned char key, const PxTransform& camera) { actualScene->keyPressed(key, camera); };
};