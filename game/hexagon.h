/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef HEXAGON_H
#define HEXAGON_H

#include <rt2d/entity.h>

/// @brief The MyEntity class is the Entity implementation.
class Hexagon : public Entity
{
public:
	/// @brief Constructor
	Hexagon();
	/// @brief Destructor
	virtual ~Hexagon();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void Highlighted();

	void Selected();

	void Unselected();

private:
	/* add your private declarations */
};

#endif /* MYENTITY_H */
