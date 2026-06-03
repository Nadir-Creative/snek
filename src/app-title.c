#include "app-title.h"

// Globals ------------------------------------
typedef enum TitleState
{
	T_INTRO,
	T_MENU,
	T_THANKS,
	T_OUTRO
} TitleState;
TitleState  tstate = T_INTRO;
AppState next_state;

Texture snek_logo, menu_play, menu_thanks, menu_quit, menu_select;
// music track
Sound sound_move, sound_select;
int m_loc = 100, m_fade = 0, outro_timer = 255;
bool show_select = true;

// functions -----------------

void titleInit()
{
	snek_logo = LoadTexture("./gfx/snek_logo.png");
	menu_play = LoadTexture("./gfx/menu_play.png");
	menu_thanks = LoadTexture("./gfx/menu_thanks.png");
	menu_quit = LoadTexture("./gfx/menu_quit.png");
	menu_select = LoadTexture("./gfx/menu_select.png");
	// load sounds
	sound_move = LoadSound("./sfx/menu_move.wav");
	sound_select = LoadSound("./sfx/menu_select.wav");
}

AppState titleUpdate()
{
	switch(tstate)
	{
		case T_INTRO:{
			if(m_fade == 255)
			{
				// start to play music track looped
			}
		}break;
		case T_MENU:{
			if(IsKeyPressed(KEY_DOWN))
			{
				PlaySound(sound_move);
				m_loc += 20;
				if (m_loc == 160){m_loc = 100;}
			}
			if(IsKeyPressed(KEY_UP))
			{
				PlaySound(sound_move);
				m_loc -= 20;
				if (m_loc == 80){m_loc = 140;}
			}
			if(IsKeyPressed(KEY_ENTER))
			{
				PlaySound(sound_select);
				if(m_loc == 100)
				{
					tstate = T_OUTRO;
					next_state = APP_PLAYING;
				}
				else if(m_loc == 120)
				{
					tstate = T_THANKS;
				}
				else if(m_loc == 140)
				{
					tstate = T_OUTRO;
					next_state = APP_EXIT;
				}
			}
		}break;
		case T_THANKS:{
			if(IsKeyPressed(KEY_ENTER))
			{
				tstate = T_MENU;
			}
		}break;
		case T_OUTRO:{
			if(outro_timer % 15 == 0)
			{
				show_select = !show_select;
			}
			outro_timer -= 5;
			if(outro_timer < 0)
			{
				return next_state;
			}
		}break;
		default:{
			// unreachable
		}
	}
	return APP_TITLE;
}

void titleDraw()
{
	nBeginDrawing();
	ClearBackground(BLACK);
	switch(tstate)
	{
		case T_INTRO:{
			DrawTexture(snek_logo, (nGetWidth() - snek_logo.width)/2, 10, (Color){m_fade, m_fade, m_fade, 255});
			m_fade+=5;
			if(m_fade>255){tstate = T_MENU;}
		}break;
		case T_MENU:{
			DrawTexture(snek_logo, (nGetWidth() - snek_logo.width)/2, 10, WHITE);
			DrawTexture(menu_play, (nGetWidth() - menu_play.width)/2, 100, WHITE);
			DrawTexture(menu_thanks, (nGetWidth() - menu_thanks.width)/2, 120, WHITE);
			DrawTexture(menu_quit, (nGetWidth() - menu_quit.width)/2, 140, WHITE);
			DrawTexture(menu_select, 90, m_loc, WHITE);
		}break;
		case T_THANKS:{
			
		}break;
		case T_OUTRO:{
			if(outro_timer<0)
				break;
			DrawTexture(snek_logo, (nGetWidth() - snek_logo.width)/2, 10, (Color){outro_timer, outro_timer, outro_timer, 255});
			DrawTexture(menu_play, (nGetWidth() - menu_play.width)/2, 100, (Color){outro_timer, outro_timer, outro_timer, 255});
			DrawTexture(menu_thanks, (nGetWidth() - menu_thanks.width)/2, 120, (Color){outro_timer, outro_timer, outro_timer, 255});
			DrawTexture(menu_quit, (nGetWidth() - menu_quit.width)/2, 140, (Color){outro_timer, outro_timer, outro_timer, 255});
			if(show_select)
			{
				DrawTexture(menu_select, 90, m_loc, (Color){outro_timer, outro_timer, outro_timer, 255});
			}
		}break;
		default:{
			// unreachable
		}
	}
		
	nEndDrawing();
}
