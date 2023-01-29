#pragma once

template <typename TComObject> struct TRemoveReference { typedef TComObject Type; };
template <typename TComObject> struct TRemoveReference<TComObject&> { typedef TComObject Type; };
template <typename TComObject> struct TRemoveReference<TComObject&&> { typedef TComObject Type; };