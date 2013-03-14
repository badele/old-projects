/*
  Auteur : Bruno Adele
  Date : 15/11/2002
  Desc : Classe qui contient des conteneurs
*/

#include "data.h"

// ############################################################################
// ## amélioration du std::string
// ############################################################################


template < class T> inline string ToString(const T &value)
{
	std::stringstream streamout;
	streamout << value;
	return streamout.str();
}

// fonction permetant de convertir d'un string vers string
template <> inline string ToString(const string &value)
{
	return value;
}

// fonction permetant de convertir d'un string vers un type
/* etant donnée que je n'arrive pas compilé ceci, je vais pour
   l'instant faire une méthode par type de donnée
template < class T> inline T FromString( const string value)
{
	std::stringstream streamin(value);
	T returnvalue = T();
	streamin >> returnvalue;
	return returnvalue;
}*/

int FromString( const string value)
{
	std::stringstream streamin(value);
	int returnvalue;
	streamin >> returnvalue;
	return returnvalue;
}


// C++ Programming Howto
void Tokenize(const string& str,vector<string>& tokens, const string& delimiters = ";")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

// ############################################################################
// ## TMap
// ############################################################################


TMap::TMap()
{
}


TMap::~TMap()
{
	Clear();
}



void TMap::Delete(string key)
{
	DeleteObject(key);
	FMap.erase(key);
}


void TMap::Clear()
{
	map_string_void::iterator firstitem; 
	while (FMap.size()>0) {
		firstitem = FMap.begin();
		DeleteObject(firstitem->first);
	}
	FMap.clear();
}



void* TMap::GetObject(string key)
{
	map_string_void::iterator found = FMap.find(key);
    if (found != FMap.end()) {
			return found->second;
	} else {
		return NULL;
	}
}

// créer une nouvelle instance d'un objet
void* TMap::NewObject(string key)
{
	// abstrait: creer une nouvelle instance
	// return new object
	return NULL;
}

void TMap::DeleteObject(string key)
{
	// abstrait: libere l'instance
	//delete object;
	return;
}

void* TMap::LoadObject(string key)
{
	void* object = GetObject(key);

	if (object) {
		return object;
	} else {
		object = NewObject(key);
		FMap.insert((map_string_void::value_type(key, object)));	
		return object;
	}
}

// ############################################################################
// ## TList
// ############################################################################


TList::TList()
{
}


TList::~TList()
{
}

void TList::Add(void* pointer)
{
	FList.push_back(pointer);
}

void* TList::Get(unsigned index)
{
	list<void*>::iterator it = FList.begin();


	// cherche l'element par rapport à l'index
	if (index<FList.size()) {
			unsigned i=0;
			// on boucle jusqu'a l'element
			while (i<index) {
				it++;
				i++;
			}
			return  *it;
		} else { // n'existe pas
				return NULL;
		}
}

int TList::getSize()
{
	return FList.size();
}



