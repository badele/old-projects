/*
  Auteur : Bruno Adele
  Date : 16/11/2002
  Desc : Déclaration de la classe Ecran
*/

#ifndef __TEcran_H__
#define __TEcran_H__

#include <SDL/SDL.h>

#include "osd.h"
#include "graphics.h"
#include "menu.h"
class TEcran
{
	private :

	TOsd * Osd;
	TMenu* MenuPrincipal;



	public :

	TEcran(TOsd * Osd) ;


	/* Initialise quelques parametres du jeu */
	int Init() ;


	/* dessine un pixel */

	void Update();

	void Idle();
	void Draw();
	
	void OnKeyDown(SDLKey key);
	void OnKeyUp(SDLKey key);	
	
	

} ;

#endif
