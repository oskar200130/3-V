#pragma once
#include "SceneManager.h"
class FinalScene : public Scene {
public:
	FinalScene(PxPhysics* _gPhysics, PxScene* _gScene);
	~FinalScene();
private:
	virtual void update(float t);

	PxPhysics* gPhysics;
	RenderItem* item = nullptr;
	PxScene* gScene;
	Vector4 color;
	SoloBodySystem* sb;
protected:
	void keyPressed(unsigned char key, const PxTransform& camera);
};

