/**
 * This class describes basicentity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "basicentity.h"

Basicentity::Basicentity() : Entity()
{
	this->addSprite("assets/color.tga");
	this->scale = Point2(0.3, 0.15);
}

Basicentity::~Basicentity()
{
}


void Basicentity::update(float deltaTime)
{
}

