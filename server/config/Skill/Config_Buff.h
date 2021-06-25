#pragma once
#include "config/Config.h"


class Config_Buff:
	public Config
{
public:

	// buff鍚?
	std::string	Name;

	// 浠嬬粛
	std::string	Content;

	std::string	UI;

	// 浣跨敤鏂规硶鍚?
	std::string	BuffMethod;

	// 褰卞搷镄勫睘镐d
	int32_t	PropID0;

	// 褰卞搷链?
	int32_t	Value0;

	int32_t	PropID1;

	int32_t	Value1;

	int32_t	PropID2;

	int32_t	Value2;

	int32_t	PropID3;

	int32_t	Value3;

	int32_t	PropID4;

	int32_t	Value4;

	int32_t	PropID5;

	int32_t	Value5;

private:

	virtual bool Parse(const cJson& json) override {
		json.Get("Id",Id);
		json.Get("Name",Name);
		json.Get("Content",Content);
		json.Get("UI",UI);
		json.Get("BuffMethod",BuffMethod);
		json.Get("PropID0",PropID0);
		json.Get("Value0",Value0);
		json.Get("PropID1",PropID1);
		json.Get("Value1",Value1);
		json.Get("PropID2",PropID2);
		json.Get("Value2",Value2);
		json.Get("PropID3",PropID3);
		json.Get("Value3",Value3);
		json.Get("PropID4",PropID4);
		json.Get("Value4",Value4);
		json.Get("PropID5",PropID5);
		json.Get("Value5",Value5);
		return true;
	}
};
