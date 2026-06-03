// NADIR ENGINE!
// 2026-05-27:
// Goal is to make a very simple engine that I can use to make simple games and apps in C very quickly.
// Right now, just focus on your own shit.
// Later on, goal will shift to make a more robust engine thing... Currently, just want a base for making games and shit...

#include <stdio.h>
#include "nadir.h"
#include "app.h"
#include "app-startup.h"
#include "app-title.h"

// GLOBAL VARIABLES---------------------------------------------
#define APP_DEBUG 1

uint8_t g_running = 1;
AppState g_state = APP_STARTUP;

// Testing Stuff
Texture2D test;

// Internal State Stuff:

void appPlaying()
{
	
}

void appMenu()
{
	// Handle input options and draw the menu
	
	
}

void appIntro()
{
	// Play 'nadir' logo and then switch to menu intro:
	
}
// INTERNAL FUNCTIONS-------------------------------------------
void init()
{
	nInit("Test Window", MODE_LO);
	InitAudioDevice();
	startupInit();
	titleInit();
	// All of the 'states' will have their own 'init' function to call that will load all their crap.
	
	// Testing Stuff:
	test = LoadTexture("pxa_db_font.png");
}

int main()
{
	if(APP_DEBUG)
	{
		g_state = APP_TITLE;
	}
	init();

	// Testing Shit here:
		
	while(g_running)
	{
		// Should be a switch statement that sends all input handling, processing and drawing to some state-driven version of those things.
		// IE: The main menu processing handles the animations / selections / drawing of the main menu screen
		// The game-play state functions handle the processing of player input, drawing the game screen, etc.
		// So the state could very well be set up in different files for the state...

		//Update internals and then update app based on state switch:
		nUpdateInternals();
		if(WindowShouldClose())
			g_state = APP_EXIT;
		switch(g_state)
		{
			case APP_STARTUP:{
				//printf("test ");
				g_state = startupUpdate();
				startupDraw();
			} break;
			case APP_TITLE:{
				g_state = titleUpdate();
				titleDraw();
			} break;
			case APP_PLAYING:{
				nBeginDrawing(); 
				ClearBackground(BLACK);
				nEndDrawing();
			} break;
			case APP_EXIT:{
				g_running = 0;
				// Unload all the things from memory
			} break;
			default: {
				// unreachable
			}
		}
		
	}

	
	nQuit();
}
