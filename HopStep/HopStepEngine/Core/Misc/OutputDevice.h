#pragma once
#include "Core/HopStepCore.h"
#include "Core/Logger/LoggerBase.h"

using namespace HopStep;

/**
 *
 */
class IOutputDevice
{
public:

	/**
	 * todo : string view to HName
	 */
	virtual void Serialize(const HChar* Value, Core::Logger::LogType Verbosity, const HStringView& Catergory) abstract;
};

/**
 *
 */
class HStringOutputDevice : public IOutputDevice
{
public:

	virtual void Serialize(const HChar* Value, Core::Logger::LogType Verbosity, const HStringView& Catergory) override;

private :

};