/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "myentity.h"

MyEntity::MyEntity() : Entity()
{
	this->addSprite("assets/hexagon.tga");
	this->scale = Point2(0.5, 0.5);
}

MyEntity::~MyEntity()
{
}

void MyEntity::update(float deltaTime)
{
}

void MyEntity::Selected() {
	this->sprite()->color = RED;
}

void MyEntity::Unselected() {
	this->sprite()->color = WHITE;
}
