#include "SceneManager.h"

SceneManager::SceneManager(int scene) {
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
	default:
		break;
	}
}

SceneManager::~SceneManager() {
	delete actualScene;
	actualScene = nullptr;
}

//--------------------------------------------------------------------

void Scene::initForces() {
	forceReg = new ParticleForceRegistry();

	pForces[0] = new ParticleGravity(Vector3(0.0, -10.0, 0.0));
	pForces[1] = new ParticleGravity(Vector3(0.0, -2.5, 0.0));
	pForces[2] = new Wind(Vector3(-10.0, 8.0, 2.0), 50.0);
	pForces[3] = new Explosion(Vector3(160.0, 160.0, 160.0), 80.0);
}

//--------------------------------------------------------------------

FireworkScene::FireworkScene() : Scene() {
	initFireworkRules();
}

FireworkScene::~FireworkScene() {
	for (FireWork* f : fireworks) {
		forceReg->removePartInstance(*fireworks.begin());
		delete* fireworks.begin();
		fireworks.erase(fireworks.begin());
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
		forceReg->add(f, pForces[0]);
		forceReg->add(f, pForces[0]);
		forceReg->add(f, pForces[2]);
		forceReg->add(f, pForces[3]);
		break;
	}
	case 'M': {
		FireWork* f = new FireWork(FireWorkType::particle);
		PxTransform pos = GetCamera()->getTransform();
		rules[3]->create(f, pos.p);
		fireworks.push_back(f);
		forceReg->add(f, pForces[1]);
		forceReg->add(f, pForces[2]);
		forceReg->add(f, pForces[3]);
		break;
	}
	case 'C': {
		FireWork* f = new FireWork(FireWorkType::explosion);
		rules[0]->create(f, position);
		fireworks.push_back(f);
		forceReg->add(f, pForces[0]);
		forceReg->add(f, pForces[2]);
		forceReg->add(f, pForces[3]);
		break;
	}
	case 'V': {
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
	case 'B': {
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

//--------------------------------------------------------------------

SpringScene::SpringScene() : Scene() {
	p1.init(Vector3(-20, 50, -20), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 0.5, 0);

	p2.init(Vector3(-20, 10, -20), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 0.5);
	forceReg->add(&p2, pForces[2]);

	ParticleSpring* sp1 = new ParticleSpring(&p2, 800.0f, 30.0f);
	forceReg->add(&p1, sp1);

	ParticleSpring* sp2 = new ParticleSpring(&p1, 800.0f, 30.0f);
	forceReg->add(&p2, sp2);
}

SpringScene::~SpringScene()
{
}

void SpringScene::update(float t) {
	Scene::update(t);
	p1.integrate(t);
	p2.integrate(t);
}

void SpringScene::keyPressed(unsigned char key, const PxTransform& camera) {
	switch (key) {
	case 'T':
	{
		static_cast<Explosion*>(pForces[3])->activateExplosion();
		break;
	}
	default: {
		break;
	}
	}
}
