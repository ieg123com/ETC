#pragma once


#include "reflection_attribute.h"
#include "reflection_assembly.h"
#include "reflection_system.h"




#define REF_VAR_NAME(_class,_line) g_reflection_task_##_class##_line

#define REF_B(_class,_attr,_line) \
Model::AddDomainTask REF_VAR_NAME(_class,_line)([] {\
Model::Reflection::ISystem<_class> ref_sys;\
ref_sys.Add(new _attr);\
	});

/**
 * @brief	∑¥…‰
 */
#define REF(_class,_attr) REF_B(_class,_attr,__LINE__)