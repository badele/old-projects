/*
  Auteur : Bruno Adele
  Date : 17/11/2002
  Desc : Classe qui permet d'avoir une liste d'image
*/

#ifndef __TImage_H__
#define __TImage_H__

/*#include <map>
#include <string>
#include <sstream>*/
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "data.h"



/*class TImages : public TMap{
public:
	TImages
	
};*/

class TImage
{
private :
	SDL_Surface* FSurface;
	
public :
	
	TImage(string filename);
	~TImage();
	SDL_Surface* getSurface();
};



class TImages : public TMap {

public:
	TImages();
	~TImages();
	void* 	NewObject(string key);
	void 	DeleteObject(string key);
	
};



#endif
