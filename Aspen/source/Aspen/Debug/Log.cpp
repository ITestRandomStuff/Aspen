#include "aspch.h"
#include "Log.h"

#include <iostream>

namespace Aspen
{
	std::string Logger::m_Name;
	std::string Logger::m_Message;

	std::string Red = "\033[31m";
	std::string Yellow = "\033[33m";
	std::string Cyan = "\033[36m";
	std::string White = "\033[37m";

	std::string BoldRed = "\033[31m\033[1m";

	void Logger::SetName(const std::string& name)
	{
		m_Name = name;
		m_Message = '[' + name + "]";
	}

	void Logger::SetColor(const std::string& color)
	{
		std::cout << color;
	}

	void Logger::Trace(const std::string& msg, int line, const std::string filename)
	{
		std::cout << m_Message << " " << filename << "(" << line << "): " << msg << '\n';
		// ['Aspen'] main.cpp(10): Hello, World!
	}

	void Logger::Trace(const std::string& msg)
	{
		std::cout << m_Message << ": " << msg << '\n';
	}

	void Logger::Info(const std::string& msg, int line, const std::string filename)
	{
		SetColor(Logger::Cyan);
		Trace(msg, line, filename);
		SetColor(Logger::White);
	}

	void Logger::Info(const std::string& msg)
	{
		SetColor(Logger::Cyan);
		Trace(msg);
		SetColor(Logger::White);
	}

	void Logger::Warn(const std::string& msg, int line, const std::string filename)
	{
		SetColor(Logger::Yellow);
		Trace(msg, line, filename);
		SetColor(Logger::White);
	}
	
	void Logger::Warn(const std::string& msg)
	{
		SetColor(Logger::Yellow);
		Trace(msg);
		SetColor(Logger::White);
	}

	void Logger::Error(const std::string& msg, int line, const std::string filename)
	{
		SetColor(Logger::BoldRed);
		Trace(msg, line, filename);
		SetColor(Logger::White);
	}
	
	void Logger::Error(const std::string& msg)
	{
		SetColor(Logger::BoldRed);
		Trace(msg);
		SetColor(Logger::White);
	}

	void Logger::Critical(const std::string& msg, int line, const std::string filename)
	{
		SetColor(Logger::Red);
		Trace(msg, line, filename);
		SetColor(Logger::White);
	}
	
	void Logger::Critical(const std::string& msg)
	{
		SetColor(Logger::Red);
		Trace(msg);
		SetColor(Logger::White);
	}
}