/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "hexagon.h"

Hexagon::Hexagon(int x_co, int y_co) : Entity()
{
	int x_coefficient = x_co;
	int y_coefficient = y_co;

	this->addSprite("assets/hexagon.tga");
	this->scale = Point2(0.5, 0.5);
	Point2 position = this->position;

	textboxX = new Text();
	textboxX->message(std::to_string(x_co), WHITE);
	textboxX->position.x = this->position.x - 50;
	this->addChild(textboxX);

	textboxY = new Text();
	textboxY->message(std::to_string(y_co), WHITE);
	textboxY->position.x = this->position.x + 50;
	this->addChild(textboxY);
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

