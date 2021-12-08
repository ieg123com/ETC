#pragma once
#include "type/type.h"
#include "type/type_factory.h"
#include "interface/ISupportTypeCreation.h"

using namespace Model;

class IMSystemHandler :
	public ISupportTypeCreation
{
public:
	virtual const Type GetRequestType() const = 0;
	virtual const Type GetResponseType() const = 0;

	int32_t appType = 0;
};