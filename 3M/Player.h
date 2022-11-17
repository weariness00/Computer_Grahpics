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
	void Init();
	void Update();
	void Handle_Evnet(unsigned char key);
	void Handle_Evnet(int specialKey);

private:

public:

	//Collider collider;

	float speed = 1;
private:

};

