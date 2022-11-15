#include "RigidBody.h"

RigidBody::RigidBody(Transform& transform) : transform(&transform)
{
	velocity = vec3(0,-0.01,0);
	mass = 1;
}

RigidBody::~RigidBody()
{
}

vec3 RigidBody::UpdateRigid()
{
	mat4 rigidModel = mat4(1.0);
	vec3 vel = vec3(velocity);

	float z = radians(-transform->worldRotation.z - Camera::mainCamera->transform.worldRotation.z);
	vel = vec3(cos(z) * vel.x - sin(z) * vel.y,
		sin(z) * vel.x + cos(z) * vel.y,
		vel.z);

	return vel;
}	