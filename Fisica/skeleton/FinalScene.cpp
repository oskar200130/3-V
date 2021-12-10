#include "FinalScene.h"

FinalScene::FinalScene(PxPhysics* _gPhysics, PxScene* _gScene) : Scene() {
	gPhysics = _gPhysics;
	gScene = _gScene;
	// Ground
	PxShape* shape = CreateShape(PxBoxGeometry(100, 1, 1000));
	PxRigidStatic* ground = gPhysics->createRigidStatic({ 0,0,0 });
	ground->attachShape(*shape);
	gScene->addActor(*ground);
	item = new RenderItem(shape, ground, { 0.6, 0.2, 1, 1 });

	color = Vector4(float((rand() % 10) / 10.0), float((rand() % 10) / 10.0), float((rand() % 10) / 10.0), 1.0);
	sb = new SoloBodySystem(gPhysics, gScene);
	//rigid
	PxRigidDynamic* rigid = gPhysics->createRigidDynamic({ 0, 6, 0 });
	// shape
	shape = CreateShape(PxBoxGeometry(5.0, 5.0, 5.0));
	rigid->attachShape(*shape);
	//Cinetica
	rigid->setLinearVelocity({ 0, 0, 0 });
	rigid->setLinearDamping(0.1);
	rigid->setAngularVelocity({ 0.0,0.0,0.0 });
	rigid->setAngularDamping(0.05);
	//Dinámica
	rigid->setMass(4);
	rigid->setMassSpaceInertiaTensor(PxVec3(0.0f, 0.0f, 0.0f));
	gScene->addActor(*rigid);
	// complete body struct
	sb->body->rigid = rigid;
	sb->body->life = 50000;
	sb->body->force = { 0.0f, 0.0f, 0.0f };
	sb->body->torque = { 0.0f, 0.0f, 0.0f };
	sb->body->renderItem = new RenderItem(shape, rigid, color);
}

FinalScene::~FinalScene() {

}

void FinalScene::update(float t){
	sb->integrate(t);
}

void FinalScene::keyPressed(unsigned char key, const PxTransform& camera) {
	switch (toupper(key))
	{
	case 'T':
		if (sb->body->rigid->getLinearVelocity().y < 0.05 && sb->body->rigid->getLinearVelocity().y >= 0) {
			sb->body->force = Vector3(0, 80000, 0);
			sb->body->torque = Vector3(-600, 0, 0);
		}
		break;
	case 'F':
		if (sb->body->rigid->getLinearVelocity().x < 0.02 && sb->body->rigid->getLinearVelocity().x > -0.02)
			sb->body->force = Vector3(-50000, 0, 0);
		break;
	case 'H':
		if (sb->body->rigid->getLinearVelocity().x < 0.02 && sb->body->rigid->getLinearVelocity().x > -0.02)
			sb->body->force = Vector3(50000, 0, 0);
		break;
	default:
		break;
	}
}
