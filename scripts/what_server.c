/*
 * Script modifier par Bruno Adele < b_adele@netcourrier.com >
 * Voici un exemple d'un script qui peut etre executé à partir de KDoors ( C ou C++ )
 *
 *
 *serVer release 1.0 (18/Mar/2000)
 * Copyright (C) 2000 Paulo Ribeiro
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * HOW TO...
 * a) compile:			gcc -Wall serVer.c -o serVer
 * b) get ftpd version:		./serVer <host or ip> 21
 * c) get httpd version:	./serVer <host or ip> 80
 */

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX	65535

int s;

struct sockaddr_in sock;
struct hostent *he;

int quit(int);

int main(int argc, char **argv)
{
        char *ver;
	char buf[MAX];
	char message[] = "HEAD / HTTP/1.0\n\n";

	int c, x, numbytes;

        if(argc == 2) {
    	    if (strstr(argv[1],"getinfo") != NULL) {
        	    printf ( "<Plugins\n" );
		    printf ( "  Author = \"Bruno Adele\"\n" );
		    printf ( "  Email = \"b_adele@netcourrier.com\"\n" );
		    printf ( "  Title = \"What Server Running\"\n" );
	    	    printf ( "  Version = \"1.0\"\n" );
		    printf ( "  Type = \"Dianostic\"\n" );
		    printf ( "  Info = \"Indique sur quel serveur tourne le serveur web ou le serveur ftp\"\n" );
		    printf ( "  Web = \"http://www.jesuislibre.org\"\n" );
		    printf ( "  Options = \"Web_Server_Port= 80\"\n" );
		    printf ( "  Solution = \"\"\n" );
		    printf ( "/>\n" );
		    exit(0);
	    } else {	    
		    exit(-1);
	    }
	}
 
        if(atoi(argv[2]) == 80)
                sock.sin_port = htons(80);
        else if(atoi(argv[2]) == 21)
                sock.sin_port = htons(21);

//        printf("Resolving address/IP number...\t");
        if((he=gethostbyname(argv[1])) == NULL)
		quit(0);

//        printf(" done.\nOpenning socket...\t\t");
        if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		quit(0);

//        printf(" done.\n");
        sock.sin_family = AF_INET;

        sock.sin_addr =  *((struct in_addr *)he->h_addr);
	bzero(&(sock.sin_zero), 8);

//	printf("Connecting to server...\t\t");
        if(connect(s, (struct sockaddr *)&sock, sizeof(struct sockaddr)) == -1)
		quit(-1);

	printf("<Plugins \n Resultat = \"");
 	if(atoi(argv[2]) == 80)
	{
 //	       printf(" done.\nRequesting informations...\t");
 		if((send(s, message, strlen(message), 0)) == -1)
               	 quit(-1);

//	        printf(" done.\nReceiving informations...\t");
       		if((numbytes=recv(s, buf, MAX, 0)) == -1)
			quit(-1);

//        	printf(" done.\nSearching for version number...\t");
       		buf[numbytes] = '\0';
        	if((ver = strstr(buf, "Server:")) == NULL)
        	{
                	printf(" failed.\nTrying again...\t\t\t");
                	if((ver = strstr(buf, "server:")) == NULL)
				quit(-1);
        	}
//        	printf(" done.\n\n");

		for(x = 0, c = ver[x]; c != '\n'; x++, c = ver[x])
        	    if (c != '\r')
			printf("%c", c);
	}
	else
	{
//        	printf(" done.\nReceiving informations...\t");
        	if((numbytes=recv(s, buf, MAX, 0)) == -1)
			quit(-1);

        	buf[numbytes] = '\0';

		for(x = 3, c = buf[x]; c != '\n'; x++, c = buf[x])
		{
			if(x == 3 && c == '-');
			else if(x == 3 && c == ' ');
			else if(x == 4 && c == ' ');
			else if(c == 'R' && buf[x+1] == 'e' && buf[x+2] == 'a'
			&& buf[x+3] == 'd' && buf[x+4] == 'y')
				break;
			else if(c == 'r' && buf[x+1] == 'e' && buf[x+2] == 'a'
        	        && buf[x+3] == 'd' && buf[x+4] == 'y')
				break;
			else    
				printf("%c", c);
		}
	}

	printf("\"\n/>\n");
	shutdown(s, 2);

	exit(0);
}

int quit(int num)
{
	printf(" failed.\n\n");
	if(num == -1)
		shutdown(s, 2);

	exit(-1);
}

