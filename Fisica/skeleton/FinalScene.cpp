#include "FinalScene.h"
#include <iostream>

FinalScene::FinalScene(PxPhysics* _gPhysics, PxScene* _gScene) : FireworkScene(), vol(5.0), mass(10.0), jump(false) {
	gPhysics = _gPhysics;
	gScene = _gScene;

	createPlatform();
	initPlayer();

	Particle* p1;
	for (int i = 0; i < 5; i++) {
		p1 = new Particle();
		p1->init(Vector3(-100 + i * 40, 4, -540), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 1.0, 10, 5, true, Vector3(10, 2, 20));
		obstacles.push_back(p1);
	}

	p1 = new Particle();
	p1->init(Vector3(-20, 4, -775), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 1.0, 10, 5, true, Vector3(100, 2, 30));
	obstacles.push_back(p1);
	p1 = new Particle();
	p1->init(Vector3(20, 4, -950), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 1.0, 10, 5, true, Vector3(20, 2, 50));
	obstacles.push_back(p1);
	p1 = new Particle();
	p1->init(Vector3(30, 4, -1250), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 1.0, 10, 5, true, Vector3(35, 2, 20));
	obstacles.push_back(p1);
	p1 = new Particle();
	p1->init(Vector3(-10, 4, -1900), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 1.0, 10, 5, true, Vector3(40, 2, 15));
	obstacles.push_back(p1);
	p1 = new Particle();
	p1->init(Vector3(0, 4, -2500), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 1.0, 10, 5, true, Vector3(60, 2, 30));
	obstacles.push_back(p1);

	createMuelle(50, -160, 2.0);
	createMuelle(100, -200, 1.6);
	createMuelle(20, -260, 2.0);
	createMuelle(50, -360, 2.2);
	createMuelle(75, -990, 2.0);
	createMuelle(25, -2175, 1.9);

	createPlatforms({ 10, 15, 40 }, { -10, 16, -675 });
	createPlatforms({ 25, 30, 60 }, { -10, 31, -875 });
	createPlatforms({ 14, 20, 50 }, { -30, 21, -1175 });
	createPlatforms({ 25, 40, 20 }, { 40, 41, -1475 });
	createPlatforms({ 30, 10, 10 }, { -35, 11, -1765 });
	createPlatforms({ 45, 40, 100 }, { 40, 41, -1875 });
	createPlatforms({ 25, 80, 40 }, { -45, 81, -2475 });
	createPlatforms({ 20, 40, 10 }, { 40, 41, -2775 });

	pb = new BodyBuoyancy(vol, vol, -4);

	static_cast<BodyWind*>(bForces[0])->activateBodWind({ 0.0, 0.0, -4250.0 });

	water = new Particle();
	water->init(Vector3(-10, -4, -3750), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(0, 0.02, 1, 1), 0.85, 0, 2.0, true, Vector3(100, 0.2, 1000));

	bodySys = new BodySystem(gPhysics, gScene, { 0, 0, -4250 });
}

void FinalScene::createPlatforms(Vector3 dim, Vector3 pos) {
	PxShape* shape = CreateShape(PxBoxGeometry(dim));
	PxRigidStatic* ground = gPhysics->createRigidStatic(PxTransform(pos));
	ground->attachShape(*shape);
	gScene->addActor(*ground);
	RenderItem* i = new RenderItem(shape, ground, { 0.6, 0.2, 1, 1 });
	plataformas.push_back(i);
	Particle* p1 = new Particle();
	p1->init(Vector3(pos.x, pos.y, pos.z + dim.z), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 0), 1.0, 10, 5, true, Vector3(dim.x, dim.y / 1.1, 2));
	obstacles.push_back(p1);
}

void FinalScene::createMuelle(float partp, float pos, float k) {
	TrampaMuelle* tp = new TrampaMuelle;
	tp->o1 = new Particle();
	tp->o1->init(Vector3(-150, 8, pos), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 0), 0.5, 0, 4, true);
	tp->o2 = new Particle();
	tp->o2->init(Vector3(138, 8, pos), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 0), 0.5, 0, 4, true);

	tp->p = new Particle();
	tp->p->init(Vector3(partp, 8, pos), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(1, 0, 0, 1), 0.5, 10, 4, true);
	obstacles.push_back(tp->p);

	tp->o1p = new ParticleSpring(tp->p, k, 50.0f);
	forceReg->add(tp->o1, nullptr, tp->o1p, nullptr);
	tp->po1 = new ParticleSpring(tp->o1, k, 50.0f);
	forceReg->add(tp->p, nullptr, tp->po1, nullptr);

	tp->o2p = new ParticleSpring(tp->p, k, 50.0f);
	forceReg->add(tp->o2, nullptr, tp->o2p, nullptr);
	tp->po2 = new ParticleSpring(tp->o2, k, 50.0f);
	forceReg->add(tp->p, nullptr, tp->po2, nullptr);

	muelles.push_back(tp);
}

FinalScene::~FinalScene() {
	delete water;
	water = nullptr;
	DeregisterRenderItem(item);
	delete item;
	DeregisterRenderItem(item2);
	delete item2;
	DeregisterRenderItem(item3);
	delete item3;
	item = item2 = item3 = nullptr;
	delete sb;
	sb = nullptr;
	sbSh = nullptr;
	for (auto* a : plataformas) {
		DeregisterRenderItem(a);
		delete a;
	}
	for (auto* a : obstacles)
		delete a;
	for (auto* a : muelles)
		delete a;
	delete pb;
	pb = nullptr;
	delete bodySys;
	bodySys = nullptr;
}

void FinalScene::update(float t) {
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
		auto a = bodySys->addBody(PxTransform(0, 60, -4250), true);
		forceReg->add(nullptr, a, nullptr, bForces[0]);
		forceReg->add(nullptr, a, nullptr, pb);
	}

	if (sb != nullptr && sb->body->rigid->getGlobalPose().p.z > -4200) {
		if (sb->body->rigid->getGlobalPose().p.z < -2910) {
			forceReg->add(nullptr, sb->body, nullptr, pb);
			sb->body->vel = { 0,0,-0.5 };
		}
		if (sb->body->rigid->getLinearVelocity().y > 5.0) {
			sb->body->vel = { 0,0,-0.75 };
		}
		else
			sb->body->vel = { 0,0,-1.5 };

		sb->integrate(t);

		Vector3 p1 = sb->body->rigid->getGlobalPose().p;
		GetCamera()->setDir({ 0,0,-1 });
		GetCamera()->handleAnalogMove(0, -p1.z + lastPos.z);
		GetCamera()->setDir({ -0.6f,-0.4f,-0.7f });
		lastPos = sb->body->rigid->getGlobalPose().p;
	}
	else {
		if (timer > 5.0 || (sb != nullptr && sb->body->rigid->getGlobalPose().p.z < -4200)) {
			GetCamera()->setEye(PxVec3(120.0f, 90.0f, 120.0f));
			reset = true;
		}
		else
			timer += t;
	}

	for (auto* a : obstacles) {
		a->integrate(t);
		if (sb != nullptr && collisions(a))
			playerDeath();
	}
	static_cast<BodyExplosion*>(bForces[2])->update(t);
}

void FinalScene::createPlatform() {
	// Ground
	PxShape* shape = CreateShape(PxBoxGeometry(100, 1, 1500));
	PxRigidStatic* ground = gPhysics->createRigidStatic({ -10,0,-1400 });
	ground->attachShape(*shape);
	gScene->addActor(*ground);
	item = new RenderItem(shape, ground, { 0.6, 0.2, 1, 1 });

	shape = CreateShape(PxBoxGeometry(1, 30, 2500));
	ground = gPhysics->createRigidStatic({ -109.1,29.1,-1400 });
	ground->attachShape(*shape);
	gScene->addActor(*ground);
	item2 = new RenderItem(shape, ground, { 0.6, 0.2, 1, 0 });

	shape = CreateShape(PxBoxGeometry(1, 30, 2500));
	ground = gPhysics->createRigidStatic({ 89.1,29.1,-1400 });
	ground->attachShape(*shape);
	gScene->addActor(*ground);
	item3 = new RenderItem(shape, ground, { 0.6, 0.2, 1, 0 });
}

void FinalScene::initPlayer() {
	color = Vector4(0.2, 0.6, 0.8, 1.0);
	sb = new SoloBodySystem(gPhysics, gScene);
	//rigid
	PxRigidDynamic* rigid = gPhysics->createRigidDynamic({ -5, 5, 0 });
	// shape
	sbSh = CreateShape(PxBoxGeometry(vol, vol, vol));
	rigid->attachShape(*sbSh);
	//Cinetica
	rigid->setLinearVelocity({ 0, 0, 0 });
	rigid->setLinearDamping(0.7);
	rigid->setAngularVelocity({ 0.0,0.0,0.0 });
	rigid->setAngularDamping(0.05);
	//Dinámica
	rigid->setMass(mass);
	rigid->setMassSpaceInertiaTensor(PxVec3(0.0f, 0.0f, 0.0f));
	gScene->addActor(*rigid);
	// complete body struct
	sb->body->rigid = rigid;
	sb->body->life = 0;
	sb->body->vel = { 0, 0, -1.5 };
	sb->body->force = { 0.0f, 0.0f, 0.0f };
	sb->body->torque = { 0.0f, 0.0f, 0.0f };
	sb->body->renderItem = new RenderItem(sbSh, rigid, color);
	forceReg->add(nullptr, sb->body, nullptr, bForces[2]);

	lastPos = sb->body->rigid->getGlobalPose().p;
}

bool FinalScene::collisions(Particle* p) {
	return PxGeometryQuery::overlap(p->getRender()->shape->getGeometry().box(), p->getPosition(), sb->body->renderItem->shape->getGeometry().box(), sb->body->rigid->getGlobalPose());
}

void FinalScene::playerDeath() {
	FireWork* f = new FireWork(FireWorkType::explosion);
	static_cast<BodyExplosion*>(bForces[2])->deactivateExplosion();
	rules[0]->create(f, sb->body->rigid->getGlobalPose().p);
	fireworks.push_back(f);
	delete sb;
	sb = nullptr;
	//forceReg->add(f, nullptr, pForces[0], nullptr);
	forceReg->add(f, nullptr, pForces[2], nullptr);
	forceReg->add(f, nullptr, pForces[3], nullptr);
}

void FinalScene::actSb() {
	if (sb != nullptr) {
		sb->body->rigid->setMass(mass);
		sb->body->rigid->detachShape(*sbSh);
		sbSh = CreateShape(PxBoxGeometry(vol, vol, vol));
		sb->body->rigid->attachShape(*sbSh);
		sb->body->renderItem->shape = sbSh;
		pb->changeVol(vol);
	}
}


void FinalScene::keyPressed(unsigned char key, const PxTransform& camera) {
	switch (toupper(key))
	{
	case 'T':
		if (sb != nullptr && sb->body->rigid->getLinearVelocity().y < 0.2 && sb->body->rigid->getLinearVelocity().y >= 0) {
			sb->body->force = Vector3(0, 140 * 300, 0);
			jump = true;
		}
		break;
	case 'F':
		if (sb != nullptr && sb->body->rigid->getLinearVelocity().x < 1.9 && sb->body->rigid->getLinearVelocity().x > -1.9) {
			sb->body->rigid->setLinearVelocity(Vector3(0, 0, sb->body->rigid->getLinearVelocity().z));
			sb->body->force = Vector3(-80 * 200, 0, 0);
		}
		break;
	case 'H':
		if (sb != nullptr && sb->body->rigid->getLinearVelocity().x < 1.9 && sb->body->rigid->getLinearVelocity().x > -1.9) {
			sb->body->rigid->setLinearVelocity(Vector3(0, 0, sb->body->rigid->getLinearVelocity().z));
			sb->body->force = Vector3(80 * 200, 0, 0);
		}
		break;
	case 'O':
		if (mass + 5 < 50) {
			mass += 5;
			vol += 0.5;
			actSb();
		}
		break;
	case 'P':
		if (mass - 5 > 10) {
			mass -= 5;
			vol -= 0.5;
			actSb();
		}
		break;
	case 'L':
		if (sb != nullptr && jump) {
			static_cast<BodyExplosion*>(bForces[2])->activateExplosion(sb->body->rigid->getGlobalPose().p - Vector3(0, 1.5, -1));
			jump = false;
		}
		break;
	default:
		break;
	}
}
