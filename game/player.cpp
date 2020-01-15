/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "player.h"

Player::Player() : Entity()
{
	this->addSprite("assets/player.tga");
	this->scale = Point2(0.3, 0.15);
}

Player::~Player()
{
}

Vector2 Player::NavigateToPoint(Vector2 beginpos, Hexagon* despos)
{
	Vector2 path = beginpos - despos->position;
	path.normalize();
	path *= 5;
	
	return path;
}

void Player::update(float deltaTime)
{
}

