#pragma once
#include "ILogger.h"
#include <spdlog/spdlog.h>

namespace GNF::SU::Logging
{
	class Logger : public ILogger
	{
	public:
		Logger() = default;

		inline virtual void Info(const std::string& msg) override
		{
			BaseInfo(msg);
		}

		inline virtual void Info(const char* msg) override
		{
			BaseInfo(msg);
		}


		inline virtual void	Warn(const std::string& msg)
		{
			BaseWarn(msg);
		}

		inline virtual void	Warn(const char* msg)
		{
			BaseWarn(msg);
		}

		inline virtual void Error(const std::string& msg)
		{
			BaseError(msg);
		}

		inline virtual void Error(const char* msg)
		{
			BaseError(msg);
		}

		inline virtual void Critical(const std::string& msg)
		{
			BaseCritical(msg);
		}

		inline virtual void Critical(const char* msg)
		{
			BaseCritical(msg);
		}

		inline virtual void Debug(const std::string& msg)
		{
			BaseDebug(msg);
		}

		inline virtual void Debug(const char* msg)
		{
			BaseDebug(msg);
		}
	protected:
		template<typename T>
		inline void BaseInfo(T msg)
		{
			spdlog::info(msg);
		}

		template<typename T>
		inline void BaseWarn(T msg)
		{
			spdlog::warn(msg);
		}

		template<typename T>
		inline void BaseError(T msg)
		{
			spdlog::error(msg);
		}

		template<typename T>
		inline void BaseCritical(T msg)
		{
			spdlog::critical(msg);
		}

		template<typename T>
		inline void BaseDebug(T msg)
		{
			spdlog::debug(msg);
		}


	};
}