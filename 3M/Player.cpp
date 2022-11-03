#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	if (!isActive)
		return;

	Object::SetMatrix();

	glDrawElements(GL_TRIANGLES, block.faceIndex * 3, GL_UNSIGNED_SHORT, 0);
}

void Player::Draw()
{
}
