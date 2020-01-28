/**
 * Copyright 2020 Niels Koster
 *
 * @file defaultscene.h
 *
 * @brief description of defaultscene behavior.
 */

#ifndef DEFAULTSCENE_H
#define DEFAULTSCENE_H

#include <rt2d/scene.h>

#include "hexagon.h"
#include "player.h"
#include "button.h"
#include "basicentity.h"
#include <text.h>
#include <iomanip>

/// @brief The MyScene class is the Scene implementation.
class DefaultScene : public Scene
{
public:
	/// @brief Constructor
	DefaultScene();
	/// @brief Destructor
	virtual ~DefaultScene();

	void addColors();

	void UISetup();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void SetupHexGrid();

	void AssignColors();

	void updatescore(int);

	void updateTime(double);

	void enableMenu();

	void pathfinding(float deltaTime);

	void checkInputs(float deltaTime);

	void checkMenuButtons();

	void toggleTimer();

	void endScreen();

	void toggleMainMenu();

	void checkHighscore();

	void retry();

	size_t findnearest(Point2 pos)
	{
		size_t n = 0;
		float shortest = 100000.0f;
		size_t counter = 0;
		for (size_t y = 0; y < 56; y++) {
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
	Hexagon* hexagon;
	std::vector<Hexagon*> hexagons;
	Player* player;
	Basicentity* menu;
	Button* mainmenubutton;
	Button* quitbutton;
	bool menuselected;
	bool findpath;
	Hexagon* destination;
	int colorCounter;
	int randomTileCounter;
	int randomtileMax;
	int points;
	int maxtargets;
	int highscore;
	std::vector<Text*> text;
	Text* menutext;
	Basicentity* menushade;
	Point2 mousepos;
	Text* scoreLine;
	Text* timeLine;
	Text* highscoreLine;
	Basicentity* pauseicon;
	Timer* timer;
	std::stringstream timestream;
	Basicentity* mainmenubg;
	Button* playbutton;
	Button* retrybutton;
	bool mainmenuselected;
	bool endscreenselected;
	Basicentity* logo;
};

#endif /* DEFAULTSCENE_H */
