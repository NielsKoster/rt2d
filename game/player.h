#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>
#include "hexagon.h"

class Player : public Entity
{
public:
	/// @brief Constructor
	Player();
	/// @brief Destructor
	virtual ~Player();

	Vector2 NavigateToPoint(Vector2 beginpos, Hexagon* despos, float deltaTime);

	std::vector<Vector2> availableroutes;

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	std::vector<RGBAColor> colors;

private:
	
};

#endif /* PLAYER_H */
