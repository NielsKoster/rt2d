/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>

#include "myentity.h"
#include "player.h"

/// @brief The MyScene class is the Scene implementation.
class MyScene : public Scene
{
public:
	/// @brief Constructor
	MyScene();
	/// @brief Destructor
	virtual ~MyScene();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void SetupHexGrid();

	size_t findnearest(Point2 pos)
	{
		size_t n = 0;
		float shortest = 100000.0f;
		size_t counter = 0;
		for (size_t y = 0; y < 58; y++) {
			for (size_t x = 0; x < 21; x++) {
				Vector2 p = Vector2(hexagons[counter]->position, pos);
				float d = p.getLength();
				if (d < shortest) {
					shortest = d;
					n = counter;
				}
				counter++;
			}
		}
		return n;
	}


private:
	//MyEntity* hexagon;
	std::vector<MyEntity*> hexagons;
	Player* player;
};

#endif /* SCENE00_H */
