#pragma once

template <class TType>
concept StaticClassGetable = requires(TType Type)
{
	TType::StaticClass();
};
