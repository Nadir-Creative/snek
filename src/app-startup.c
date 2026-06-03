#include "app-startup.h"

// Stores all the data required for the startup state, and loads all the things...
// GLOBALS --------------------
uint8_t current_note = 0;
float timer[6] = {0.5, 0.8, 1.1, 1.4, 1.7, 2.5};
float duration = 0.0;
float end = 5.0;
#define NAD_LOGO_SCALE 6
Texture2D logo;
Rectangle logo_clip = {0, 0, 3, 6};
Rectangle logo_target = {40, 60, 18, 36};
char *phrase;
Sound note_nr, note_ai, note_d, note_dot;

#define NUM_PHRASES 17
char phrases[NUM_PHRASES][32] = {
	"just the worst",
	"make it stop!",
	"terrible",
	"I hate it!",
	"bottom of the barrel",
	"disappointing",
	"OH NO!!!!",
	"garbage",
	"painfully bad",
	"this sucks",
	"not good",
	"pure crap",
	"this stinks!",
	"MEDIOCRE!",
	"disgusting",
	"just awful",
	"what a disaster!"
};

void startupInit()
{
	// load nadir texture
	logo = LoadTexture("./gfx/nad_logo.png");
	// load sounds
	note_nr = LoadSound("./sfx/note_nr.wav");
	note_ai = LoadSound("./sfx/note_ai.wav");
	note_d = LoadSound("./sfx/note_d.wav");
	note_dot = LoadSound("./sfx/note_dot.wav");

	phrase = phrases[nrand(0, NUM_PHRASES-1)];
}

AppState startupUpdate()
{
	duration += nDelta();
	if(current_note > 5)
	{
		// last note has played, so we check to see if end has been reached:
		if (duration > end)
		{
			return APP_TITLE;
		}
	}
	else if(duration > timer[current_note])
	{
		switch(current_note)
		{
			case 0: {
				PlaySound(note_nr);
			} break;
			case 1: {
				PlaySound(note_ai);
				logo_clip.width = 7;
				logo_target.width = logo_clip.width * NAD_LOGO_SCALE;
			} break;
			case 2: {
				PlaySound(note_d);
				logo_clip.width = 11;
				logo_target.width = logo_clip.width * NAD_LOGO_SCALE;
			} break;
			case 3: {
				PlaySound(note_ai);
				logo_clip.width = 13;
				logo_target.width = logo_clip.width * NAD_LOGO_SCALE;
			} break;
			case 4: {
				PlaySound(note_nr);
				logo_clip.width = 16;
				logo_target.width = logo_clip.width * NAD_LOGO_SCALE;
			} break;
			case 5: {
				PlaySound(note_dot);
				logo_clip.height = 8;
				logo_target.height = logo_clip.height * NAD_LOGO_SCALE;
			} break;
			default: break;
		}
		current_note += 1;
	}
	return APP_STARTUP;
}

void startupDraw()
{
	nBeginDrawing();
		ClearBackground(BLACK);
		if(current_note > 0)
			DrawTexturePro(logo, logo_clip, logo_target, (Vector2){0, 0}, 0.0, WHITE);
		if(current_note > 5)
			nSysPrint(phrase, 123, 95, RED);
	nEndDrawing();
}
