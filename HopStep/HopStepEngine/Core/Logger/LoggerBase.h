#pragma once
#include "Core\PrimitiveTypeDefines.h"
#include "Core\CoreStandardIncludes.h"
#include "Core\HopStepOverrides.h"

namespace HopStep
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

		virtual void Write(const LogType Type, const HChar* ArgFormat, ...)
		{
			HChar LogText[ConsoleLogMaxLength]{};

			va_list Args = nullptr;
			__va_start(&Args, ArgFormat);
			vswprintf_s(LogText, ConsoleLogMaxLength, ArgFormat, Args);
			__crt_va_end(Args);

			HStringView LogTextView(LogText);

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

		virtual void Trace(HStringView& InText) abstract;
		virtual void Info(HStringView& InText) abstract;
		virtual void Error(HStringView& InText) abstract;
		virtual void Warn(HStringView& InText) abstract;
		virtual void Debug(HStringView& InText) abstract;
	};
}
