#pragma once

#define LEN 1024

struct Frame {
	enum Type {
		ECHO,
		TEXT,
		RECV_FILE,
		SEND_FILE,
		FILE_DATA,
		END_OF_FILE,
		INVALID_COMMAND
	};

	uint8_t type;
	uint16_t len;
	uint8_t data[LEN];
};