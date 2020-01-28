/**
 * This class describes button behavior.
 *
 * Copyright 2020 Niels Koster 
 */

#include "button.h"


Button::Button() : Entity()
{
	this->addSprite("assets/button.tga");
	textbox = new Text();
	textbox->scale = Point2(0.8, 0.8);
	this->addChild(textbox);
}

Button::~Button()
{
}

void Button::update(float deltaTime)
{
}

