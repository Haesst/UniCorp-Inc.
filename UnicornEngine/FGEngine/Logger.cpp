#pragma warning( push )
#pragma warning (disable : 26812 )

#include "Logger.h"

#include <iostream>
#include <fstream>

namespace FG
{
	const std::string Logger::logFile = "log.txt";

	void Logger::Log(const std::string& message, const std::string& inFile /*= ""*/, int atLine /*= 0*/)
	{
		static bool isInitialized = false;
	
		std::cout << "[Logger] " << inFile << "(" << atLine << ") " << message << std::endl;

		std::fstream::_Openmode openMode;

		if (isInitialized)
		{
			openMode = std::fstream::app;
		}
		else
		{
			openMode = std::fstream::out;
		}

		std::ofstream file(logFile, openMode);
		if (!file.is_open())
		{
			return;
		}

		file << inFile << " (" << atLine << ")\t" << message << std::endl;
		file.close();
	}

	void Logger::LogSDL(void* userData, int category, SDL_LogPriority, const char* message)
	{
		Log(message);
	}

	std::string Logger::RemovePathFromFile(const std::string& file)
	{
		return std::string(file).substr(0, file.find_last_of("\\/"));
	}

}

#pragma warning ( pop )