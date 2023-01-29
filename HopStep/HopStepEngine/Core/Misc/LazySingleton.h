#pragma once

/**
 * Reference Unreal Engine LazySingleton
 */
class HLazySingletonBase
{
protected:
	template <class TComObject> static void Construct(void* Place) { new (Place) TComObject; }
	template <class TComObject> static void Destruct(TComObject* Instance) { Instance->~TComObject(); }
};

template <class TComObject>
class TLazySingleton final : public HLazySingletonBase
{
public:

	static TComObject& GetPropertyPtr()
	{
		return GetLazy(Construct<TComObject>).GetPtr();
	}

	static void TearDown()
	{
		return GetLazy(nullptr).Reset();
	}

	static TComObject* TryGet()
	{
		return GetLazy(Construct<TComObject>).TryGetValue();
	}

private:

	static TLazySingleton& GetLazy(void(*Constructor)(void*))
	{
		static TLazySingleton Singleton(Constructor);
		return Singleton;
	}

	/**
	 * 
	 */
	alignas(TComObject) unsigned char Data[sizeof(TComObject)];

	/**
	 * 
	 */
	TComObject* Ptr;

	TLazySingleton(void(*Constructor)(void*))
	{
		if (Constructor)
		{
			Constructor(Data);
		}

		Ptr = Constructor ? (TComObject*)Data : nullptr;
	}

	~TLazySingleton()
	{
		Reset();
	}

	TComObject* TryGetValue() 
	{
		return Ptr; 
	}

	TComObject& GetPtr() 
	{
		return *Ptr; 
	}

	void Reset()
	{
		if (Ptr)
		{
			Destruct(Ptr);
			Ptr = nullptr;
		}
	}
};
