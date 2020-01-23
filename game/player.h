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

	Basicentity* playericon;

	Vector2 NavigateToPoint(Vector2 beginpos, Hexagon* despos, float deltaTime);

	void iconmovement(float deltaTime);

	void showpoints(int points);

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	std::vector<RGBAColor> colors;

private:
	bool faded;
};

#endif /* PLAYER_H */
