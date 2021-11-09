#pragma once
#include "Particle.h"
#include "ParticleForce.h"

class Scene {
public:
	Scene() { initForces(); };
	~Scene() { delete forceReg; delete pForces; };
	virtual void update(float t) {};
	virtual void keyPressed(unsigned char key, const PxTransform& camera) {};
protected:
	ParticleForceRegistry* forceReg;
	ParticleForceGenerator* pForces[4];

	void initForces();
};

//-------------------------------------------------------

class FireworkScene : public Scene{
public:
	FireworkScene();
	~FireworkScene();

private:
	std::vector<FireWork*> fireworks;
	FireWorkRule* rules[4];

	void initFireworkRules();
	void fireWorksUpdate(float t);

protected:
	virtual void update(float t);
	void keyPressed(unsigned char key, const PxTransform& camera);
};

//-------------------------------------------------------

class SceneManager{
private:
	Scene* actualScene;
	int numScene;
public:
	SceneManager(int scene);
	void changeScene(int scene);
	~SceneManager();
	void update(float t) { actualScene->update(t); };
	void keyPressed(unsigned char key, const PxTransform& camera) { actualScene->keyPressed(key, camera); };
};