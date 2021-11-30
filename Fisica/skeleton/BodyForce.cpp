#include "BodyForce.h"

void BodyWind::updateForce(SolidBody* particle, float t){
	particle->force += w;
}
//-------------------------------------------------------------------------------------------------

void BodyTorque::updateForce(SolidBody* particle, float t){
	particle->torque += torque;
}
