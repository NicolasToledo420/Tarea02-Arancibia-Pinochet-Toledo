/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "YASL.h"      // For Socket, ServerSocket, and SocketException
#include "json.hpp"	//Libreria Json	
#include "<fstream> // Manejo de archivos
#include "checkArgs.h"
#include <iostream>    // For cerr and cout
#include <cstdlib>     // For atoi()

const uint32_t RCVBUFSIZE = 32;    // Size of receive buffer

// TCP client handling function
void HandleTCPClient(TCPSocket *sock) {
	std::cout << "Handling client ";
	try {
		std::cout << sock->getForeignAddress() << ":";
	} catch (SocketException e) {
		std::cerr << "Unable to get foreign address" << std::endl;
	}
	try {
		std::cout << sock->getForeignPort();
	} catch (SocketException e) {
		std::cerr << "Unable to get foreign port" << std::endl;
	}
	std::cout << std::endl;
//-------CODIGO ORIGINAL DEL STRING QUE ERA ENVIADO DEL SERVIDOR ECHO--------
	/*// Send received string and receive again until the end of transmission
	char echoBuffer[RCVBUFSIZE];
	uint32_t recvMsgSize;
	while ((recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE)) > 0) { // Zero means
	                                                 // end of transmission
		// Echo message back to client
		sock->send(echoBuffer, recvMsgSize);
		}*/
//----------------------------------------------------------------------------------------------------	
	
	
	sock->send("HTTP/1.1 200 OK\r\n", );//HTTP indicado en la especificacion de la tarea
	
	//------------Leer Archivo HTML----------------------
	std::string leerlinea;std::string structhtml="";std::ifstream data("1.html");//Tola aqui se coloca la pagina1 data(" ")
	//std::string leer: es una variable en la cual se usa para obtener una linea de un archivo
	//std::string structhtml: es la variable en la cual se guardara la estructura del html
	//std::string ifstream: es la variable que me permite abrir el archivo variable("pagina html");
	/*  En este espacio se deberia crear el code en el cual guardamos la estrucura html, debemos guardar el html linea por linea
	abriendolo con ifstream data("Ubicacion del html"), y al revisar linea por linea el codigo, tendremos la variable leerlinea en la cual
	guardaremos linea por linea en la variable structhtml
	*/
	
	delete sock;
}

int main(int argc, char *argv[]) {
	
	checkArgs* argumentos = new checkArgs(argc, argv);
	
	uint16_t echoServPort;   
	echoServPort  = argumentos->getArgs().PORT;

	try {
		TCPServerSocket servSock(echoServPort);     // Server Socket object

		for (;;) {   // Run forever
			HandleTCPClient(servSock.accept());       // Wait for a client to connect
		}
	} catch (SocketException &e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	// NOT REACHED

	return EXIT_SUCCESS;
}
