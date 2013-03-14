/*
  Auteur : Bruno Adele
  Date : 10/11/2002
  Desc : Classe qui simule un affichage des fonctions sur un televiseur
*/


/* TODO
	- Renomer OSD en Terminal (simule un terminal, par les touche power(on|off),up/down, etc..
*/

#include <time.h>
#include <iostream.h>
#include <SDL/SDL.h>
#include "osd.h"
#include "graphics.h"

TOsd :: TOsd( SDL_Surface *screen )
{
	this->screen = screen ;

	/* penser à faire les SDL_free !!! */
	
	FCanvas = SDL_AllocSurface(SDL_SWSURFACE, screen->w, screen->h,
                          screen->format->BitsPerPixel,
                          screen->format->Rmask, screen->format->Gmask,
                          screen->format->Bmask,screen->format->Amask);

//	Uint32 trans = SDL_MapRGB(FCanvas->format,255,0,255);
//	SDL_SetColorKey(FCanvas,SDL_SRCCOLORKEY,trans);
	
	
	sizesurface.x = sizesurface.y =0;
	sizesurface.w=screen->w;
	sizesurface.h=screen->h;
	
	FElapsed = 0;
	
	Canvas = new TCanvas(screen);
	Canvas->Fonts->LoadObject("../skins/fonts/vixar.ttf;36");
	Canvas->Fonts->LoadObject("../skins/fonts/vixar.ttf;18");
	
}


void TOsd::Init()
{
	ItemIndex = 1;
	/* On cache le curseur de la souris (on en a pas besoin) */
	SDL_ShowCursor(SDL_DISABLE) ;

	SDL_EnableKeyRepeat(2,1) ;



	return  ;
}

void TOsd :: Next()
{
	ItemIndex++;
}

void TOsd :: Prev()
{
	ItemIndex--;
}


void TOsd::MyUpdate()
{

	SDL_BlitSurface(FCanvas, &sizesurface, screen, &sizesurface);
	SDL_UpdateRects(screen,1,&sizesurface);
}


void TOsd::Update()
{

	SDL_BlitSurface(FCanvas, &sizesurface, screen, &sizesurface);
	SDL_UpdateRects(screen,1,&sizesurface);
}

void TOsd::Elapsed()
{
	FElapsed++;
}

 void TOsd::DrawHorloge() 
{
	SDL_Rect tmp_rect;
	
	time_t t = time(&t); 
	char heure[9]; 

	Canvas->Font = 	(TFont*)Canvas->Fonts->LoadObject("../skins/fonts/vixar.ttf;36");
	strftime(heure, 9, "%H:%M:%S", (struct tm *)localtime(&t)); 
	tmp_rect = GetTextSize(Canvas->Font,"00:00:00");
	Canvas->Font->Color.r =  255;
	Canvas->Font->Color.g =  255;
	Canvas->Font->Color.b =  255;
	Canvas->Font->Alpha =  100;
	DrawText(Canvas,790-tmp_rect.w,590-tmp_rect.h,heure);
//	DrawText(Canvas,rect,align,heure);
	
} 


void TOsd::DrawBackground()
{
	// Déssine le fond
	DrawImage(Canvas,0,0,(TImage*)Canvas->Images->LoadObject("../skins/images/fond1.png"));
	
	// Désine le logo
	SDL_Rect img_rectlogo;
	img_rectlogo.x = 0;
	img_rectlogo.y = 20;
	img_rectlogo.w = 730;
	img_rectlogo.h = 100;
	DrawImageEx(Canvas,img_rectlogo,(TImage*)Canvas->Images->LoadObject("../skins/images/boxtv.png"),ALIGN_RIGHT | ALIGN_TOP);
	
/*	// Affiche titre
	SDL_Rect rect;
	rect.x =rect.y = 10;
	rect.w=790;
	rect.h=80;
	Canvas->Color = SDL_MapRGB(FCanvas->format,255,255,255);
	Canvas->Alpha = 100;
	DrawRect(Canvas,rect);	
	
	Canvas->Font = (TFont*)Canvas->Fonts->LoadObject("../skins/fonts/vixar.ttf;18");
	Canvas->Font->Color.r =  0;
	Canvas->Font->Color.g =  0;
	Canvas->Font->Color.b =  0;
	Canvas->Font->Alpha =  255;

	DrawTextEx(Canvas,rect,ALIGN_CENTER | ALIGN_MIDDLE,"MAGNETO");*/
	
	DrawHorloge();

}

void TOsd::DrawForeground()
{
	// Déssine le fond
//	DrawImage(img_background,0,0);

	SDL_Rect rect;
	rect.x = 50;
	rect.y = 50;
	rect.w =  50+FElapsed;
	rect.h =60;

//	DrawRect(FCanvas,rect,SDL_MapRGB(FCanvas->format,255,255,255),255);	


}







/*void TOsd::DrawImage(SDL_Surface *img,int x,int y)
{
	SDL_Rect img_rect;
	img_rect.x = x;
	img_rect.y = y;
	img_rect.w=x+img_background->w;
	img_rect.h=y+img_background->h;

	SDL_BlitSurface(img, &sizesurface, FCanvas, &sizesurface);

}*/


int TOsd::getItemIndex()
{
	return ItemIndex;
}

SDL_Surface* TOsd::getCanvas()
{
	return FCanvas;
}


