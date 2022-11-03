#pragma once
#include "Object.h"
#include "Collider.h"

class Player : public Object
{
public:
	Player();
	~Player();

public:
	void Init();
	void Draw();

private:

public:
	Collider collider;

private:

};

