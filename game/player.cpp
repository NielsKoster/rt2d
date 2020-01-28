/**
 * This class describes player behavior.
 *
 * Copyright 2020 Niels Koster
 */

#include "player.h"

Player::Player() : Entity()
{
	this->addSprite("assets/player.tga");
	this->sprite()->color = WHITE;
}

Player::~Player()
{
}

Vector2 Player::NavigateToPoint(Vector2 beginpos, Hexagon* despos, float deltaTime)
{
	int walkspeed = 4;
	Vector2 path = beginpos - despos->position;
	path.normalize();
	path *= walkspeed;
	
	return path;
}

void Player::update(float deltaTime)
{
}

