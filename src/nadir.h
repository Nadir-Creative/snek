#ifndef NADIR_H
#define NADIR_H

#include "raylib.h"
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>

#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0

#define MODE_HI 0
#define MODE_MID 1
#define MODE_LO 2

typedef struct nFont
{
	Texture t;
	Rectangle clip;
} nFont;

void nInit(char *title, uint8_t mode);
void nUpdateInternals();
void nBeginDrawing();
void nEndDrawing();
void nQuit();

uint32_t nGetMouseX();
uint32_t nGetMouseY();
float nGetWidth();
float nGetHeight();
float nDelta();
int32_t nrand(int32_t min, int32_t max);
float nrandf(float min, float max);

nFont nLoadFont(const char *filename);
void nPrint(char *s, nFont *font, int32_t x, int32_t y, Color c);
void nSysPrint(char *s, int32_t x, int32_t y, Color c);

#endif // NADIR_H
