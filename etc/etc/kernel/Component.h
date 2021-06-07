#pragma once
#include "Object.h"


class Component :
	public Object
{
public:

	virtual void Dispose() {
		if (Object::IsDisposed()) {
			return;
		}
		else {
			Object::Dispose();
		}
	}



};