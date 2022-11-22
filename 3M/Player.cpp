#include "Player.h"

ObjectBlock* Player::player_Block = nullptr;

Player::Player()
{
	name = "Player";

	if (player_Block == nullptr)
	{
		player_Block = new ObjectBlock;
		ReadObj((char*)"Player.obj", *player_Block);
	}

	block.vertIndex = player_Block->vertIndex;
	block.faceIndex = player_Block->faceIndex;
	block.vertices = player_Block->vertices;
	block.face = player_Block->face;

	collider.object = this;
	//collider.SetBox_OBB(vec3(10,50,10));
	vec3 box[2] = { vec3(0), vec3(player_Block->max) };
	collider.SetBox(box,2);
	collider.isCollide = false;
	collider.tag = "Player";
}

Player::~Player()
{
}

void Player::Enable()
{
	this->collider.isCollide = true;
}

void Player::Disable()
{
	this->collider.isCollide = false;
}

void Player::Init()
{
	SetActive(false);
	transform.localRotation.y = 180;
	transform.localPivot.y = -1;

	transform.worldScale *= 0.05;
	transform.worldPosition.y = 1;

	Object::Init();
	Render::objectRenedr->AddObject(this);
}

void Player::Update()
{
	Handle_Evnet(key);
	Handle_Evnet(specialKey);
}

void Player::Handle_Evnet(unsigned char key)
{
	float frameSpeed = speed * FrameTime::oneFrame;
	float x = transform.worldRotation.x;
	transform.worldRotation.x -= x;
	switch (key)
	{
	case 'a':
		transform.worldRotation.y += 90;
		transform.LookAt(speed);
		transform.worldRotation.y -= 90;
		break;
	case 'd':
		transform.worldRotation.y -= 90;
		transform.LookAt(speed);
		transform.worldRotation.y += 90;
		break;
	case 'w':
		transform.LookAt(speed);
		break;
	case 's':
		transform.LookAt(-speed);
		break;
	}
	transform.worldRotation.x += x;
}

void Player::Handle_Evnet(int specialKey)
{

}

void Player::Collision()
{
	if (!collider.isCollide)
		return;

	speed = 1;
	for (auto& other : Collider::allCollider)
	{
		if (other->object->id == this->id)
			continue;

		if (!other->isCollide)
			continue;

		if (!collider.Collide_XZ(*other))
			continue;

		speed = 0;
	}

	//for (auto& other : Collider::allCollider)
	//{
	//	if (other->object->id == this->id)
	//		continue;

	//	if (!this->collider.OBBCollision(this->collider, *other))
	//		continue;

	//	cout << other->tag << endl;
	//}
}