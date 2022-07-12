#pragma once
#include "LoggerBase.h"
#include "..\..\HopStepOverrides.h"

namespace HopStep::Core::Logger
{
	class HConsoleLogger final : public HLoggerBase
	{
	public:

		HConsoleLogger() {};
		virtual ~HConsoleLogger() {};

	protected:

		void ConsoleOut(const ConsoleColor Color, const wchar_t* InLogHead, const HStringView& InStringView)
		{
			std::lock_guard<std::mutex> WriteLock(Lock);
			SetConsoleOutColor(Color);

			std::cout << InLogHead << InStringView << std::endl;
		}

		void SetConsoleOutColor(const ConsoleColor Color)
		{
#if HopStep_On_Windows
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color);
#endif
		}

		virtual void Trace(HStringView& InText)
		{
			ConsoleOut(ConsoleColor::Blue, L"[TRACE] ", InText);
		}

		virtual void Info(HStringView& InText)
		{
			ConsoleOut(ConsoleColor::Green, L"[INFO] ", InText);
		}

		virtual void Error(HStringView& InText)
		{
			ConsoleOut(ConsoleColor::Red, L"[ERROR] ", InText);
		}

		virtual void Warn(HStringView& InText)
		{
			ConsoleOut(ConsoleColor::Yellow, L"[WARN] ", InText);
		}

		virtual void Debug(HStringView& InText)
		{
#if _DEBUG
			ConsoleOut(ConsoleColor::White, L"[DEBUG] ", InText);
#endif
		}
	};
}
