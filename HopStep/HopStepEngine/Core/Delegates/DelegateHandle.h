#pragma once
#include "..\PrimitiveTypeDefines.h"

namespace HopStep
{
	class HDelegateHandle
	{
	public:

		enum EDelegateHandleGenerateType
		{
			NewHandleIDGenerate
		};

		/**
		 * 
		 */
		HDelegateHandle()
			: ID(0LL)
		{

		}

		/**
		 * 
		 */
		explicit HDelegateHandle(EDelegateHandleGenerateType)
			: ID(GenerateNewID())
		{

		}

		/**
		 * 
		 */
		bool IsValid() const 
		{
			return ID != 0LL;
		}

		/**
		 * 
		 */
		void Reset()
		{
			ID = 0;
		}


	private:

		static uint64 GenerateNewID();

		uint64 ID;
	};
}