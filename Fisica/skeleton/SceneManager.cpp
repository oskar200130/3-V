#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(int scene, PxScene* gSce, PxPhysics* gPhy) {
	gScene = gSce;
	gPhysics = gPhy;
	sceneSelector(scene);
}

void SceneManager::changeScene(int scene) {
	if (scene != numScene) {
		delete actualScene;
		sceneSelector(scene);
	}
}

void SceneManager::sceneSelector(int scene) {
	numScene = scene;
	switch (scene) {
	case 0:
		actualScene = new FireworkScene();
		break;
	case 1:
		actualScene = new SpringScene();
		break;
	case 2:
		actualScene = new BuoyancyScene();
		break;
	case 3:
		actualScene = new RigidSolidScene(gPhysics, gScene);
	default:
		break;
	}
}

SceneManager::~SceneManager() {
	delete actualScene;
	actualScene = nullptr;
}

//--------------------------------------------------------------------

Scene::~Scene(){
	forceReg->clear();
	delete forceReg;
	for (auto f : pForces)
		delete f;
	for (auto f : bForces)
		delete f;
}

void Scene::initForces() {
	forceReg = new ParticleForceRegistry();

	pForces[0] = new ParticleGravity(Vector3(0.0, -10.0, 0.0));
	pForces[1] = new ParticleGravity(Vector3(0.0, -2.5, 0.0));
	pForces[2] = new Wind(Vector3(-10.0, 8.0, 2.0), 50.0);
	pForces[3] = new Explosion(Vector3(160.0, 160.0, 160.0), 80.0);
	
	bForces[0] = new BodyWind({ 0.0f, -100.0f, -100.0f });
	bForces[1] = new BodyTorque({ 100.0f, 0.0f, 0.0f });
	bForces[2] = new BodyExplosion(Vector3(500.0, 500.0, 500.0), 15.0);
}

//--------------------------------------------------------------------

FireworkScene::FireworkScene() : Scene() {
	initFireworkRules();
}

FireworkScene::~FireworkScene() {
	for (FireWork* f : fireworks) {
		forceReg->removePartInstance(*fireworks.begin(), nullptr);
		delete* fireworks.begin();
		fireworks.erase(fireworks.begin());
	}
	for (FireWorkRule* r : rules) {
		delete r;
	}
}

void FireworkScene::initFireworkRules() {
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

void FireworkScene::fireWorksUpdate(float t) {
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
					forceReg->add(newF, nullptr, pForces[0], nullptr);
					forceReg->add(newF, nullptr, pForces[2], nullptr);
					forceReg->add(newF, nullptr, pForces[3], nullptr);
				}
			}
		}
	}
	for (FireWork* f : fireworks) {
		if (!f->isActive()) {
			forceReg->removePartInstance(f, nullptr);
			delete f;
			fireworks.erase(std::remove(fireworks.begin(), fireworks.end(), f), fireworks.end());
		}
	}
	for (auto i = add.begin(); i != add.end(); ++i)
		fireworks.push_back(*i);

	static_cast<Explosion*>(pForces[3])->update(t);
}

void FireworkScene::update(float t) {
	Scene::update(t);
	fireWorksUpdate(t);
}

void FireworkScene::keyPressed(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	Vector3 position = {
			GetCamera()->getTransform().p.x + GetCamera()->getDir().x * 400,
			GetCamera()->getTransform().p.y + GetCamera()->getDir().y * 400,
			GetCamera()->getTransform().p.z + GetCamera()->getDir().z * 400 };

	switch (toupper(key))
	{
	case ' ': {
		FireWork* f = new FireWork(FireWorkType::particle);
		PxTransform pos = GetCamera()->getTransform();
		rules[3]->create(f, pos.p);
		fireworks.push_back(f);
		forceReg->add(f, nullptr, pForces[0], nullptr);
		forceReg->add(f, nullptr, pForces[2], nullptr);
		forceReg->add(f, nullptr, pForces[3], nullptr);
		break;
	}
	case 'M': {
		FireWork* f = new FireWork(FireWorkType::particle);
		PxTransform pos = GetCamera()->getTransform();
		rules[3]->create(f, pos.p);
		fireworks.push_back(f);
		forceReg->add(f, nullptr, pForces[1], nullptr);
		forceReg->add(f, nullptr, pForces[2], nullptr);
		forceReg->add(f, nullptr, pForces[3], nullptr);
		break;
	}
	case 'C': {
		FireWork* f = new FireWork(FireWorkType::explosion);
		rules[0]->create(f, position);
		fireworks.push_back(f);
		forceReg->add(f, nullptr, pForces[0], nullptr);
		forceReg->add(f, nullptr, pForces[2], nullptr);
		forceReg->add(f, nullptr, pForces[3], nullptr);
		break;
	}
	case 'V': {
		FireWork* f = new FireWork(FireWorkType::shoot);
		position.x += 200;
		position.z += 200;
		rules[1]->create(f, position);
		fireworks.push_back(f);
		forceReg->add(f, nullptr, pForces[0], nullptr);
		forceReg->add(f, nullptr, pForces[2], nullptr);
		forceReg->add(f, nullptr, pForces[3], nullptr);
		break;
	}
	case 'B': {
		FireWork* f = new FireWork(FireWorkType::fireball);
		position.x -= 300;
		position.y -= 300;
		position.z -= 300;
		rules[2]->create(f, position);
		fireworks.push_back(f);
		forceReg->add(f, nullptr, pForces[0], nullptr);
		forceReg->add(f, nullptr, pForces[2], nullptr);
		forceReg->add(f, nullptr, pForces[3], nullptr);
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

//--------------------------------------------------------------------

SpringScene::SpringScene() : Scene() {
	k = 2.0;
	p1 = new Particle();
	p1->init(Vector3(-60, 50, -60), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 0.5, 0);

	p2 = new Particle();
	p2->init(Vector3(-60, 10, -60), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 0.5);
	forceReg->add(p2, nullptr, pForces[0], nullptr);
	forceReg->add(p2, nullptr, pForces[3], nullptr);

	sp1 = new ParticleSpring(p2, k, 30.0f);
	forceReg->add(p1, nullptr, sp1, nullptr);

	sp2 = new ParticleSpring(p1, k, 30.0f);
	forceReg->add(p2, nullptr, sp2, nullptr);
}

SpringScene::~SpringScene() {
	delete p1;
	delete p2;
	delete sp1;
	delete sp2;
	p1 = p2 = nullptr;
	sp1 = sp2 = nullptr;
}

void SpringScene::update(float t) {
	Scene::update(t);
	p1->integrate(t);
	p2->integrate(t);
	static_cast<Explosion*>(pForces[3])->update(t);
}

void SpringScene::keyPressed(unsigned char key, const PxTransform& camera) {
	switch (toupper(key)) {
	case 'T':
	{
		static_cast<Explosion*>(pForces[3])->activateExplosion();
		break;
	}
	case 'R':
	{
		changeAnchor();
		break;
	}
	case '+':
	{
		if (k < 8) {
			k++;
			sp1->changeK(k);
			sp2->changeK(k);
		}
		break;
	}
	case '-':
	{
		if (k > 1) {
			k--;
			sp1->changeK(k);
			sp2->changeK(k);
		}
		break;
	}
	default: {
		break;
	}
	}
}

void SpringScene::changeAnchor() {
	int m = p1->getMass();
	delete p1;
	delete p2;
	delete sp1;
	delete sp2;
	forceReg->clear();

	p1 = new Particle();

	if (m != 1)
		p1->init(Vector3(-60, 60, -60), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 0.5, 0);
	else {
		p1->init(Vector3(-80, 10, -50), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 0.5);
		forceReg->add(p1, nullptr, pForces[0], nullptr);
		forceReg->add(p1, nullptr, pForces[3], nullptr);
	}

	p2 = new Particle();
	p2->init(Vector3(-60, 10, -60), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 0.5);
	forceReg->add(p2, nullptr, pForces[0], nullptr);
	forceReg->add(p1, nullptr, pForces[3], nullptr);

	sp1 = new ParticleSpring(p2, k + 0.1, 30.0f);
	forceReg->add(p1, nullptr, sp1, nullptr);

	sp2 = new ParticleSpring(p1, k + 0.1, 30.0f);
	forceReg->add(p2, nullptr, sp2, nullptr);
}

//--------------------------------------------------------------------

BuoyancyScene::BuoyancyScene() : Scene() {
	vol = 0.3;
	mass = 5;

	p = new Particle();
	p->init(Vector3(-60, 60, -60), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 0.5, mass, 10, true);
	forceReg->add(p, nullptr, pForces[0], nullptr);

	by = new ParticleBuoyancy(10, vol, 10);
	forceReg->add(p, nullptr, by, nullptr);

	floor = new Particle();
	floor->init(Vector3(-60, 10, -60), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(0, 0.02, 1, 0.3), 0.85, 0, 2.0, true, Vector3(50, 0.2, 50));
}

BuoyancyScene::~BuoyancyScene() {
	delete p;
	delete floor;
	delete by;
	p = floor = nullptr;
	by = nullptr;
}

void BuoyancyScene::update(float t) {
	Scene::update(t);
	p->integrate(t);
}

void BuoyancyScene::keyPressed(unsigned char key, const PxTransform& camera) {
	switch (toupper(key)) {
	case '+':
	{
		mass++;
		p->setMass(mass);
		break;
	}
	case '-':
	{
		if (mass > 1)
			mass--;
		p->setMass(mass);
		break;
	}
	case 'P':
	{
		if (vol < 0.8) {
			vol += 0.1;
			by->changeVol(vol);
		}
		break;
	}
	case 'L':
	{
		if (vol > 0.1) {
			vol -= 0.1;
			by->changeVol(vol);
		}
		break;
	}
	default: {
		break;
	}
	}
}

//--------------------------------------------------------------------

RigidSolidScene::RigidSolidScene(PxPhysics* _gPhysics, PxScene* _gScene) {
	gPhysics = _gPhysics;
	gScene = _gScene;
	// Ground
	PxShape* shape = CreateShape(PxBoxGeometry(100, 1, 100));
	PxRigidStatic* ground = gPhysics->createRigidStatic({ 0,0,0 });
	ground->attachShape(*shape);
	gScene->addActor(*ground);
	item = new RenderItem(shape, ground, { 0.6, 0.2, 1, 1 });
	// sistema de sólidos rígidos
	bodySys = new BodySystem(gPhysics, gScene, { 0, 40, 0 });
}

RigidSolidScene::~RigidSolidScene(){
	delete bodySys;
	bodySys = nullptr;
	DeregisterRenderItem(item);
	delete item;
	item = nullptr;
}

void RigidSolidScene::update(float t){
	FireworkScene::update(t);
	bodySys->integrate(t);

	for (SolidBody* f : bodySys->bodies) {
		if (!f->active) {
			forceReg->removePartInstance(nullptr, f);
			delete* bodySys->bodies.begin();
			bodySys->bodies.erase(std::remove(bodySys->bodies.begin(), bodySys->bodies.end(), f), bodySys->bodies.end());
		}
	}

	if (bodySys->getNumPar() < bodySys->getMaxPar() && bodySys->getTimeSinceAdding() > bodySys->getStep()) {
		auto a = bodySys->addBody();
		forceReg->add(nullptr, a, nullptr, bForces[0]);
		forceReg->add(nullptr, a, nullptr, bForces[1]);
		forceReg->add(nullptr, a, nullptr, bForces[2]);
	}


	static_cast<BodyExplosion*>(bForces[2])->update(t);
}

void RigidSolidScene::keyPressed(unsigned char key, const PxTransform& camera){
	switch (toupper(key))
	{
	case 'M': {
		FireWork* f = new FireWork(FireWorkType::particle);
		PxTransform pos = GetCamera()->getTransform();
		rules[3]->create(f, pos.p);
		fireworks.push_back(f);
		forceReg->add(f, nullptr, pForces[1], nullptr);
		forceReg->add(f, nullptr, pForces[2], nullptr);
		forceReg->add(f, nullptr, pForces[3], nullptr);
		break;
	}
	case 'E':
	{
		static_cast<BodyTorque*>(bForces[1])->activateTorque();
		break;
	}
	case 'R':
	{
		static_cast<BodyTorque*>(bForces[1])->deactivateTorque();
		break;
	}
	case 'F':
	{
		static_cast<BodyWind*>(bForces[0])->activateBodWind();
		break;
	}
	case 'G':
	{
		static_cast<BodyWind*>(bForces[0])->deactivateBodWind();
		break;
	}
	case 'T':
	{
		static_cast<BodyExplosion*>(bForces[2])->activateExplosion();
		break;
	}
	}
}
