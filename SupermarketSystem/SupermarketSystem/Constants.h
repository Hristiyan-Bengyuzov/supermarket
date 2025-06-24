#pragma once

namespace Constants {
	static const char* RESET = "\033[0m";
	static const char* ARG = "\033[33m";  // Yellow for arguments
	static const char* CMD = "\033[1m";   // Bold for commands
	static const char* HEADER = "\033[1;36m"; // Bold cyan for headers
	static const char* SUCCESS = "\033[32m"; // Green
	static const char* FAILURE = "\033[31m"; // Red
	static const size_t BUFFER_SIZE = 1025;
	static const char* PINK = "\033[95m"; 
}