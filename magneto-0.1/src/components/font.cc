/*
  Auteur : Bruno Adele
  Date : 15/11/2002
  Desc : Classe qui permet Encaspuler les TTF_Font
*/


#include "canvas.h"
#include <vector>

TFont::TFont(string fontname,int ptsize)
{
	// Chargement de la fonte
	cout << "Chargement fonte ... " ;
	FFont = NULL;
	FFont = TTF_OpenFont(fontname.c_str(), ptsize);
  	if(!FFont){
		fprintf(stderr,"Impossible de charger la fontes %s", SDL_GetError());
		exit(1);
  	}
	
	// Initialisation des variables
	Style = TTF_STYLE_NORMAL;
	Color.r = 255;
	Color.g = 255;
	Color.b = 255;
	Alpha = 100;
	
	TTF_SetFontStyle(FFont, Style);
}

TFont::~TFont()
{
	TTF_CloseFont(FFont);
}

TTF_Font* TFont::getTTF_Font()
{
		return FFont;
}


// ############################################################################
// ## TFonts
// ############################################################################

TFonts::TFonts() 
: TMap()
{
	//TMap::TMap();
	// Initalisation de SDL_ttf
	cout << "Initialisation de la bibliothèque SDL_ttf ... " ;
	if ( TTF_Init() < 0 ) {
			cout << "[TFonts::TFonts - Erreur" << endl << SDL_GetError();
			exit(1);
	}
}


TFonts::~TFonts()
{
	TTF_Quit();
}

// fontlocation;ptsize
void* TFonts::NewObject (string key)
{
	vector<string> list;
	Tokenize(key,list);
	return new TFont(list[0],FromString(list[1]));
}

void TFonts::DeleteObject(string key)
{
	delete (TFont*)GetObject(key);
}
/*void TFonts::Clear()
{
	map_string_void::iterator firstitem; 
	while (FFonts.size()>0) {
		firstitem = FFonts.begin();
		delete (TFont*)firstitem->second;
	}
	FFonts.clear();
}*/


/*TFont* TFonts::GetFont(string fontname, int ptsize)
{
	// convertir un int en string
	std::ostringstream ostr;
	ostr << ptsize;
	string sptsize(ostr.str());
	
	
	map_string_void::iterator found = FFonts.find(fontname+"-"+sptsize);
    if (found != FFonts.end()) {
			return (TFont*)found->second;
	} else {
		return NULL;
	}
}


TFont* TFonts::LoadFont(string fontname,int ptsize)
{
	TFont* font = GetFont(fontname,ptsize);

	// convertir un int en string
	std::ostringstream ostr;
	ostr << ptsize;
	string sptsize(ostr.str());

	if (font) {
		return font;
	} else {
		font = new TFont(fontname,ptsize);
		FFonts.insert((map_string_void::value_type(fontname+sptsize, font)));	
		return font;
	}
}

void TFonts::DeleteFont(string fontname,int ptsize)
{
	// convertir un int en string
	std::ostringstream ostr;
	ostr << ptsize;
	string sptsize(ostr.str());
	
	FFonts.erase(fontname+sptsize);
	
}*/
