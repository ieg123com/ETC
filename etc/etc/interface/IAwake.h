#pragma once


template<typename ...Type>
class IAwake
{
	virtual void Awake(Type ... Args) = 0;
};