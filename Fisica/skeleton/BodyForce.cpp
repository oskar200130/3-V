#include "BodyForce.h"

void BodyWind::updateForce(SolidBody* particle, float t) {
	if (activated && (particle->rigid->getGlobalPose().p - renderItem->transform->p).magnitude() < radius) {
		particle->force += w;
	}
}

void BodyWind::activateBodWind() {
	if (!activated) {
		pos = new PxTransform(0, 0, 0);

		pos->p = { 0, 15, 0 };

		Vector4 color = { 0.0, 1.0, 0.0, 0.0 };
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(radius)), pos, color);
		activated = true;
	}
}

void BodyWind::deactivateBodWind() {
	if (activated) {
		DeregisterRenderItem(renderItem);
		delete renderItem;
		delete pos;
		renderItem = nullptr;
		activated = false;
	}
}
//-------------------------------------------------------------------------------------------------

void BodyTorque::updateForce(SolidBody* particle, float t) {
	if (activated && (particle->rigid->getGlobalPose().p - renderItem->transform->p).magnitude() < radius) {
		particle->torque += torque;
	}
}

void BodyTorque::activateTorque() {
	if (!activated) {
		pos = new PxTransform(0, 0, 0);

		pos->p = { 0, 15, 0 };

		Vector4 color = { 0.0, 0.0, 1.0, 0.0 };
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(radius)), pos, color);
		activated = true;
	}
}

void BodyTorque::deactivateTorque() {
	if (activated) {
		DeregisterRenderItem(renderItem);
		delete renderItem;
		delete pos;
		renderItem = nullptr;
		activated = false;
	}
}
//-------------------------------------------------------------------------------------------------

void BodyExplosion::updateForce(SolidBody* particle, float t) {
	if (activated && (particle->rigid->getGlobalPose().p - renderItem->transform->p).magnitude() < radius) {
		Vector3 force = (particle->rigid->getGlobalPose().p - renderItem->transform->p).getNormalized() * g.magnitude();
		particle->force += g;
	}
}

void BodyExplosion::update(float t) {
	if (activated) {
		lastIni += t;
		if (lastIni >= duration) {
			deactivateExplosion();
			lastIni = 0;
		}
	}
}

void BodyExplosion::activateExplosion() {
	if (!activated) {
		pos = new PxTransform(0, 0, 0);

		pos->p = { 0,15.0,0 };

		Vector4 color = { 1.0, 0.0, 0.0, 0.0 };
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(radius)), pos, color);
		activated = true;
	}
}

void BodyExplosion::deactivateExplosion() {
	if (activated) {
		DeregisterRenderItem(renderItem);
		delete renderItem;
		delete pos;
		renderItem = nullptr;
		activated = false;
	}
}