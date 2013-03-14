/*
  Auteur : Bruno Adele
  Date : 16/11/2002
  Desc : Déclaration de la classe Menu
*/


#include <time.h>
#include <iostream.h>
#include <SDL/SDL.h>
#include "menu.h"


TMenuItem::TMenuItem(string caption,TImage* image,void* data) 
{
	this->Caption = caption;
	this->Image = image;
	this->Data = data;
}

TMenu::TMenu( TCanvas* canvas )
{
	FList = new TList();
	
	FCanvas = canvas ;
	FItemIndex = 0;
	FTopIndex=0;
	Marge = 10;
	FMaxImageWidth = 0;
	FMaxImageHeight = 0;
	Color = SDL_MapRGB(FCanvas->getSurface()->format,0,0,75);
	BackgroundColor = SDL_MapRGB(FCanvas->getSurface()->format,255,255,255);
	ShowBackground = true;
	FRect.x = 0;
	FRect.y = 0;
	FRect.h=canvas->getRect()->h;
	FRect.w=canvas->getRect()->w;
	// calcule la hauteur des images
	FArrowHeight = ((TImage*)FCanvas->Images->LoadObject("../skins/images/fleche_haut.png"))->getSurface()->h;
	if (((TImage*)FCanvas->Images->LoadObject("../skins/images/fleche_bas.png"))->getSurface()->h>FArrowHeight) {
		FArrowHeight = ((TImage*)FCanvas->Images->LoadObject("../skins/images/fleche_bas.png"))->getSurface()->h;
	}

}

void TMenu::Add(TMenuItem* menuitem)
{
	if (menuitem->Image!=NULL) {
		if (FMaxImageWidth<menuitem->Image->getSurface()->w) {
			FMaxImageWidth = menuitem->Image->getSurface()->w;
		}
		if (FMaxImageHeight<menuitem->Image->getSurface()->h) {
			FMaxImageHeight = menuitem->Image->getSurface()->h;
		}
	}
	FList->Add((void*) menuitem);
}

void TMenu::Add(string caption,TImage* image /* NULL */,void* data /* NULL */)
{
	TMenuItem* menuitem = new TMenuItem(caption,image,data);
	this->Add(menuitem);
}


void TMenu::Next()
{
	if (FItemIndex<FList->getSize()-1) {
		FItemIndex++;
		if (FItemIndex>getMaxiShow()-1) {
				FTopIndex++;
		}
	}	
}


void TMenu::Prev()
{
	if (FItemIndex>0) {
		FItemIndex--;
		if (FItemIndex<FTopIndex) {
				FTopIndex--;
		}
	}	
}

void TMenu::Draw()
{
	
	// Desine le fond
	if (ShowBackground) {
		FCanvas->Alpha = 50;
		FCanvas->Color = BackgroundColor;
		DrawRect(FCanvas,FRect);	
	}	

	
	FCanvas->Color = Color;
	FCanvas->Alpha = 100;
	DrawRect(FCanvas,GetRectSelected(FItemIndex));	
	// Déssine le titre
	FCanvas->Font = FFont;
	FCanvas->Alpha = 255;
	int positem;
	for (int i=FTopIndex;i<FTopIndex+getMaxiShow() && i<FList->getSize() ;i++) {
		TMenuItem* menuitem = (TMenuItem*)FList->Get(i);
		positem = i-FTopIndex;
		if (menuitem->Image) {
			DrawImageEx(FCanvas,GetRectIcon(i),menuitem->Image,ALIGN_CENTER | ALIGN_MIDDLE);
		}
		DrawTextEx(FCanvas,GetRectText(i),ALIGN_LEFT | ALIGN_MIDDLE ,(char*)menuitem->Caption.c_str());
	}	
	
	// affiche la fleche du bas
	TImage* img_arrow;
	if (getMaxiShow()<FList->getSize()-1 && (FTopIndex+getMaxiShow())<FList->getSize()) {
		img_arrow = (TImage*)FCanvas->Images->LoadObject("../skins/images/fleche_bas.png");
		DrawImageEx(FCanvas,GetRectArrowBottom(),img_arrow,ALIGN_CENTER | ALIGN_MIDDLE);
	}
	
	// affiche la fleche du haut
	if (FTopIndex>0) {
		img_arrow = (TImage*)FCanvas->Images->LoadObject("../skins/images/fleche_haut.png");
		DrawImageEx(FCanvas,GetRectArrowUp(),img_arrow,ALIGN_CENTER | ALIGN_MIDDLE);
	}
	
}

SDL_Rect TMenu::GetRectSelected(int AItemIndex)
{
	SDL_Rect tmp_rect;
	tmp_rect.x = FRect.x;
	tmp_rect.y = FRect.y+Marge+FArrowHeight+Marge+((FFontHeight+Marge)*(AItemIndex-FTopIndex));
	tmp_rect.w = FRect.w;
	tmp_rect.h = tmp_rect.y+FFontHeight+Marge;
	return tmp_rect;
}

SDL_Rect TMenu::GetRectText(int AItemIndex)
{
	SDL_Rect tmp_rect;
	tmp_rect.x = FRect.x+Marge+FMaxImageWidth+Marge;
	tmp_rect.y = FRect.y+Marge+FArrowHeight+Marge+((FFontHeight+Marge)*(AItemIndex-FTopIndex));
	tmp_rect.w = FRect.w;
	tmp_rect.h = tmp_rect.y+FFontHeight+Marge;
	return tmp_rect;
}


SDL_Rect TMenu::GetRectIcon(int AItemIndex)
{
	SDL_Rect tmp_rect;
	tmp_rect.x = FRect.x+Marge;
	tmp_rect.y = FRect.y+Marge+FArrowHeight+Marge+((FFontHeight+Marge)*(AItemIndex-FTopIndex));
	tmp_rect.w = tmp_rect.x+FMaxImageWidth;
	tmp_rect.h = tmp_rect.y+FFontHeight+Marge;
	return tmp_rect;
}



SDL_Rect TMenu::GetRectArrowUp()
{
	SDL_Rect tmp_rect;
	tmp_rect.x = FRect.x;
	tmp_rect.y = FRect.y+Marge;
	tmp_rect.w = FRect.w;
	tmp_rect.h = tmp_rect.y+FArrowHeight+Marge;
	return tmp_rect;
}

SDL_Rect TMenu::GetRectArrowBottom()
{
	SDL_Rect tmp_rect;
	tmp_rect.x = FRect.x;
	tmp_rect.y = FRect.h-Marge-FArrowHeight-Marge;
	tmp_rect.w = FRect.w;
	tmp_rect.h = FRect.h;
	return tmp_rect;
}


void TMenu::setFont(TFont* font)
{
	SDL_Rect tmp_rect;

	FFont = font;
	tmp_rect = GetTextSize(font,"hauteur");
	FFontHeight = tmp_rect.h;
}

TFont* TMenu::getFont()
{
	return FFont;
}

SDL_Rect* TMenu::getRect()
{
	return &FRect;
}

int TMenu::getMaxiShow()
{
	int height,maxi;
	height = FRect.h-(2*FArrowHeight)-(4*Marge)-FRect.y;
	maxi = height/(FFontHeight+Marge);

	return maxi;
}




