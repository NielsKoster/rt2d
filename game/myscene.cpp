/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	SetupHexGrid();
}


MyScene::~MyScene()
{
	this->removeChild(hexagon);
	delete hexagon;
}

void MyScene::SetupHexGrid() {

	float hexoffsetx = 0;
	float hexoffsety = 0;

	//float hexwidth = SWIDTH;
	//float hexheight = SWIDTH;

	float spriteheight = 0.5;
	float spritewidth = spriteheight * 1.5;

	bool offsetline = false;

	for (int column = 0; column < 60; column = column + 1) {
		for (int rows = 0; rows < 50; rows = rows + 1) {
			hexagon = new MyEntity();
			this->addChild(hexagon);
			hexagon->scale = Point2(spritewidth, spriteheight);
			hexagon->position.x = hexagon->position.x + hexoffsetx;
			hexagon->position.y = hexagon->position.y + hexoffsety;

			hexoffsetx += 60;
		}

		//Check if the line needs an offset
		if (offsetline == false) {
			offsetline = true;
		}
		else {
			offsetline = false;
		}

		//Horizontal row is full, make a new column
		hexoffsety += 12.5;

		//If the line is a line that needs an offset, give it an offset
		if (offsetline) {
			hexoffsetx = 30;
		}
		else {
			hexoffsetx = 0;
		}

		std::cout << "Hexagons placed!" << std::endl;
	}
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}
}
