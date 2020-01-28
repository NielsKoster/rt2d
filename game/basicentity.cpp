/**
 * This class describes BasicEntity behavior.
 *
 * Copyright 2020 Niels Koster
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

