/**
 * Copyright 2020 Niels Koster
 *
 * @file player.h
 *
 * @brief description of player behavior.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>
#include "hexagon.h"
#include "basicentity.h"

class Player : public Entity
{
public:
	/// @brief Constructor
	Player();
	/// @brief Destructor
	virtual ~Player();

	Basicentity* pointsicon;

	Vector2 NavigateToPoint(Vector2 beginpos, Hexagon* despos, float deltaTime);

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	std::vector<RGBAColor> colors;

private:
};

#endif /* PLAYER_H */
