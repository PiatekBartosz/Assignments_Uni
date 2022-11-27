#include "Client.h"
#include "Server.h"
#include <iostream>

int main() {
	Server server(1234);
	server.Start();

	std::string tmp;
	Client client;
	
	/*getline(std::cin, tmp);
	client.Text(tmp, "127.0.0.1", 1234);*/

	/*if(client.RecvFile("C:\\Users\\Bartek\\Desktop\\Figure_1.jpeg", "test1.jpg",
		"127.0.0.1", 1234)){
		std::cout << "y\n";
	}
	else {
		std::cout << "n\n";
	}*/


	client.SendFile("C:\\Users\\Bartek\\Desktop\\Figure_1.jpeg", "server.jpg", "127.0.0.1", 1234);
}