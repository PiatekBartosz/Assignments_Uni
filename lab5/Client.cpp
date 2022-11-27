#include "Client.h"
#include "asio.hpp"
#include "Frame.h"
#include "BinFile.h"
#include <iostream>

void Client::Echo(std::string text, const std::string ip, const unsigned short port)
{
	Frame sframe;
	sframe.type = Frame::Type::ECHO;
	sframe.len = text.size();
	memcpy(sframe.data, text.data(), text.size());

	//send frame to server
	asio::io_service io_service; // Any program that uses asio need to have at least one io_service object
	asio::ip::tcp::socket socket(io_service); //create client socket
	socket.connect(asio::ip::tcp::endpoint(asio::ip::address_v4::from_string(ip), port)); //connect to server

	std::cout << "C: Send echo request with data: " << text << std::endl;
	asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));

	//receive echo
	Frame rframe;
	asio::read(socket, asio::buffer(&rframe, sizeof(Frame)));
	std::cout << "C: Echo is: " << std::string((const char*)rframe.data, rframe.len) << std::endl;
}

void Client::Text(const std::string text, const std::string ip, const unsigned short port) {
	Frame sframe;
	sframe.type = Frame::Type::TEXT;
	sframe.len = text.size();
	memcpy(sframe.data, text.data(), text.size());

	asio::io_service io_service;
	asio::ip::tcp::socket socket(io_service);
	socket.connect(asio::ip::tcp::endpoint(asio::ip::address_v4::from_string(ip), port));

	std::cout << "C: Send text request with data: " << text << std::endl;
	asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));
}

bool Client::RecvFile(const std::string serverFilePath, const std::string clientFilePath,
	const std::string ip, const unsigned short port){

	//prepare frame
	Frame sframe;
	sframe.type = Frame::Type::RECV_FILE;
	sframe.len = serverFilePath.size();
	memcpy(sframe.data, serverFilePath.data(), sframe.len);

	asio::io_service io_service; // Any program that uses asio need to have at least one io_service object
	asio::ip::tcp::socket socket(io_service); //create client socket
	socket.connect(asio::ip::tcp::endpoint(asio::ip::address_v4::from_string(ip), port)); //connect to server
	asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));

	BinFile file(clientFilePath, true);
	Frame rframe;
	bool retVal = false;
	if (file.IsOpen()) {
		do {
			asio::read(socket, asio::buffer(&rframe, sizeof(Frame)));
			if (rframe.type == Frame::Type::FILE_DATA) {
				file.Append(rframe.data, rframe.len);
			}
		} while (rframe.type == Frame::Type::FILE_DATA);
		retVal = rframe.type == Frame::Type::END_OF_FILE;
	}
	return retVal;
}

bool Client::SendFile(const std::string filePathClient, const std::string filePathServer, const std::string ip,
	const unsigned short port) {

	// open file to send
	BinFile file(filePathClient, false);
	
	// initial frame
	Frame sframe;
	sframe.type = Frame::Type::SEND_FILE;
	sframe.len = filePathServer.size();
	memcpy(sframe.data, filePathServer.data(), sframe.len);


	asio::io_service io_service;
	asio::ip::tcp::socket socket(io_service);
	socket.connect(asio::ip::tcp::endpoint(asio::ip::address_v4::from_string(ip), port));
	asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));

	bool retVal = false;
	if (file.IsOpen()) {
		size_t len;
		while (len = file.Read(sframe.data, sizeof(sframe.data))) {
			std::cout << "C: Sending file...\n";
			sframe.type = Frame::Type::FILE_DATA;
			sframe.len = len;
			asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));
		};
		sframe.type = Frame::Type::END_OF_FILE;
		sframe.len = 0;
		asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));
		retVal = sframe.type == Frame::Type::END_OF_FILE;
	}
	else {
		//TODO
	}
	return retVal;
}