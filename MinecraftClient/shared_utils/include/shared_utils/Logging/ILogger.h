#pragma once

#include <string>

namespace GNF::SU::Logging
{
	class ILogger
	{
	public:
		virtual ~ILogger() = default;

		inline virtual void Info(const std::string& msg) = 0;

		inline virtual void Info(const char* msg) = 0;

		inline virtual void	Warn(const std::string& msg) = 0;

		inline virtual void	Warn(const char* msg) = 0;

		inline virtual void Error(const std::string& msg) = 0;

		inline virtual void Error(const char* msg) = 0;

		inline virtual void Critical(const std::string& msg) = 0;

		inline virtual void Critical(const char* msg) = 0;

		inline virtual void Debug(const std::string& msg) = 0;

		inline virtual void Debug(const char* msg) = 0;
	};
}