/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"
#include "player.h";

MyScene::MyScene() : Scene()
{
	hexagons = std::vector<MyEntity*>();
	SetupHexGrid();
	player = new Player();
	this->addChild(player);
	player->position.x = 360;
	player->position.y = 480;
}


MyScene::~MyScene()
{
	for (int i = 0; i < hexagons.size(); i++) 
	{
		delete hexagons[i];
	}

	delete player;
}

void MyScene::SetupHexGrid() {

	float hexoffsetx = 0;
	float hexoffsety = 0;

	float counter = 0;

	//float hexwidth = SWIDTH;
	//float hexheight = SWIDTH;


	float spriteheight = 0.12;
	float spritewidth = spriteheight * 1.5;

	bool offsetline = false;

	for (int column = 0; column < 58; column = column + 1) {
		for (int rows = 0; rows < 21; rows = rows + 1) {
			MyEntity* hexagon = new MyEntity();
			hexagons.push_back(hexagon);
			this->addChild(hexagon);
			counter++;
			hexagon->scale = Point2(spritewidth, spriteheight);
			hexagon->position.x = hexagon->position.x + hexoffsetx;
			hexagon->position.y = hexagon->position.y + hexoffsety;

			hexoffsetx += 64;
		}

		//Check if the line needs an offset
		if (offsetline == false) {
			offsetline = true;
		}
		else {
			offsetline = false;
		}

		//Horizontal row is full, make a new column
		hexoffsety += 12.95;

		//If the line is a line that needs an offset, give it an offset
		if (offsetline) {
			hexoffsetx = 32;
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

	//Get mouse coordinates
	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();
	//Combine them into a Point2
	Point2 mousepos = Point2(mousex, mousey);
	//Find the nearest hexagon to the mouse
	size_t activeid = findnearest(mousepos);

	for (int j = 0; j < hexagons.size(); j++) {
		if (hexagons[j] == hexagons[activeid] && input()->getMouse(0))
		{
			hexagons[j]->Selected();
		}

		else if (hexagons[j] == hexagons[activeid]) {
			hexagons[j]->Highlighted();
		}
		
		else 
		{
			hexagons[j]->Unselected();
		}
	}
}
