/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
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

void Button::OnClick()
{

}

