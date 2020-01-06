/**
 * This class describes player behavior.
 *
 * Copyright 2020 Niels Koster
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
	Vector2 distance = Vector2(playerpos - destinationpos);
	this->position = playerpos -= distance;
}

void Player::update(float deltaTime)
{
}

