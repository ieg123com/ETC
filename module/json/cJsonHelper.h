#pragma once
#include "cJSON.h"
#include <string>


cJSON* cJSON_Create(const std::string& val);
cJSON* cJSON_Create(const char* val);
cJSON* cJSON_Create(const int32& val);
cJSON* cJSON_Create(const uint32& val);
cJSON* cJSON_Create(const int64& val);
cJSON* cJSON_Create(const uint64& val);
cJSON* cJSON_Create(const bool val);
cJSON* cJSON_Create(const float& val);
cJSON* cJSON_Create(const double& val);

cJSON* cJSON_Add(cJSON* json, cJSON* val);
cJSON* cJSON_Add(cJSON* json, const std::string& val);
cJSON* cJSON_Add(cJSON* json, const char* val);
cJSON* cJSON_Add(cJSON* json, const int32& val);
cJSON* cJSON_Add(cJSON* json, const uint32& val);
cJSON* cJSON_Add(cJSON* json, const int64& val);
cJSON* cJSON_Add(cJSON* json, const uint64& val);
cJSON* cJSON_Add(cJSON* json, const bool val);
cJSON* cJSON_Add(cJSON* json, const float& val);
cJSON* cJSON_Add(cJSON* json, const double& val);

cJSON* cJSON_Add(cJSON* json, const char* key, cJSON* val);
cJSON* cJSON_Add(cJSON* json, const char* key, const std::string& val);
cJSON* cJSON_Add(cJSON* json, const char* key, const char* val);
cJSON* cJSON_Add(cJSON* json, const char* key, const int64& val);
cJSON* cJSON_Add(cJSON* json, const char* key, const uint64& val);
cJSON* cJSON_Add(cJSON* json, const char* key, const double& val);

bool cJSON_Get(cJSON* json, std::string& val);
bool cJSON_Get(cJSON* json, int32& val);
bool cJSON_Get(cJSON* json, uint32& val);
bool cJSON_Get(cJSON* json, int64& val);
bool cJSON_Get(cJSON* json, uint64& val);
bool cJSON_Get(cJSON* json, bool& val);
bool cJSON_Get(cJSON* json, float& val);
bool cJSON_Get(cJSON* json, double& val);

bool cJSON_Get(cJSON* json, const char* key, cJSON*& val);
bool cJSON_Get(cJSON* json, const char* key, std::string& val);
bool cJSON_Get(cJSON* json, const char* key, int32& val);
bool cJSON_Get(cJSON* json, const char* key, uint32& val);
bool cJSON_Get(cJSON* json, const char* key, int64& val);
bool cJSON_Get(cJSON* json, const char* key, uint64& val);
bool cJSON_Get(cJSON* json, const char* key, bool& val);
bool cJSON_Get(cJSON* json, const char* key, float& val);
bool cJSON_Get(cJSON* json, const char* key, double& val);
cJSON* cJSON_Get(cJSON* json, const char* key);

cJSON* cJSON_Next(cJSON* json);


std::string cJSON_ToString(cJSON* json);

