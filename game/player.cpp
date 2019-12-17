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

void Player::NavigateToPoint(Point2 destinationpos)
{
	Point2 playerpos = this->position;

	/*while (playerpos != destinationpos) {

	}*/
}

void Player::update(float deltaTime)
{
}

