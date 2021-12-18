#pragma once
#include "SceneManager.h"
#include <vector>
struct TrampaMuelle {
	Particle* p, * o1, * o2;
	ParticleSpring* o1p, * po1, * o2p, * po2;
	~TrampaMuelle() {
		delete o1;
		delete o2;
		delete o1p;
		delete o2p;
		delete po1;
		delete po2;
		p = o1 = o2 = nullptr;
		o1p = po1 = o2p = po2 = nullptr;
	}
};

class FinalScene : public FireworkScene {
public:
	FinalScene(PxPhysics* _gPhysics, PxScene* _gScene);
	~FinalScene();
	virtual void update(float t);
private:
	void createPlatform();
	void createPlatforms(Vector3 dim, Vector3 pos);
	void createMuelle(float partp, float pos, float k);
	void initPlayer();
	bool collisions(Particle* p);
	void playerDeath();
	void actSb();
	PxPhysics* gPhysics;
	PxScene* gScene;
	RenderItem* item = nullptr;
	RenderItem* item2 = nullptr;
	RenderItem* item3 = nullptr;
	Particle* water;
	PxVec3 lastPos;
	Vector4 color;
	SoloBodySystem* sb;
	PxShape* sbSh;
	vector<Particle*> obstacles;
	vector<RenderItem*> plataformas;
	vector<TrampaMuelle*> muelles;
	BodyBuoyancy* pb;
	BodySystem* bodySys;

	float timer = 0.0;
	float mass, vol;
	bool jump;
protected:
	void keyPressed(unsigned char key, const PxTransform& camera);
};

