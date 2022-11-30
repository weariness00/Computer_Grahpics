#pragma once
#include "Object.h"
#include "Collider.h"
#include "Render.h"

class Player : public Object
{
public:
	static ObjectBlock* player_Block;

public:
	Player();
	~Player();

public:
	void Enable();
	void Disable();
	void Init();
	void Update();
	void Handle_Evnet(unsigned char key);
	void Handle_Evnet(int specialKey);
	void Collision();

private:
	void Dash();

public:
	Collider collider;

	float speed = 1;
private:
	vec3 prevPos;

	float dashTime = 0;
	bool isDash = false;
};

