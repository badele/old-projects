/*
  Auteur : Bruno Adele
  Date : 10/11/2002
  Desc : Classe graphique
*/

#ifndef __Tgraphics_H__
#define __Tgraphics_H__

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "canvas.h"

#define ALIGN_LEFT 	0x01
#define ALIGN_RIGHT	0x02
#define ALIGN_CENTER 	0x04
#define ALIGN_TOP	 	0x08
#define ALIGN_BOTTOM 	0x10
#define ALIGN_MIDDLE 	0x20


void 		DrawImage(TCanvas* canvas,int x,int y,TImage* img);
void 		DrawImageEx(TCanvas* canvas,SDL_Rect rect,TImage* img,int align);
void 		DrawRect(TCanvas* canvas,SDL_Rect rectangle);
SDL_Rect 	GetTextSize(TFont* font,char* message);
void 		DrawText(TCanvas* canvas,int x,int y,char* message);
void 		DrawTextEx(TCanvas* canvas,SDL_Rect rect,int align,char* message);

#endif
