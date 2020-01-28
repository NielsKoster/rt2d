/**
 * Copyright 2020 Niels Koster
 *
 * @file button.h
 *
 * @brief description of button behavior.
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <entity.h>
#include <text.h>

class Button : public Entity
{
public:
	/// @brief Constructor
	Button();
	/// @brief Destructor
	virtual ~Button();

	Text* textbox;

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void OnClick();

private:
};

#endif /* BUTTON_H */
