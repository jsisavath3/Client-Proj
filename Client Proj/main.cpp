#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void recvThread(SOCKET sock, char buff[4096]) {
	int bytesReceived;
	while (1) {
		bytesReceived = recv(sock, buff, 4096, 0);
		if (bytesReceived > 0) {
			cout << string(buff, 0, bytesReceived);
		}
	}
}

int main() {
	string ipAddress = "73.6.97.169";
	int port = 38000;

	//initialize
	WSADATA wsaData;
	WORD ver = MAKEWORD(2, 2);
	WSAStartup(ver, &wsaData);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in hints;
	hints.sin_family = AF_INET;
	hints.sin_port = htons(38000);
	inet_pton(AF_INET, ipAddress.c_str(), &hints.sin_addr);

	int connection = connect(sock, (sockaddr*)& hints, sizeof(hints));
	if (connection == SOCKET_ERROR) {
		closesocket(sock);
		sock = INVALID_SOCKET;
	}
	if (sock == INVALID_SOCKET) {
		cout << "Failed to connect!";
		WSACleanup();
		return 1;
	}
	char buff[4096];
	string input;
	bool running = true;

	thread r1(recvThread, sock, buff);

	while (running) {
		getline(cin, input);
		if (input.size() > 0) {
			int sendresult = send(sock, input.c_str(), input.size() + 1, 0);
		}
	}
	return 0;
}