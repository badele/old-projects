/*
  Auteur : Bruno Adele
  Date : 16/11/2002
  Desc : Déclaration de la classe Menu
*/

#ifndef __TMenu_H__
#define __TMenu_H__

#include <SDL/SDL.h>

#include "canvas.h"
#include "font.h"
#include "graphics.h"
#include "image.h"


class TMenuItem
{
public:
	string 	Caption;
	void* 	Data;
	TImage* Image;
	TMenuItem(string caption,TImage* image=NULL,void* data = NULL);
};

class TMenu
{
	private :

	TCanvas* 	FCanvas;
	TFont*		FFont;
	int			FFontHeight;
	int			FMaxImageWidth,FMaxImageHeight;
	TList*		FList;
	int 		FItemIndex,FTopIndex;
	SDL_Rect	FRect;
	int			FArrowHeight;
	
	SDL_Rect 	GetRectSelected(int AItemIndex);
	SDL_Rect 	GetRectText(int AItemIndex);
	SDL_Rect 	GetRectIcon(int AItemIndex);
	SDL_Rect 	GetRectArrowBottom();
	SDL_Rect 	GetRectArrowUp();

	public :

	TMenu(TCanvas* canvas) ;
	int 		Marge;
	Uint32 		Color,BackgroundColor;
	bool		ShowBackground;


	void		Add(TMenuItem* menutiem);
	void 		Add(string caption,TImage* image=NULL,void* data= NULL);
	void 		Draw();
	void 		Next();
	void 		Prev();
	void 		setFont(TFont* font);
	TFont* 		getFont();
	SDL_Rect* 	getRect();	
	int 		getMaxiShow();
	

} ;

#endif
