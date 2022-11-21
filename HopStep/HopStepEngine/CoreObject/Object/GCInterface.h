#pragma once

namespace HopStep
{
	/**
	 * Who wants to managed by Garbage collector, must inherit this interface.
	 */
	class IGCObject
	{
	public:

		virtual ~IGCObject() = default;


	};
}
