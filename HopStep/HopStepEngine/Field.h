#pragma once

namespace HopStep::CoreObject::Reflection
{
	/**
	* Object that has name on it.
	*/
	class HField
	{
	public:

		HField(std::wstring& InName) : Name(InName) {}

		virtual ~HField() {}

		const std::wstring& GetName() const { return Name; }

	protected:

		std::wstring Name;
	};
}
