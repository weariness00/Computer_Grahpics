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

	transform.localScale *= 0.01;
}

Player::~Player()
{
}

void Player::Init()
{
	Object::Init();
	Render::mainRender->AddObject(this);
}

void Player::Update()
{
	Handle_Evnet(key);
	Handle_Evnet(specialKey);

	SetMatrix();
}

void Player::Handle_Evnet(unsigned char key)
{
}

void Player::Handle_Evnet(int specialKey)
{

	float frameSpeed = speed * FrameTime::oneFrame;
	switch (specialKey)
	{
	case GLUT_KEY_LEFT:
		transform.worldPosition.x -= frameSpeed;
		break;
	case GLUT_KEY_RIGHT:
		transform.worldPosition.x += frameSpeed;
		break;
	case GLUT_KEY_UP:
		transform.worldPosition.z += frameSpeed;
		break;
	case GLUT_KEY_DOWN:
		transform.worldPosition.z -= frameSpeed;
		break;
	}
}
