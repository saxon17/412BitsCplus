#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <string>
#include <cstring>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
#define MAXMESGLEN 1024
#define LISTENQUEUE 1
#define SERVERPORT 7777
#define CLIENTPORT 8888
#define RCVBUFSIZE 4096

// For connecting to another host and sending char data
class DataSender {
	
	private:
	// for socket file descriptor
	unsigned short mySocket, serverPort;
	string serverIP;
	void* ReplyListener(void* arg);
	
	public:
	
	char replyBuffer[RCVBUFSIZE];
	
	// Class constructor
	DataSender(string serverIP = "", unsigned short serverPort = 0);
	
	
	// Getters & Setters for IP and port
	string getServer();
	unsigned short getPort();
	void setServer(string serverIP);
	void setPort(unsigned int serverPort);
	
	
	/* Desc: Used to establish remote TCP connection
	 * Input: serverIP expects IPv4 address as string, ex: "192.168.1.1"
	 * Output: returns result of success, fail < 0, success >= 0
	*/
	short createConn();
	
	
	/* Desc: Disconnect TCP connection and reset mySocket
	 * Output: returns result of success, fail < 0, success >= 0
	 */
	short disconnect();
	
	
	/* Desc: Transmits string message less than 1024 bytes to
	 * 		current socket connection
	 * Input: Expects string of less than 1024 bytes
	 * Output: returns result of success, fail < 0, success >= 0
	*/
	short transmit(string message = "");
};

// For listening and receiving data
class DataReceiver {
	
	private:
	// for socket file descriptor
	unsigned short clientSocket, listenSocket;
	unsigned long myIP;
	
	public:
	char msgBuffer[RCVBUFSIZE];
	DataReceiver();
	void listener(int portNum);
	void HandleTCPClient();
	short transmit(string message = "");
	short disconnect( unsigned short *socketName );
};

#endif
