#ifndef BUTTON_H
#define BUTTON_H

#include <entity.h>

class Button : public Entity
{
public:
	/// @brief Constructor
	Button();
	/// @brief Destructor
	virtual ~Button();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void OnClick();

private:
};

#endif /* BUTTON_H */
