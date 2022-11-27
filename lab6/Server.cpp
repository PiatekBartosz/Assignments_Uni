#include <iostream>
#include <thread> 
#include "BinFile.h"
#include "Frame.h"
#include "Server.h"
#include "asio.hpp"


Server::Server(unsigned short port) : port(port)
{
}


Server::~Server()
{
}


//communication session handler (ECHO)
void session(asio::ip::tcp::socket socket)
{
	try
	{
		while (true)
		{
			Frame rframe;
			asio::read(socket, asio::buffer(&rframe, sizeof(Frame)));

			switch (rframe.type) {
			case Frame::Type::ECHO: {
				Frame sframe = rframe;
				asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));
			}
								  break;

			case Frame::Type::TEXT: {
				std::cout << "S: Text is: " << std::string((const char*)rframe.data, rframe.len) << "\n";
			}
								  break;

			case Frame::Type::RECV_FILE: {

				//get file path from first frame
				std::string filePath((const char*)rframe.data, rframe.len);
				BinFile file(filePath, false);
				Frame sframe;
				if (file.IsOpen()) {
					size_t len;
					while (len = file.Read(sframe.data, sizeof(sframe.data))) {
						sframe.type = Frame::Type::FILE_DATA;
						sframe.len = len;
						asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));
					}
					sframe.type = Frame::Type::END_OF_FILE;
					sframe.len = 0;
					asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));
				}
				else {
					//TODO
					sframe.type = Frame::Type::INVALID_COMMAND;
					sframe.len = 0;
					asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));
				}
			}
									   break;

			case Frame::Type::SEND_FILE: {

				std::string filePath((const char*)rframe.data, rframe.len);
				BinFile file(filePath, true);

				if (file.IsOpen()) {
					size_t len;
					do
					{
						asio::read(socket, asio::buffer(&rframe, sizeof(Frame)));
						if (rframe.type == Frame::Type::FILE_DATA){
						
							file.Append(rframe.data, rframe.len);
						}
					} while (rframe.type = Frame::Type::FILE_DATA);
				}

			}
									   break;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void Server::ThreadRoutine()
{
	asio::io_service io_service; // Any program that uses asio need to have at least one io_service object
	asio::ip::tcp::acceptor acceptor(io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)); //create acceptor for listening purposes
	acceptor.listen(1024);
	while (isRunning())
	{
		asio::ip::tcp::socket socket(io_service); //create a socket for communication purposes
		acceptor.accept(socket); //then accept connection
		
		//read data sent by the client, then send echo
		std::thread(session, std::move(socket)).detach();

		std::this_thread::yield();
	}
}
