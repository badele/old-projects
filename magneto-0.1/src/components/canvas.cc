
#include <iostream.h>
#include <stdlib.h>

#include "canvas.h"



TCanvas::TCanvas(SDL_Surface * screen)
{
	
	FScreen = screen;
	
	// Création de la surface
	FSurface = SDL_AllocSurface(SDL_SWSURFACE, screen->w, screen->h,
                          screen->format->BitsPerPixel,
                          screen->format->Rmask, screen->format->Gmask,
                          screen->format->Bmask,screen->format->Amask);

	FRect.x = FRect.y =0;
	FRect.w=screen->w;
	FRect.h=screen->h;
	
	// Création de la fonte
//	Font = new TFont("../skins/fonts/vixar.ttf",18);
	Fonts = new TFonts();
	Images = new TImages();
}

TCanvas::~TCanvas()
{
	delete Fonts;
	delete Images;
	SDL_FreeSurface(FSurface);
//	TTF_CloseFont(Font->getFont());
}

void TCanvas::Update()
{
	SDL_BlitSurface(FSurface, &FRect, FScreen, &FRect);
	SDL_UpdateRects(FScreen,1,&FRect);

	/*SDL_BlitSurface(FSurface, NULL, FScreen, NULL);
	SDL_UpdateRects(FScreen,1,NULL);*/
}


SDL_Rect* TCanvas::getRect()
{
	return &FRect;
}

SDL_Surface* TCanvas::getSurface()
{
	return FSurface;
}




