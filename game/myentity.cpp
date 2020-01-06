/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2020 Niels Koster
 */

#include "myentity.h"

MyEntity::MyEntity() : Entity()
{
	this->addSprite("assets/hexagon.tga");
	this->scale = Point2(0.5, 0.5);
	Point2 position = this->position;
}

MyEntity::~MyEntity()
{
}

void MyEntity::update(float deltaTime)
{
}

void MyEntity::Highlighted() {
	this->addSprite("assets/hexagon_selected.tga");
	this->sprite()->color = GRAY;
}

void MyEntity::Selected() {
	this->addSprite("assets/hexagon_selected.tga");
	this->sprite()->color = RED;
}


void MyEntity::Unselected() {
	this->addSprite("assets/hexagon.tga");
	this->sprite()->color = GRAY;
}
