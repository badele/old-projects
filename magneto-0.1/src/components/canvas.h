/*
  Auteur : Bruno Adele
  Date : 10/11/2002
  Desc : Classe qui permet d'avoir un canvas
*/

#ifndef __TCanvas_H__
#define __TCanvas_H__

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "font.h"
#include "image.h"

class TCanvas
{
	private :

	SDL_Surface *FScreen;
	SDL_Surface *FSurface;
	SDL_Rect FRect;

	public :

	Uint32 		Color;
	TFont* 		Font;
	TFonts*		Fonts;
	TImages* 	Images;

	Uint8	Alpha;
	
	TCanvas(SDL_Surface * screen);
	TCanvas::~TCanvas();
	void Update();

	// Lecture des propriétées
	SDL_Rect* 		getRect();
	SDL_Surface* 	getSurface();

} ;



#endif
