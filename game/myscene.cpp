/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"
#include "player.h";
#include "button.h";

MyScene::MyScene() : Scene()
{
	hexagons = std::vector<MyEntity*>();
	SetupHexGrid();
	player = new Player();
	menu = new MyEntity();
	mainmenubutton = new Button();
	quitbutton = new Button();
	bool menuselected;

	this->addChild(player);
	player->position.x = hexagons[600]->position.x;
	player->position.y = hexagons[600]->position.y - 5;

	//Menu's
	this->addChild(menu);
	this->addChild(mainmenubutton);
	this->addChild(quitbutton);

	menu->addSprite("assets/color.tga");
	mainmenubutton->addSprite("assets/mainmenubutton.tga");
	quitbutton->addSprite("assets/quitbutton.tga");

	menu->position.x = 9999;
	mainmenubutton->position.x = 9999;
	quitbutton->position.x = 9999;
	
	menu->position.y = SHEIGHT / 2;
	mainmenubutton->position.y = SHEIGHT / 2;
	quitbutton->position.y = SHEIGHT / 2;
	
	menu->scale = Point2(1, 1.5);
	mainmenubutton->scale = Point2(0.75, 0.75);
	quitbutton->scale = Point2(0.75, 0.75);
}

MyScene::~MyScene()
{
	for (int i = 0; i < hexagons.size(); i++) 
	{
		delete hexagons[i];
	}

	delete player;
	delete menu;
	delete mainmenubutton;
	delete quitbutton;
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
	}
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key puts menu on screen
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		if (menu->position.x != SWIDTH / 2) {
			menu->position.x = SWIDTH / 2;
			mainmenubutton->position.x = SWIDTH / 2;
			quitbutton->position.x = SWIDTH / 2;

			mainmenubutton->position.y = (SHEIGHT / 2);
			quitbutton->position.y = (SHEIGHT / 2) + 125;
			menuselected = true;
		} 
		else {
			menu->position.x = 9999;
			mainmenubutton->position.x = 9999;
			quitbutton->position.x = 9999;
			menuselected = false;
		}
	}

	//Get mouse coordinates
	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();
	//Combine them into a Point2
	Point2 mousepos = Point2(mousex, mousey);

	if (!menuselected) {
		//Find the nearest hexagon to the mouse
		size_t activeid = findnearest(mousepos);

		//Search through all hexagons 
		for (int j = 0; j < hexagons.size(); j++) {
			//If a the mouse hovers over a hexagon and the player clicks the left mouse button...
			if (hexagons[j] == hexagons[activeid] && input()->getMouse(0))
			{
				//Select that hexagon
				hexagons[j]->Selected();
				//Only do the calculation for the new path once 
				if (hexagons[j] == hexagons[activeid] && input()->getMouseDown(0)) {
					//Let player calculate a path to the destination
					//std::cout << player->NavigateToPoint(hexagons[j]->position) << std::endl;
					player->NavigateToPoint(hexagons[j]->position);
				}
			}
			//If the payer 
			else if (hexagons[j] == hexagons[activeid]) {
				hexagons[j]->Highlighted();
			}

			//If neither are true, then just keep it as a gray hexagon
			else
			{
				hexagons[j]->Unselected();
			}
		}
	}
}
