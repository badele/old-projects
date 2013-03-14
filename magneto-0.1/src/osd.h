/*
  Auteur : Bruno Adele
  Date : 10/11/2002
  Desc : Classe qui simule un affichage des fonctions sur un televiseur
*/

#ifndef __TOsd_H__
#define __TOsd_H__

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "canvas.h"


class TOsd
{
	private :

	
	SDL_Surface *screen;
	SDL_Surface *FCanvas;
	SDL_Rect sizesurface;
	int ItemIndex;
	int FElapsed;



	public :

	TCanvas *Canvas;
	SDL_Surface *text;


	/* Constructeur : prend en paramètre la SDL_Surface représentant l'écran du jeu */
	TOsd(SDL_Surface *screen) ;


	/* Initialise quelques parametres du jeu */
	void Init() ;


	//void DrawImage(SDL_Surface *img,int x,int y);
	void Update();
	void MyUpdate();
	void DrawBackground();
	void DrawForeground();
	void DrawHorloge() 	;
	void Elapsed();
//	void DrawRect(SDL_Rect rectangle,Uint32 color,Uint8 alpha=0);

	void Next();
	void Prev();
	int getItemIndex();
	SDL_Surface* getCanvas();

	
	

} ;

#endif
