/*
  Auteur : Bruno Adele
  Date : 15/11/2002
  Desc : Classe qui permet Encaspuler les TTF_Font
*/

#ifndef __TData_H__
#define __TData_H__

#include <map>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

using namespace std;
typedef map<string, void *> map_string_void;

// ############################################################################
// ## amélioration du std::string
// ############################################################################


// fonction permetant de convertir d'un type vers string
template < class T> inline string ToString(const T &value);

// fonction permetant de convertir d'un string vers string
/* etant donnée que je n'arrive pas compilé ceci, je vais pour
   l'instant faire une méthode par type de donnée
template <> inline string ToString(const string &value);*/


// fonction permetant de convertir d'un string vers un type
/* etant donnée que je n'arrive pas compilé ceci, je vais pour
   l'instant faire une méthode par type de donnée
template < class T> inline T FromString( const string value);*/
int FromString(string);

// Convertir une chaine avec des delimiteur en vecteur
void Tokenize(const string& str,vector<string>& tokens, const string& delimiters = ";");

// ############################################################################
// ## Classe TMap
// ############################################################################


class TMap {

	
private: 
	map_string_void FMap;
	
protected:
	
public:
					TMap();
	virtual 		~TMap();
	void* 			LoadObject(string key);
	virtual void* 	NewObject(string key);
	virtual void 	DeleteObject(string key);	
	void* 			GetObject(string key);
	void 			Clear();
	void			Delete(string key);
	int				getSize();
	
};


class TList {

	
private: 
	list<void*> FList;
	
protected:
	
public:
					TList();
	virtual 		~TList();
	void			Add(void* pointer);
	void* 			Get(unsigned index);
	int				getSize();
};


#endif
