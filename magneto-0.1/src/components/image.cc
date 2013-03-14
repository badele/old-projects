/*
  Auteur : Bruno Adele
  Date : 15/11/2002
  Desc : Classe qui permet d'avoir une liste d'image
*/


#include "image.h"

TImage::TImage(string filename)
{
	FSurface=NULL;
	FSurface=IMG_Load(filename.c_str());
	if (!FSurface) {
		cout << "Erreur de chargement images" ;
	}	

}

TImage::~TImage()
{
	SDL_FreeSurface(FSurface);
}

SDL_Surface* TImage::getSurface()
{
	return FSurface;
}


// ############################################################################
// ## TImages
// ############################################################################


TImages::TImages()
: TMap()
{
	
}

TImages::~TImages()
{
	
}


void* TImages::NewObject (string key)
{
	return new TImage(key);
}

void TImages::DeleteObject(string key)
{
	delete (TImage*)GetObject(key);
}
