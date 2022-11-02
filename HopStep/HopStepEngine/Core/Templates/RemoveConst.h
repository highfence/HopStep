#pragma once

template <class TType>
struct TRemoveConst
{
	typedef TType Type;
};

template <class TType>
struct TRemoveConst<const TType>
{
	typedef TType Type;
};
