#include "nadir.h"

// GLOBALS --------------------------------------------------------
// window
float g_width = 320;
float g_height = 180;
Rectangle g_screen;
Rectangle g_target;
RenderTexture2D g_screen_texture;
uint8_t g_mode;

float g_mousex;
float g_mousey;

float g_dt;

nFont g_font;

// INIT & WINDOW SHIT -----------------------------------------------
void nInit(char *title, uint8_t mode)
{
	SetTraceLogLevel(LOG_NONE);
	switch(mode)
	{
		case MODE_HI: 
		{
			InitWindow(1280, 720, title);
			g_width = 640;
			g_height = 360;
		} break;
		case MODE_MID:
		{
			InitWindow(960, 540, title);
			g_width = 480;
			g_height = 270;
		}  break;
		case MODE_LO: 
		{
			InitWindow(1280, 720, title);
			g_width = 320;
			g_height = 180;
		} break;
		default: {}
	}
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);

	g_screen_texture = LoadRenderTexture(g_width, g_height);
	g_screen = (Rectangle){0, 0, g_width, -g_height};
	g_font = nLoadFont("./gfx/default_font.png");
	
	// Setup random number generation.
	srand(time(0));
}

void nUpdateInternals() // This will be where I update all the states and shit / dt / keyboard / joy / etc
{
	// DeltaTime
	g_dt = GetFrameTime(); // I dunno if this is stable, so I want to have a set time here for all update code.
	// check for screen resize:
	float w = GetRenderWidth();
	float h = GetRenderHeight();
	if (w < 1 || h < 1)
	{
		g_target.x = 0; g_target.y = 0; g_target.width = 0; g_target.height = 0;
	}
	float ratio;
	float mratio;
	if (w/g_width < h/g_height) // Favor width
	{
		ratio = w/g_width;
		mratio = g_width / w;
		g_target.width = g_width * ratio;
		g_target.height = g_height * ratio;
		g_target.y = (h - g_target.height) / 2;
	}
	else // Favor height
	{
		ratio = h/g_height;
		mratio = g_height / h;
		g_target.width = g_width * ratio;
		g_target.height = g_height * ratio;
		g_target.x = (w - g_target.width) / 2;
		}
	// check for mouse movement and convert to our pixelspace:
	g_mousex = ((GetMouseX() * mratio) - (g_target.x * mratio));
	g_mousey = ((GetMouseY() * mratio) - (g_target.y * mratio));
}

void nBeginDrawing()
{
	BeginTextureMode(g_screen_texture);
}

void nEndDrawing()
{
	EndTextureMode();
	BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(g_screen_texture.texture, g_screen, g_target, (Vector2){0, 0}, 0, WHITE);
	EndDrawing();
}
// ONERS -----------------------------------------
uint32_t nGetMouseX() {return g_mousex;}
uint32_t nGetMouseY() {return g_mousey;}
float nDelta() {return g_dt;}
float nGetWidth() {return g_width;}
float nGetHeight() {return g_height;}

int32_t nrand(int32_t min, int32_t max)
{
	return rand() % (max-min+1) + min;
}

float nrandf(float min, float max) // TODO: Make floating Point rand() function to work...
{
	return min+max;
}

nFont nLoadFont(const char *filename)
{
	nFont font;
	font.t = LoadTexture(filename);
	font.clip.x = 0;
	font.clip.y = 0;
	font.clip.width = font.t.width / 16;
	font.clip.height = font.t.height / 16;
	return font;
}

void nPrint(char *s, nFont *font, int32_t x, int32_t y, Color c)
{
	int32_t i=0;
	while(s[i]!='\0')
	{
		font->clip.x=(s[i]%16)*font->clip.width;
		font->clip.y=(s[i]/16)*font->clip.height;
		DrawTexturePro(font->t, font->clip, (Rectangle){x+(font->clip.width*i), y, font->clip.width, font->clip.height}, (Vector2){0, 0}, 0, c);
		i++;
	}
}

void nSysPrint(char *s, int32_t x, int32_t y, Color c)
{
	int32_t i=0;
	while(s[i]!='\0')
	{
		g_font.clip.x=(s[i]%16)*g_font.clip.width;
		g_font.clip.y=(s[i]/16)*g_font.clip.height;
		DrawTexturePro(g_font.t, g_font.clip, (Rectangle){x+(g_font.clip.width*i), y, g_font.clip.width, g_font.clip.height}, (Vector2){0, 0}, 0, c);
		i++;
	}
}

void nQuit()
{
	UnloadRenderTexture(g_screen_texture);
	CloseWindow();
}
