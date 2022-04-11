#pragma once
#include "PrimitiveTypeDefines.h"
#include <mutex>
#include <string>
#include <wchar.h>

namespace HopStep::Core::Logger
{
	constexpr int32 ConsoleLogMaxLength = 256;

	enum class LogType : uint8
	{
		Trace = 1,
		Info = 2,
		Error = 3,
		Warn = 4,
		Debug = 5
	};

	class HLoggerBase
	{
	public:

		HLoggerBase() {};
		virtual ~HLoggerBase() {};

		virtual void Write(const LogType Type, const wchar_t* ArgFormat, ...)
		{
			wchar_t LogText[ConsoleLogMaxLength]{};

			va_list Args = nullptr;
			__va_start(&Args, ArgFormat);
			vswprintf_s(LogText, ConsoleLogMaxLength, ArgFormat, Args);
			__crt_va_end(Args);

			std::wstring_view LogTextView(LogText);

			switch (Type)
			{
			case LogType::Trace:
				Trace(LogTextView);
				break;

			case LogType::Info:
				Info(LogTextView);
				break;

			case LogType::Error:
				Error(LogTextView);
				break;

			case LogType::Warn:
				Warn(LogTextView);
				break;

			case LogType::Debug:
				Debug(LogTextView);
				break;

			}
		}

	protected:

		enum class ConsoleColor : uint8
		{
			Green = 2,
			Blue = 9,
			Red = 12,
			Yellow = 14,
			White = 15
		};

		std::mutex Lock;

		virtual void Trace(std::wstring_view& InText) abstract;
		virtual void Info(std::wstring_view& InText) abstract;
		virtual void Error(std::wstring_view& InText) abstract;
		virtual void Warn(std::wstring_view& InText) abstract;
		virtual void Debug(std::wstring_view& InText) abstract;
	};
}
