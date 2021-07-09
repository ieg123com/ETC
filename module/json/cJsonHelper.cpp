#include "cJsonHelper.h"



cJSON* cJSON_Create(const std::string& val)
{
	return cJSON_CreateString(val.c_str());
}

cJSON* cJSON_Create(const char* val)
{
	return cJSON_CreateString(val);
}

cJSON* cJSON_Create(const int32& val)
{
	return cJSON_CreateInt((uint64)val, -1);
}

cJSON* cJSON_Create(const uint32& val)
{
	return cJSON_CreateInt((uint64)val, 1);
}

cJSON* cJSON_Create(const int64& val)
{
	return cJSON_CreateInt((uint64)val, -1);
}

cJSON* cJSON_Create(const uint64& val)
{
	return cJSON_CreateInt(val, 1);
}

cJSON* cJSON_Create(const bool val)
{
	return cJSON_CreateBool((int)val);
}

cJSON* cJSON_Create(const float& val)
{
	return cJSON_CreateDouble((double)val, -1);
}

cJSON* cJSON_Create(const double& val)
{
	return cJSON_CreateDouble(val, -1);
}

cJSON* cJSON_Add(cJSON* json, cJSON* val)
{
	cJSON_AddItemToArray(json, val);
	return val;
}

cJSON* cJSON_Add(cJSON* json, const std::string& val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToArray(json, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const char* val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToArray(json, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const int32& val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToArray(json, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const uint32& val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToArray(json, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const int64& val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToArray(json, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const uint64& val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToArray(json, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const float& val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToArray(json, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const bool val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToArray(json, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const double& val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToArray(json, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const char* key, cJSON* val)
{
	cJSON_AddItemToObject(json, key, val);
	return val;
}

cJSON* cJSON_Add(cJSON* json, const char* key, const std::string& val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToObject(json, key, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const char* key, const char* val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToObject(json, key, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const char* key, const int64& val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToObject(json, key, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const char* key, const uint64& val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToObject(json, key, pjson);
	return pjson;
}

cJSON* cJSON_Add(cJSON* json, const char* key, const double& val)
{
	cJSON* pjson = cJSON_Create(val);
	cJSON_AddItemToObject(json, key, pjson);
	return pjson;
}


bool cJSON_Get(cJSON* json, std::string& val)
{
	if (json == NULL)
	{
		return(false);
	}
	if (json->type != cJSON_String)
	{
		return(false);
	}
	val = json->valuestring;
	return(true);
}

bool cJSON_Get(cJSON* json, int32& val)
{
	if (json == NULL)
	{
		return(false);
	}
	if (json->type == cJSON_Int)
	{
		val = (int32)(json->valueint);
		return(true);
	}
	else if (json->type == cJSON_Double)
	{
		val = (int32)(json->valuedouble);
		return(true);
	}
	return(false);
}

bool cJSON_Get(cJSON* json, uint32& val)
{
	if (json == NULL)
	{
		return(false);
	}
	if (json->type == cJSON_Int)
	{
		val = (uint32)(json->valueint);
		return(true);
	}
	else if (json->type == cJSON_Double)
	{
		val = (uint32)(json->valuedouble);
		return(true);
	}
	return(false);
}

bool cJSON_Get(cJSON* json, int64& val)
{
	if (json == NULL)
	{
		return(false);
	}
	if (json->type == cJSON_Int)
	{
		val = (int64)(json->valueint);
		return(true);
	}
	else if (json->type == cJSON_Double)
	{
		val = (int64)(json->valuedouble);
		return(true);
	}
	return(false);
}

bool cJSON_Get(cJSON* json, uint64& val)
{
	if (json == NULL)
	{
		return(false);
	}
	if (json->type == cJSON_Int)
	{
		val = (uint64)(json->valueint);
		return(true);
	}
	else if (json->type == cJSON_Double)
	{
		val = (uint64)(json->valuedouble);
		return(true);
	}
	return(false);
}

bool cJSON_Get(cJSON* json, bool& val)
{
	if (json == NULL)
	{
		return(false);
	}
	if (json->type > cJSON_True)
	{
		return(false);
	}
	val = json->type;
	return(true);
}

bool cJSON_Get(cJSON* json, float& val)
{
	if (json == NULL)
	{
		return(false);
	}
	if (json->type == cJSON_Double)
	{
		val = (float)json->valuedouble;
		return(true);
	}
	else if (json->type == cJSON_Int)
	{
		val = (float)(json->valueint);
		return(true);
	}
	return(false);
}

bool cJSON_Get(cJSON* json, double& val)
{
	if (json == NULL)
	{
		return(false);
	}
	if (json->type == cJSON_Double)
	{
		val = json->valuedouble;
		return(true);
	}
	else if (json->type == cJSON_Int)
	{
		val = (double)(json->valueint);
		return(true);
	}
	return(false);
}

bool cJSON_Get(cJSON* json, const char* key, cJSON*& val)
{
	if (json != NULL)
	{
		val = cJSON_GetObjectItem(json, key);
		return(true);
	}
	return(false);
}

bool cJSON_Get(cJSON* json, const char* key, std::string& val)
{
	cJSON* pJson = NULL;
	if (json != NULL)
	{
		pJson = cJSON_GetObjectItem(json, key);
	}
	return cJSON_Get(pJson, val);
}

bool cJSON_Get(cJSON* json, const char* key, int32& val)
{
	cJSON* pJson = NULL;
	if (json != NULL)
	{
		pJson = cJSON_GetObjectItem(json, key);
	}
	return cJSON_Get(pJson, val);
}

bool cJSON_Get(cJSON* json, const char* key, uint32& val)
{
	cJSON* pJson = NULL;
	if (json != NULL)
	{
		pJson = cJSON_GetObjectItem(json, key);
	}
	return cJSON_Get(pJson, val);
}

bool cJSON_Get(cJSON* json, const char* key, int64& val)
{
	cJSON* pJson = NULL;
	if (json != NULL)
	{
		pJson = cJSON_GetObjectItem(json, key);
	}
	return cJSON_Get(pJson, val);
}

bool cJSON_Get(cJSON* json, const char* key, uint64& val)
{
	cJSON* pJson = NULL;
	if (json != NULL)
	{
		pJson = cJSON_GetObjectItem(json, key);
	}
	return cJSON_Get(pJson, val);
}

bool cJSON_Get(cJSON* json, const char* key, bool& val)
{
	cJSON* pJson = NULL;
	if (json != NULL)
	{
		pJson = cJSON_GetObjectItem(json, key);
	}
	return cJSON_Get(pJson, val);
}

bool cJSON_Get(cJSON* json, const char* key, float& val)
{
	cJSON* pJson = NULL;
	if (json != NULL)
	{
		pJson = cJSON_GetObjectItem(json, key);
	}
	return cJSON_Get(pJson, val);
}

bool cJSON_Get(cJSON* json, const char* key, double& val)
{
	cJSON* pJson = NULL;
	if (json != NULL)
	{
		pJson = cJSON_GetObjectItem(json, key);
	}
	return cJSON_Get(pJson, val);
}

cJSON* cJSON_Get(cJSON* json, const char* key)
{
	cJSON* pJson = NULL;
	if (json != NULL)
	{
		pJson = cJSON_GetObjectItem(json, key);
	}
	return pJson;
}

cJSON* cJSON_Next(cJSON* json)
{
	return cJSON_GetArrayItem(json, 0);
}

std::string cJSON_ToString(cJSON* json)
{
	std::string json_data = "";
	char* pdata = NULL;
	pdata = cJSON_PrintUnformatted(json);
	if (pdata != NULL)
	{
		json_data = pdata;
		free(pdata);
	}
	return json_data;
}