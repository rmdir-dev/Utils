
#if __linux__ == 1

#include "Utils/Log.h"
#include <signal.h>
#include "Utils/pch.h"

namespace Log
{
	void platformLogMessage(LogLevel level, const char* message)
	{
        //Reset the terminal colors to normal.
		std::string reset = "\033[0m";
        //Create a new line
		reset += '\n';

		switch (level)
		{
		case LogLevel::Info:
			std::cout << "\033[1;37m" << message << reset;
			break;
		case LogLevel::Error:
			std::cout << "\033[1;31m" << "[ERROR] " << message << reset;
			break;
		case LogLevel::Warning:
			std::cout << "\033[1;33m" << "[WARNING] " << message << reset;
			break;
		case LogLevel::Critical:
			std::cout << "\033[1;37;41m" << "[CRITICAL] " << message << reset;
			break;
		default:
			break;
		}
	}

	void platformBreak()
	{
        //Raise a sigtrip to break the program when it catches an assertion.
		raise(SIGTRAP);
	}
}
#endif