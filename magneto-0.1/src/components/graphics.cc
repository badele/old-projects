
#include "graphics.h"

#include <iostream.h>
#include <stdlib.h>



//#include <SDL/SDL.h>

/* TODO
	- essayer de trouver comment faire pour superposer des canvas en gerant la tansparence et l'alpha blending
*/

// ----------------------------------------------------------------------------
// DrawImage - Dessine une image
// ----------------------------------------------------------------------------
void DrawImage(TCanvas* canvas,int x,int y,TImage* img)
{
	SDL_Rect img_rect,dest_rect;
	img_rect.x = 0;
	img_rect.y = 0;
	img_rect.w=img->getSurface()->w;
	img_rect.h=img->getSurface()->h;
	
	dest_rect.x = x;
	dest_rect.y = y;

	SDL_BlitSurface(img->getSurface(), &img_rect, canvas->getSurface(), &dest_rect);
}

// ----------------------------------------------------------------------------
// DrawImage - Dessine une image avec des fonction étendu
// ----------------------------------------------------------------------------
void DrawImageEx(TCanvas* canvas,SDL_Rect rect,TImage* img,int align)
{
	int x=0,y=0;
	
	// Alignement horizontal
	if ((align & ALIGN_LEFT) == ALIGN_LEFT) {
		x =rect.x;
	} else if ((align & ALIGN_RIGHT) == ALIGN_RIGHT) {
		x =  rect.w - img->getSurface()->w;
	} else if ((align & ALIGN_CENTER) == ALIGN_CENTER) {
		x =  rect.x+(rect.w - rect.x - img->getSurface()->w)/2;
	}
	
	// Alignement vertical
	if ((align & ALIGN_TOP) == ALIGN_TOP) {
		y= rect.y;
	} else if ((align & ALIGN_BOTTOM) == ALIGN_BOTTOM) {
		y= rect.h - img->getSurface()->h;
	} else if ((align & ALIGN_MIDDLE) == ALIGN_MIDDLE) {
		y =  rect.y+(rect.h - rect.y - img->getSurface()->h)/2;
	}
	
	DrawImage	(canvas,x,y,img);
}



// ----------------------------------------------------------------------------
// DrawRect - Dessine un rectangle
// ----------------------------------------------------------------------------
void DrawRect(TCanvas* canvas,SDL_Rect rectangle)
{
	SDL_Surface * tmp_surface = NULL;

	tmp_surface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA,rectangle.w,rectangle.h,canvas->getSurface()->format->BitsPerPixel,
	canvas->getSurface()->format->Rmask,canvas->getSurface()->format->Gmask,canvas->getSurface()->format->Bmask,canvas->getSurface()->format->Amask);
	if (!tmp_surface) {
		exit(1);
	}
	SDL_FillRect(tmp_surface, NULL, canvas->Color);
	SDL_SetAlpha(tmp_surface,SDL_SRCALPHA,canvas->Alpha);
	SDL_BlitSurface(tmp_surface, &rectangle, canvas->getSurface(), &rectangle);
	
	SDL_FreeSurface(tmp_surface);
}


// ----------------------------------------------------------------------------
// GetTextSize - retourne les tailles de la chaine
// ----------------------------------------------------------------------------
/*SDL_Rect GetTextSize(TCanvas* canvas,char* message)*/
SDL_Rect GetTextSize(TFont* font,char* message)
{
	SDL_Rect rect;
	int w,h;
	
	TTF_SizeText(font->getTTF_Font(),message,&w,&h);
	rect.x = rect.y = 0;
	rect.w = w;
	rect.h = h;
	return rect;
}


// ----------------------------------------------------------------------------
// DrawText - Affiche un texte
// ----------------------------------------------------------------------------
void DrawText(TCanvas* canvas,int x,int y,char* message)
{
	SDL_Surface *tmp_text = NULL;
	SDL_Rect dstrect;
	
	tmp_text = TTF_RenderText_Solid(canvas->Font->getTTF_Font(), message,  canvas->Font->Color);	
	SDL_SetAlpha(tmp_text,SDL_SRCALPHA,canvas->Font->Alpha);

	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = tmp_text->w;
	dstrect.h = tmp_text->h;

	SDL_BlitSurface(tmp_text, NULL, canvas->getSurface(), &dstrect);
	SDL_FreeSurface(tmp_text);
}



// ----------------------------------------------------------------------------
// DrawTextEx - Affiche un texte avec des fonctions étendues
// ----------------------------------------------------------------------------
void DrawTextEx(TCanvas* canvas,SDL_Rect rect,int align,char* message)
{
	int x = 0;
	int y = 0;
	SDL_Rect tmp_rect;
	
	// Alignement horizontal
	if ((align & ALIGN_LEFT) == ALIGN_LEFT) {
		x =rect.x;
	} else if ((align & ALIGN_RIGHT) == ALIGN_RIGHT) {
		tmp_rect = GetTextSize(canvas->Font,message);
		x =  rect.w - tmp_rect.w;
	} else if ((align & ALIGN_CENTER) == ALIGN_CENTER) {
		tmp_rect = GetTextSize(canvas->Font,message);
		x =  rect.x+(rect.w - rect.x - tmp_rect.w)/2;
	}
	
	// Alignement vertical
	if ((align & ALIGN_TOP) == ALIGN_TOP) {
		y= rect.y;
	} else if ((align & ALIGN_BOTTOM) == ALIGN_BOTTOM) {
		tmp_rect = GetTextSize(canvas->Font,message);
		y= rect.h - tmp_rect.h;
	} else if ((align & ALIGN_MIDDLE) == ALIGN_MIDDLE) {
		tmp_rect = GetTextSize(canvas->Font,message);
		y =  rect.y+(rect.h - rect.y - tmp_rect.h)/2;
	}
	
	DrawText	(canvas,x,y,message);
}

