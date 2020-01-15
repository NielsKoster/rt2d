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

	pos = Point2(x_co, y_co);
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

void Hexagon::SelectedN() {
	this->addSprite("assets/hexagon_selected.tga");
	this->sprite()->color = BLUE;
}


void Hexagon::Unselected() {
	this->addSprite("assets/hexagon.tga");
	this->sprite()->color = GRAY;
}

Vector2 Hexagon::Calculatedistance(Point2 objective) 
{
	Vector2 distance = Vector2(position - objective);
	return distance;
}

