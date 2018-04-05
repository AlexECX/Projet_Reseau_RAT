//
// Connection.h
// Connection.cpp
//
// Object that initiates a single connection between a client 
// its target server, or vice versa. If a Name or IP address is given,
// will initiate as a client, else will be a server. A port number
// is needed for one or the other.
//
// The object comes with functions to send/receive messages or
// files.
//
// Compile and link with wsock32.lib.
//
//
// Written by: Alexandre Cox
// Date: 04/04/2018
//
#pragma once
#include <winsock.h>
#include <iostream>
#include <fstream>
#include <string>

class Connection
{
private:
	SOCKET      theSocket;
	SOCKET      listenSocket;
	SOCKADDR_IN saServer;

public:
	//mode listen()
	Connection(short cPort);

	//mode connect() 
	Connection(short cPort, char *szServer);

	~Connection();

	/*Déprécier, utiliser WaitRequest()*/
	int runAsServer();

	//Utiliser lorsqu'en mode serveur pour recevoir
	//une requete de connection.
	int WaitRequest();

	//Fonctions pouvant envoyer et recevoir des fichiers
	//de grande taille. Envoie/reçois le fichier en plusieurs 
	//lectures disque, sans charger la totalité du fichier en mémoire.
	int sendFile(std::string FilePath);

	int recvFile(std::string FilePath);

	//Permet d'envoyer le nom du fichier � envoy�.
	/*Déprécié, utiliser sendMessage()*/
	bool sendFileRequest(std::string file_name);

	//Permet de recevoir le nom du fichier � envoy�.
	/*Déprécié, utiliser recvMessage()*/
	bool recvFileRequest(char* &buffer, unsigned int &buffer_size);

	//permet d'envoyer un message ou un fichier. Si trop grand,
	//l'envoie en plusieurs paquets.
	bool sendMessage(std::string file);

	//permet de recevoir un message ou un fichier. Si trop grand,
	//est pret a recevoir en plusieurs paquets.
	bool recvMessage(std::string &message, bool show_progress=false);


};

