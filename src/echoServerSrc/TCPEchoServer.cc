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
#include <fstream> // Manejo de archivos
#include "checkArgs.h"
#include <iostream>    // For cerr and cout
#include <cstdlib>     // For atoi()
#include <string>

const uint32_t RCVBUFSIZE = 512;    // Size of receive buffer
// TCP client handling function
void HandleTCPClient(TCPSocket *sock) {	
	//SE OBTIENE LA IP Y EL HOST DEL CLIENTE
	try {
		std::cout << "El cliente con la IP: ";
		std::cout << sock->getForeignAddress() << ":";
	} catch (SocketException e) {
		std::cerr << "No se puede obtener la IP" << std::endl;
	}
	try {
		std::cout << sock->getForeignPort();
		std::cout << " esta manejando el servidor";
	} catch (SocketException e) {
		std::cerr << "No se puede obtener el puerto" << std::endl;
	}
	std::cout << std::endl;
	// Send received string and receive again until the end of transmission
	//SE DEFINE EL ECHOVBUFFER CON EL LARGO DEL RCVBUFSIZE
	char echoBuffer[RCVBUFSIZE];
	uint32_t recvMsgSize;
	recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE);
	std::cout << recvMsgSize + "\n";
	//SE ENVIA A TRAVÉS DEL SOCKET EL RESPONSE AL REQUEST INICIAL
	sock->send("HTTP/1.1 200 OK\r\n", 32);//HTTP indicado en la especificacion de la tarea
	sock->send("Content-Type: text/html\r\n\r\n", 32);
	//SE GENERAN LAS VARIABLES NECESARIAS PARA COMPRAR EL ECHOBUFFER CON EL NOMBRE DE LOS ARCHIVOS
	//ADEMAS SE GENERAN VARIABLES PARA PODER LEER LINEA POR LINEA EL ARCHIVO HTML
	std::string leerlinea;
	std::string htmlstruct="";
	std::string rqe(echoBuffer, 5, 6);
	std::string a1 = "1.html";
	std::string a2 = "2.html";
	std::string a3 = "3.html";
	std::ifstream arch("../www-data/1.html");//Tola aqui se coloca la pagina1 data(" ")
	std::ifstream arch1("../www-data/2.html");
	std::ifstream arch2("../www-data/3.html");
	std::ifstream arch404("../www-error/404.html");
	std::cout << rqe + "\n";
	//SI EL SUBSTRING rqe PROVENIENTE DEL ECHOBUFFER ES IGUAL AL NOMBRE DEL ARCHIVO 1
	//SE LEE LINEA POR LINEA EL HTML Y LO ENVIA A TRAVÉS DEL SOCKET
	//ESTA MISMA CONDICION SE REPLICA PARA EL ARCHIVO 2, 3 Y EL ARCHIVO 404
	//ESTE ULTIMO SOLO SE VA A EJECUTAR SI EL REQUES NO CORRESPONDE A NINGUN NUMBRE DE
	//NINGUN ARCHIVO.
	if(rqe == a1){
		if (arch.is_open()){
			while(getline(arch, leerlinea)){
				htmlstruct = htmlstruct + leerlinea + "\n";
			}
			arch.close();
			sock->send(htmlstruct.c_str(), htmlstruct.length());
		}
		else{
			std::cout << "No se ha podido abrir el HTML correspondiente";
		}
	}
	else if (rqe == a2){
		if (arch1.is_open()){
			while(getline(arch1, leerlinea)){
				htmlstruct = htmlstruct + leerlinea + "\n";
			}
			arch1.close();
			sock->send(htmlstruct.c_str(), htmlstruct.length());
		}
		else{
			std::cout << "No se ha podido abrir el HTML correspondiente";
		}
	}
	else if (rqe == a3){
		if (arch2.is_open()){
			while(getline(arch2, leerlinea)){
				htmlstruct = htmlstruct + leerlinea + "\n";
			}
			arch2.close();
			sock->send(htmlstruct.c_str(), htmlstruct.length());
		}
		else{
			std::cout << "No se ha podido abrir el html correspondiente";
		}
	}
	else{
		if(arch404.is_open()){
			while(getline(arch404, leerlinea)){
				htmlstruct = htmlstruct + leerlinea + "\n";
			}
			arch404.close();
			sock->send(htmlstruct.c_str(), htmlstruct.length());
		}
		
		else{
			std::cout << "No se ha podido abrir el html correspondiente";
		}
	}
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
