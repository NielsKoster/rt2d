/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2020 Niels Koster
 */

#include "hexagon.h"

Hexagon::Hexagon() : Entity()
{
	this->addSprite("assets/hexagon.tga");
	this->scale = Point2(0.5, 0.5);
	Point2 position = this->position;

	//MyEntity nwNeigh;
}

Hexagon::~Hexagon()
{
}

void Hexagon::update(float deltaTime)
{
}

void Hexagon::Highlighted() {
	this->addSprite("assets/hexagon_selected.tga");
	this->sprite()->color = GRAY;
}

void Hexagon::Selected() {
	this->addSprite("assets/hexagon_selected.tga");
	this->sprite()->color = RED;
}


void Hexagon::Unselected() {
	this->addSprite("assets/hexagon.tga");
	this->sprite()->color = GRAY;
}
