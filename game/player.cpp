/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "player.h"

Player::Player() : Entity()
{
	this->addSprite("assets/hexagon_selected.tga");
	this->sprite()->color = RED;
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

