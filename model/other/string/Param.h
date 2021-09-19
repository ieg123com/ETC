#pragma once
#include <map>
#include "str.h"


namespace std
{

	//string GetParamValue(const map<string, string>& params, const string& key);

	template<typename T>
	T GetParamValue(const map<string, string>& params, const string& key) {
		auto found = params.find(key);
		if (found == params.end())
		{
			return to<T>("");
		}
		return to<T>(found->second);
	}

	string GetParamValue(const map<string, string>& params, const string& key) {
		auto found = params.find(key);
		if (found == params.end())
		{
			return "";
		}
		return found->second;
	}
}
