/*
  Auteur : Bruno Adele
  Date : 10/11/2002
  Desc : Classe principalle
*/


#include <iostream.h>
#include <stdlib.h>

#include <SDL/SDL.h>

#include "osd.h"
#include "ecran.h"

int main()
{

	int ret ;

	cout << endl << "Lancement du lecteur à " << __DATE__ << " )" << endl << endl;
	

	cout << "Chargement du projet" << endl ;

	// Initalisation de SDL
	cout << "Initialisation de la bibliothèque SDL ... " ;
	if ( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0 )
		{
			cout << "[Erreur]" << endl << SDL_GetError();
			exit(1);
		}
	cout << "[OK]" << endl ;
		
		
	/* on cree la surface de l'ecran */
	SDL_Surface *screen ;

	cout << "Initialisation du mode graphique ... " ;
	screen = SDL_SetVideoMode(800, 600, 16, SDL_HWSURFACE); // | SDL_DOUBLEBUF  | SDL_FULLSCREEN
	if (screen == NULL )
		{
			cout << "[FAILED]" << endl << SDL_GetError();
			exit(1);
		}
	else
		cout << "[OK]" << endl ;

	/*****************************************************************************************************/

	TEcran *ecrans[5];
	TEcran * ecranselected;
	SDLKey key;
	
	/* On crée l'objet qui represente un téléviseur */
	TOsd *Osd = new TOsd( screen ) ;
	ecrans[0] = new TEcran(Osd);
	ecranselected = ecrans[0];


	
	/* on initialise quelques parametres */
	Osd->Init() ;

//	Osd->Draw();
//	Osd->Update();
	
	SDL_Event event;
	//SDL_WaitEvent(&event);

    Uint32 next_time = 0;
    Uint32 now;
	

	while (1) {
		#define TICK_INTERVAL    3
		now = SDL_GetTicks();
		if ( next_time <= now ) {
			next_time = now+TICK_INTERVAL;
			ecranselected->Idle();
			Osd->Elapsed();
			Osd->DrawBackground();
			ecranselected->Draw();
			Osd->DrawForeground();
			//Osd->Update();
			Osd->Canvas->Update();
		}

		while (SDL_PollEvent(&event)>0) {
			switch (event.type) {
				case SDL_KEYDOWN:
					key = event.key.keysym.sym;
					ecranselected->OnKeyDown(key);
					break;
				case SDL_KEYUP:
					key = event.key.keysym.sym;
					ecranselected->OnKeyUp(key);
					break;
				case SDL_QUIT:
					exit(0);
					break;
			}		
		}	
}
		
	
		





	/* ... puis on le lance */
	//ret = Osd->launch() ;

	if ( ret != 0 )
		{
			cerr << "** ERROR **" << endl ;
			return 1 ;
		}

	cout << "Good bye ! " << endl ;
	SDL_Quit() ;
	return 0 ;
}
