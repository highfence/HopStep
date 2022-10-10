#pragma once

/**
 * Reference Unreal Engine LazySingleton
 */
class HLazySingletonBase
{
protected:
	template <class T> static void Construct(void* Place) { new (Place) T; }
	template <class T> static void Destruct(T* Instance) { Instance->~T(); }
};

template <class T>
class TLazySingleton final : public HLazySingletonBase
{
public:

	static T& GetPropertyPtr()
	{
		return GetLazy(Construct<T>).GetPtr();
	}

	static void TearDown()
	{
		return GetLazy(nullptr).Reset();
	}

	static T* TryGet()
	{
		return GetLazy(Construct<T>).TryGetValue();
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
	alignas(T) unsigned char Data[sizeof(T)];

	/**
	 * 
	 */
	T* Ptr;

	TLazySingleton(void(*Constructor)(void*))
	{
		if (Constructor)
		{
			Constructor(Data);
		}

		Ptr = Constructor ? (T*)Data : nullptr;
	}

	~TLazySingleton()
	{
		Reset();
	}

	T* TryGetValue() 
	{
		return Ptr; 
	}

	T& GetPtr() 
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
