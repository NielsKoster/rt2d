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

	playericon = new Basicentity();

	playericon->addSprite("assets/1up.tga");
	this->addChild(playericon);
	playericon->position = Point2(this->position.x, this->position.y - 100);
	playericon->scale = Point2(10, 10);

	bool faded = false;
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

void Player::iconmovement(float deltaTime)
{
	if (playericon->position.y > this->position.y - 250 && faded == false)
	{
		playericon->position.y-- * deltaTime;

		if (playericon->sprite()->color.a > 1)
		{
			playericon->sprite()->color.a-- * deltaTime;
		} 
		else
		{
			faded = true;
		}
	}
}

void Player::showpoints(int points)
{
	if (points == 1)
	{
		playericon->addSprite("assets/1up.tga");
		faded = false;
	}

	if (points == -1)
	{
		playericon->addSprite("assets/1down.tga");
		faded = false;
	}
}

void Player::update(float deltaTime)
{
}

