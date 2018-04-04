//
// Server.cpp
//
// Extremely simple, stream server example.
// Works in conjunction with Client.cpp.
//
// The program sets itself up as a server using the TCP
// protoocl. It waits for data from a client, displays
// the incoming data, sends a message back to the client
// and then exits.
//
// Compile and link with wsock32.lib
//
// Pass the port number that the server should bind() to
// on the command line. Any port number not already in use
// can be specified.
//
// Example: Server 2000
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
