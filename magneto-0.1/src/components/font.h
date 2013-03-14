/*
  Auteur : Bruno Adele
  Date : 15/11/2002
  Desc : Classe qui permet Encaspuler les TTF_Font
*/

#ifndef __TFont_H__
#define __TFont_H__

#include <map>
#include <string>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "data.h"

using namespace std;
typedef map<string, void *> map_string_void;


class TFont
{
private :
	TTF_Font *FFont;
	
public :
	SDL_Color Color;
	int Style;
	int Alpha;
	int Align;
	
	TFont(string fontname,int ptsize);
	~TFont();
	TTF_Font* getTTF_Font();
};


/*class TFonts {

	
private: 
	map_string_void FFonts;
	TFont* 	GetFont(string fontname, int ptsize);
	
public:
	TFonts();
	~TFonts();
    TFont* 	LoadFont(string fontname,int ptsize);
	void 	Clear();
	void 	DeleteFont(string fontname,int ptsize);
};*/

class TFonts : public TMap {

public:
	TFonts();
	~TFonts();
	void* 	NewObject(string key);
	void 	DeleteObject(string key);
	
};





#endif
