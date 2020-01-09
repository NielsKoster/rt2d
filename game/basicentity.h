#ifndef BASICENTITY_H
#define BASICENTITY_H

#include <entity.h>

class Basicentity : public Entity
{
public:
	/// @brief Constructor
	Basicentity();
	/// @brief Destructor
	virtual ~Basicentity();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
};

#endif /* BASICENTITY_H */
