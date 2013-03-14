/*
  Auteur : Bruno Adele
  Date : 16/11/2002
  Desc : Déclaration de la classe Ecran
*/


#include <time.h>
#include <iostream.h>
#include <SDL/SDL.h>
#include "ecran.h"

TEcran :: TEcran( TOsd* Osd )
{
	this->Osd = Osd ;

	MenuPrincipal = new TMenu(Osd->Canvas);
	MenuPrincipal->setFont((TFont*)Osd->Canvas->Fonts->LoadObject("../skins/fonts/vixar.ttf;76"));
	MenuPrincipal->getRect()->x=300;
	MenuPrincipal->getRect()->y=90;
	MenuPrincipal->getRect()->h=545;
	MenuPrincipal->getRect()->w=725;
	MenuPrincipal->Marge=8;
	MenuPrincipal->getFont()->Alpha=255;
	// ajout des menus
	MenuPrincipal->Add("Musique",(TImage*)Osd->Canvas->Images->LoadObject("../skins/images/test_musique.png"));
	MenuPrincipal->Add("Television",(TImage*)Osd->Canvas->Images->LoadObject("../skins/images/test_tv.png"));
	MenuPrincipal->Add("Film",(TImage*)Osd->Canvas->Images->LoadObject("../skins/images/test_film.png"));
	MenuPrincipal->Add("Photos",(TImage*)Osd->Canvas->Images->LoadObject("../skins/images/test_d30.png"));
	MenuPrincipal->Add("Jeux",(TImage*)Osd->Canvas->Images->LoadObject("../skins/images/test_pad.png"));
	MenuPrincipal->Add("Configuration",(TImage*)Osd->Canvas->Images->LoadObject("../skins/images/test_config.png"));
	MenuPrincipal->Add("Quitter",(TImage*)Osd->Canvas->Images->LoadObject("../skins/images/shutdown.png"));
	
	
}


int TEcran :: Init()
{

	return 1 ;
}

void TEcran::OnKeyDown(SDLKey key)
{
	switch (key) {
		case SDLK_DOWN:
			MenuPrincipal->Next();
			break;
		case SDLK_UP:
			MenuPrincipal->Prev();
			break;
		case SDLK_ESCAPE:
			exit(0);	
			break;
		default:
			break;
	}

}

void TEcran::OnKeyUp(SDLKey key)
{
}


void TEcran::Idle()
{
		Draw();
}




void TEcran::Update()
{
}

void TEcran::Draw()
{
	MenuPrincipal->Draw();
}




