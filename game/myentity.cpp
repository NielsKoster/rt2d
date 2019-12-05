/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "myentity.h"
#include "sprite.h"

MyEntity::MyEntity() : Entity()
{
	this->addSprite("assets/hex_cursor.tga");
	this->sprite()->color = WHITE;
}

MyEntity::~MyEntity()
{

}

void MyEntity::update(float deltaTime)
{
}
