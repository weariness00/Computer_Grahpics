#pragma once
#include "Camera.h"

class RigidBody
{
public:
	RigidBody(Transform& transform);
	~RigidBody();

public:
	vec3 UpdateRigid();
	
public:
	Transform* transform;

	vec3 velocity;

	float mass; // Áú·®
};

