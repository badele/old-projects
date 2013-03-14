/* **************************************************************************
                          kresolvename.cpp  -  description
                             -------------------
    begin                : Sun Jan 7 2001
    copyright            : (C) 2001 by Bruno Adele
    email                : b_adele@netcourrier.com
 ************************************************************************** */

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
// include pour le reseaux
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <kapp.h>
#include "kresolvename.h"


KResolveName::KResolveName(KDHostItem* AItem) : QObject()
{
	Item 	= AItem;
}

KResolveName::~KResolveName()
{
}

void KResolveName::run()
{
	unsigned long ipaddr;
	struct hostent * host;


	Item->setText(2,"Résolution de : "+Item->text(1));
	kapp->processEvents();

	ipaddr = inet_addr(Item->text(1));
	host = gethostbyaddr((char*)&ipaddr,sizeof(long),AF_INET);
	if (host) {
		Item->setText(2,host->h_name);
	} else {
		Item->setText(2,"");
	}

	delete this;
}

KDPing::KDPing(KDHostItem* AItem) : KProcess()
{
	Item 	= AItem;
	*this << "/bin/ping";
	*this << "-c1";
	*this << Item->text(1);
	connect (this,SIGNAL(receivedStdout (KProcess*,char*,int)),SLOT(slotStdout (KProcess*,char*,int)));
}

KDPing::~KDPing()
{

}

void KDPing::slotStdout(KProcess* AProcess,char* ABuffer,int ALength)
{
	QString string;
	string = QString(ABuffer);
	string.truncate(ALength);
	int start,end;

	// si on recois rien
	if (string.find("0 packets received")>-1) {
		Item->setText(0,"Down");	
	}	// si on à recu des pings
	else if (string.find("min/avg/max")>-1) {
		// trouve / donc corespond au contenu du avg
		start = string.find("min/avg/max");
		start+= QString("min/avg/max").length();
		start = string.find("/",start+1);
		end 	= string.find("/",start+1);
		Item->setText(0,string.mid(start+1,end-start-1)+" ms");
	}
}


/*KDSearchPort::KDSearchPort(QListViewItem* AItem) : KProcess()
{
	Item 	= AItem;
	*this << "/bin/ping";  // nmap -m - pour parser
	*this << "-c1";
	*this << Item->text(1);
	connect (this,SIGNAL(receivedStdout (KProcess*,char*,int)),SLOT(slotStdout (KProcess*,char*,int)));
}

KDSearchPort::~KDSearchPort()
{

}

void KDSearchPort::slotStdout(KProcess* AProcess,char* ABuffer,int ALength)
{
	QString string;
	string = QString(ABuffer);
	string.truncate(ALength);
	int start,end;

	// on recois rien
	if (string.find("0 packets received")>-1) {
		Item->setText(0,"Down");	
	}	// on à recu des pings
	else if (string.find("min/avg/max")>-1) {
		// trouve / donc corespond au contenu du avg
		start = string.find("min/avg/max");
		start+= QString("min/avg/max").length();
		start = string.find("/",start+1);
		end 	= string.find("/",start+1);
		Item->setText(0,string.mid(start+1,end-start-1)+" ms");
	}
} */

