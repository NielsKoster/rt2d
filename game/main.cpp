/**
 * Copyright 2020 Niels Koster 
 *
 * @brief ColorClicker.
 *
 * @file main.cpp
 *
 * @mainpage ColorClicker
 *
 * @section intro Introduction

 * Colorclicker is a game where the goal is to move a hexagon to other hexagons.	

 * If you select the right color when over another hexagon and you just happen to press space, ya get a point.
 * If you press space and the if statement above aint true, there are only negative points for you.
 * This game only really lasts 30 seconds per session, but it's pretty interesting seeing how 'high' your 'score' really can get. 
 * 
 * There's even a second paragraph.
 */

#include <rt2d/core.h>

#include "defaultscene.h"

/// @brief main entry point
int main( void )
{
	// Core instance
	Core core;

	// Scene01
	DefaultScene* defaultscene = new DefaultScene(); // create Scene on the heap
	while(defaultscene->isRunning()) { // check status of Scene every frame
		core.run(defaultscene); // update and render the current scene
		core.showFrameRate(10); // show framerate in output every n seconds
	}
	core.cleanup(); // cleanup ResourceManager (Textures + Meshes, but not Shaders)
	delete defaultscene; // delete Scene and everything in it from the heap to make space for next Scene

	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	return 0;
}
