#pragma once
#include <string>
#include "asio.hpp"
class Client
{
public:
	static void Echo(const std::string text, const std::string ip, const unsigned short port);
	static void Text(const std::string text, const std::string ip, const unsigned short port);
	static bool RecvFile(const std::string, const std::string, const std::string,
		const unsigned short);
	static bool SendFile(const std::string, const std::string, const std::string,
		const unsigned short);
};

