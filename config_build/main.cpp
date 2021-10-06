#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <io.h>
#include <direct.h>
#include <queue>
#include "xlnt/xlnt.hpp"
#include "./json/ejson.h"
#include "model/other/string/str.h"

// key类型
enum class EKeyType : int32_t 
{
	INVALID	= 0,	// 无效类型
	STRING	= 1,	// 文本
	INT		= 2,	// 整数
	LONG	= 3,	// 长整数
	FLOAT	= 4,	// 小数
	DOUBLE	= 5,	// 双精度小数
	STRING_ARRAY= 6,	// 文本[]
	INT_ARRAY	= 7,	// 整数[]
	LONG_ARRAY	= 8,	// 长整数[]
	FLOAT_ARRAY = 9,	// 小数[]
	DOUBLE_ARRAY= 10,	// 双精度小数[]
};

// 转换类型
enum class ECastType:int32_t
{
	CAST_EMPTY = 0,
	XLSX_TO_JSON = 1,
	XLSX_AUTO_GEN_CPP = 2,
};

struct stCellInfo
{
	std::string key_title;
	std::string	key_name;
	EKeyType	key_type;
	bool		not_export;
	stCellInfo()
	{
		key_type = EKeyType::INVALID;
		not_export = true;
	}
};

struct stGenState
{
	std::string folder;
	std::string file_name;
};


static std::string g_xlsx_path = "";
static std::string g_read_config_path = "";
static std::string g_curr_dir = "";
static std::string g_export_type = "server";

EKeyType GetTypeFromName(const std::string& name);

bool IsFolderExist(const char* folder)
{
	bool ret = 0;

	ret = _access(folder, 0);
	if (ret == 0)
		ret = true;
	else
		ret = false;

	return ret;
}

int32_t CreateDirectory(const char* directoryPath)
{
	uint32_t dirPathLen = 0;
	if (directoryPath != NULL) {
		dirPathLen = strlen(directoryPath);
	}
	if (dirPathLen > FILENAME_MAX)
	{
		return -1;
	}
	char tmpDirPath[FILENAME_MAX] = { 0 };
	for (uint32_t i = 0; i < dirPathLen; ++i)
	{
		tmpDirPath[i] = directoryPath[i];
		if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
		{
			if (!IsFolderExist(tmpDirPath))
			{
				int ret = _mkdir(tmpDirPath);
				//BOOL ret = CreateDirectory(tmpDirPath, NULL);
				if (ret != 0)
					return -1;
			}
		}
	}
	return 0;
}

void WriteToFile(const std::string& path, const std::string& data)
{
	CreateDirectory(path.c_str());
	FILE* pf = fopen(path.c_str(), "wb");
	if (pf == nullptr)
	{
		throw std::exception(("failed to open the file to be saved!(" + data + ")").c_str());
	}

	fwrite(data.c_str(), data.size(), 1, pf);
	fclose(pf);
}

std::vector<stCellInfo> GetKey(xlnt::workbook& wb)
{
	auto ws = wb.active_sheet();
	auto row = ws.rows(false);
	auto title_row = row[0];
	auto key_row = row[1];
	auto type_row = row[2];
	auto export_type_row = row[3];
	if (key_row.empty())
	{
		throw std::exception("key row is empty.");
	}
	if (type_row.empty())
	{
		throw std::exception("type row is empty.");
	}

	std::vector<stCellInfo>	all_key;

	int32_t length = key_row.length();
	for (int i = 0; i < length; ++i)
	{
		stCellInfo	new_cell_info;
		new_cell_info.key_name = key_row[i].to_string();
		if (new_cell_info.key_name.empty())
		{
			// key 为空
			all_key.push_back(new_cell_info);
			continue;
		}
		// 标题
		new_cell_info.key_title = title_row[i].to_string();
 
		// 类型
		new_cell_info.key_type = GetTypeFromName(type_row[i].to_string());

		if(new_cell_info.key_type == EKeyType::INVALID)
		{
			std::cout << "uncertain type of key." << std::endl;
			std::cout << "key name:" << key_row[i].to_string().c_str() << std::endl;
			std::cout << "type name:" << type_row[i].to_string().c_str() << std::endl;
			throw std::exception("There is an unresolvable type.");
		}
		// 判断是否需要导出
		auto all_export_type = std::split(export_type_row[i].to_string(), "|");
		for (auto& item : all_export_type)
		{
			if (strcmp(item.c_str(), g_export_type.c_str()) == 0)
			{
				new_cell_info.not_export = false;
				continue;
			}
		}
		

		all_key.push_back(new_cell_info);
	}
	return all_key;
}

EKeyType GetTypeFromName(const std::string& name)
{
	if (strcmp(name.c_str(), "string") == 0) return EKeyType::STRING;
	else if (strcmp(name.c_str(), "int") == 0) return EKeyType::INT;
	else if (strcmp(name.c_str(), "long") == 0) return EKeyType::LONG;
	else if (strcmp(name.c_str(), "float") == 0) return EKeyType::FLOAT;
	else if (strcmp(name.c_str(), "double") == 0) return EKeyType::DOUBLE;
// 	else if (strcmp(name.c_str(), "string[]") == 0) return EKeyType::STRING_ARRAY;
// 	else if (strcmp(name.c_str(), "int[]") == 0) return EKeyType::INT_ARRAY;
// 	else if (strcmp(name.c_str(), "long[]") == 0) return EKeyType::LONG_ARRAY;
// 	else if (strcmp(name.c_str(), "float[]") == 0) return EKeyType::FLOAT_ARRAY;
// 	else if (strcmp(name.c_str(), "double[]") == 0) return EKeyType::DOUBLE_ARRAY;
	return EKeyType::INVALID;
}

std::string GetTypeName(const EKeyType type)
{
	switch (type)
	{
	case EKeyType::STRING:	return "std::string";
	case EKeyType::INT:		return "int32_t";
	case EKeyType::LONG:	return "int64_t";
	case EKeyType::FLOAT:	return "float";
	case EKeyType::DOUBLE:	return "double";
// 	case EKeyType::STRING_ARRAY:return "std::vector<std::string>";
// 	case EKeyType::INT_ARRAY:	return "std::vector<int32_t>";
// 	case EKeyType::LONG_ARRAY:	return "std::vector<int64_t>";
// 	case EKeyType::FLOAT_ARRAY:	return "std::vector<float>";
// 	case EKeyType::DOUBLE_ARRAY:return "std::vector<double>";
	default:
		throw std::exception("There is an unresolvable type.");
		break;
	}
	return "";
}

std::vector<std::string> DiscoverAllFolder(const std::string& path) 
{
	std::vector<std::string> all_dir;
	intptr_t handle;                                                //用于查找的句柄
	struct _finddata_t file_info;                          //文件信息的结构体
	handle = _findfirst(path.c_str(), &file_info);         //第一次查找
	if (-1 == handle)
		return all_dir;
	do {
		if (file_info.attrib == _A_SUBDIR)
		{
			if (!std::strcmp(file_info.name, ".") ||
				!std::strcmp(file_info.name, ".."))
			{
				continue;
			}
			all_dir.push_back(file_info.name);
		}
	} while (_findnext(handle, &file_info) == 0);
	_findclose(handle);
	return all_dir;
}

std::vector<std::string> DiscoverAllFile(const std::string& path)
{
	std::vector<std::string> all_file;
	intptr_t handle;                                                //用于查找的句柄
	struct _finddata_t file_info;                          //文件信息的结构体
	handle = _findfirst(path.c_str(), &file_info);         //第一次查找
	if (-1 == handle)
		return all_file;
	do {
		if (file_info.attrib == _A_ARCH)
		{
			all_file.push_back(file_info.name);
		}
	} while (_findnext(handle, &file_info) == 0);
	_findclose(handle);
	return all_file;
}



std::string GetXlsxFileName(const std::string& path) 
{
	size_t pos = path.find(".");
	return path.substr(0,pos);
}

void XlsxToJson(xlnt::workbook& wb,const std::string& save_path)
{
 	auto ws = wb.active_sheet();
 	auto row = ws.rows(false);
	auto key_row = row[1];
	auto type_row = row[2];
	if (key_row.empty())
	{
		std::cout << "key row is empty." << std::endl;
		return;
	}
	if (type_row.empty())
	{
		std::cout << "type row is empty." << std::endl;
		return;
	}
	
	std::vector<stCellInfo>	all_key = GetKey(wb);

	// 将数据写到json
	neb::CJsonObject save_json;

	int32_t key_size = all_key.size();
	auto iter = row.begin();
	++iter;
	++iter;
	++iter;
	++iter;
	while (iter != row.end())
	{
		if (key_size > 0 && 
			(strcmp((*iter)[0].to_string().substr(0,2).c_str(), "//") == 0||
			strcmp((*iter)[0].to_string().substr(0, 1).c_str(), "#") == 0 ||
			(*iter)[0].to_string().empty()))
		{
			// 注释行，不进行解析
			++iter;
			continue;
		}
		neb::CJsonObject json_buff;
		for (int i = 0; i < key_size; ++i)
		{
			if (all_key[i].not_export)continue;
			switch (all_key[i].key_type)
			{
			case EKeyType::STRING:
			{
				json_buff.Add(all_key[i].key_name, (*iter)[i].to_string());
			}
				break;
			case EKeyType::INT:
			{
				int32_t num_32 = std::to<int32_t>((*iter)[i].to_string());
				json_buff.Add(all_key[i].key_name, num_32);
			}
				break;
			case EKeyType::LONG:
			{
				int64_t num_64 = std::to<int64_t>((*iter)[i].to_string());
				json_buff.Add(all_key[i].key_name, num_64);
			}
			break;
			case EKeyType::FLOAT:
			{
				float numf_32 = std::to<float>((*iter)[i].to_string());
				json_buff.Add(all_key[i].key_name, numf_32);
			}
			break;
			case EKeyType::DOUBLE:
			{
				double numf_64 = std::to<double>((*iter)[i].to_string());
				json_buff.Add(all_key[i].key_name, numf_64);
			}
			break;
			default:
				// 无效类型，不处理
				break;
			}
		}
		save_json.Add(json_buff);
	
		++iter;
	}

	WriteToFile(save_path, save_json.ToString());

	std::cout << "serialized successfully!" << std::endl;
}

void XlsxToCpp(xlnt::workbook& wb, const std::string& cpp_path,const std::string& class_name)
{
	auto all_key = GetKey(wb);

	bool has_id = false;

	static std::string code;
	code.clear();
	code.append("#pragma once\r\n");
	code.append("#include \"config/Config.h\"\r\n");
	code.append("\r\n");
	code.append("\r\n");
	code.append("class " + class_name + ":\r\n");
	code.append("	public Config\r\n");
	code.append("{\r\n");
	code.append("public:\r\n");
	code.append("\r\n");

	// 字段
	for (auto& item : all_key)
	{
		if (item.key_name.empty() ||
			item.not_export)
		{
			continue;
		}
		if (std::strcmp(item.key_name.c_str(), "Id") == 0)
		{
			has_id = true;
			continue;
		}
		if (!item.key_title.empty())
		{
			// 注释
			code.append("	// ");
			code.append(item.key_title);
			code.append("\r\n");
		}
		code.append("	");
		code.append(GetTypeName(item.key_type));
		code.append("	");
		code.append(item.key_name);
		code.append(";\r\n");
		code.append("\r\n");
	}

	code.append("private:\r\n");
	code.append("\r\n");
	code.append("	virtual bool Parse(Json json) override {\r\n");
	// 加载
	for (auto& item : all_key)
	{
		if (item.key_name.empty() ||
			item.not_export)
		{
			continue;
		}
		code.append("		cJSON_Get(json,\"");
		code.append(item.key_name);
		code.append("\",");
		code.append(item.key_name);
		code.append(");\r\n");
	}

	code.append("		return true;\r\n");
	code.append("	}\r\n");
	code.append("};\r\n");

	if (has_id == false)
	{
		throw std::exception("Not be exist key 'Id'");
	}
	WriteToFile(cpp_path, code);
}

void GenInitCpp(const std::vector<stGenState>& all_state, const std::string& code_path)
{
	static std::string code;
	code.clear();
	code.append("#pragma once\r\n");
	
	// 头文件引用
	for (auto& item : all_state)
	{
		code.append("#include \"");
		code.append(item.folder + GetXlsxFileName(item.file_name) + ".h");
		code.append("\"\r\n");
	}

	code.append("\r\n");
	code.append("\r\n");
	code.append("class Config_Init\r\n");
	code.append("{\r\n");
	code.append("public:\r\n");
	code.append("\r\n");
	code.append("	static void Init(){\r\n");

	for (auto& item : all_state)
	{
		code.append("		if(!ConfigComponent::Instance->Load<");
		code.append(GetXlsxFileName(item.file_name));
		code.append(">(\"");
		code.append(g_read_config_path + item.folder + GetXlsxFileName(item.file_name) + ".json");
		code.append("\")) LOG_WARN(\"load '");
		code.append(g_read_config_path + item.folder + GetXlsxFileName(item.file_name) + ".json");
		code.append("' configure file failed!\");\r\n");
	}




	code.append("	}\r\n");
	code.append("};\r\n");


	WriteToFile(code_path +"Config_Init.h", code);


}

void GetWorkBook(xlnt::workbook& wb,const std::string& path)
{
	try {
		wb.load(path);
	}
	catch (xlnt::exception e)
	{
		throw std::exception(e.what());
	}
}

void AppendGenState(std::vector<stGenState>& all_state)
{
	auto all_xlsx = DiscoverAllFile(g_xlsx_path + g_curr_dir + "*.xlsx");
	for (auto& item : all_xlsx)
	{
		stGenState new_state;
		new_state.folder = g_curr_dir;
		new_state.file_name = item;
		all_state.emplace_back(std::move(new_state));
	}
}

// 自动生成代码
void AutoGenCode(const std::string& xlsx_path,const std::string& config_path,const std::string& code_path)
{
	g_xlsx_path = xlsx_path;

	std::vector<stGenState> all_state;
	std::vector<stGenState> completed_state;
	std::vector<std::string> all_folder;
	
	// 取出全部目录
	{
		std::vector<std::string> dirs;
		std::queue<std::string> temp_folder;
		std::string parent_dir = "";
		all_folder.push_back("");
		temp_folder.push("");

		while (!temp_folder.empty())
		{
			parent_dir = temp_folder.front();
			temp_folder.pop();
			dirs = DiscoverAllFolder(xlsx_path + parent_dir + "*");
			for (auto& item : dirs)
			{
				all_folder.push_back(parent_dir + item + "/");
				temp_folder.push(parent_dir + item + "/");
			}
		}
	}

	// 取出全部xlsx文件
	{
		for (auto& item : all_folder)
		{
			g_curr_dir = item;
			AppendGenState(all_state);
		}
	}


	// 开始生成代码
	{
		for (auto& item : all_state)
		{
			xlnt::workbook wb;
			if (std::strcmp(item.file_name.substr(0,7).c_str(), "Config_") == 0)
			{
				try {
					printf("gen %s%s%s\r\n", xlsx_path.c_str(), item.folder.c_str(), item.file_name.c_str());
					GetWorkBook(wb, xlsx_path + item.folder + item.file_name);
					XlsxToCpp(
						wb,
						code_path + item.folder + GetXlsxFileName(item.file_name) + ".h",
						GetXlsxFileName(item.file_name));
					XlsxToJson(wb, config_path + item.folder + GetXlsxFileName(item.file_name) + ".json");
					completed_state.push_back(item);
				}
				catch (std::exception& e)
				{
					printf("[error]:%s\r\n", e.what());
				}
			}
		}
	}

	GenInitCpp(completed_state, code_path);

}





int main(int argc, char* argv[])
{

	std::string _FilePath;
	std::string _FileSave;
	ECastType	_CastType = ECastType::XLSX_TO_JSON;

	// 生成cpp
	bool		gen_cpp = false;
	std::string cpp_path;
	std::string class_name;

// 	_FilePath = "./Config_SocketItemOption.xlsx";
// 	_FileSave = "./Config_SocketItemOption.json";
// 	cpp_path = "./code/Config_SocketItemOption.h";
// 	class_name = "Config_SocketItemOption";
	
	for (int i = 0; i < argc; ++i)
	{
		if (i == 1)
		{
			_FilePath = argv[i];
			continue;
		}


		std::string _str = argv[i];
		size_t _pos = _str.find("=");
		if (_pos == -1)
			continue;
		if (_str.substr(2, _pos - 2) == "out_type")
		{
			std::string type = _str.substr(_pos + 1, _str.size() - _pos - 1);
			if (std::strcmp(type.c_str(), "auto_gen_cpp") == 0)
			{
				_CastType = ECastType::XLSX_AUTO_GEN_CPP;
			}
			else if (std::strcmp(type.c_str(), "json") == 0)
			{
				_CastType = ECastType::XLSX_TO_JSON;
			}
		}
		else if (_str.substr(2, _pos - 2) == "json_out")
		{
			_FileSave = _str.substr(_pos + 1, _str.size() - _pos - 1);
		}
		else if (_str.substr(2, _pos - 2) == "cpp_out")
		{
			cpp_path = _str.substr(_pos + 1, _str.size() - _pos - 1);
			gen_cpp = true;
		}
		else if (_str.substr(2, _pos - 2) == "class_name")
		{
			class_name = _str.substr(_pos + 1, _str.size() - _pos - 1);
		}
		else if (_str.substr(2, _pos - 2) == "read_conf_path")
		{
			g_read_config_path = _str.substr(_pos + 1, _str.size() - _pos - 1);
		}
		else if (_str.substr(2, _pos - 2) == "export_type")
		{
			g_export_type = _str.substr(_pos + 1, _str.size() - _pos - 1);
		}
	}


	switch (_CastType)
	{
	case ECastType::XLSX_TO_JSON:
	{
		xlnt::workbook wb;
		GetWorkBook(wb, _FilePath);
		XlsxToJson(wb, _FileSave);
		if (gen_cpp)XlsxToCpp(wb, cpp_path, class_name);
	}
		break;
	case ECastType::XLSX_AUTO_GEN_CPP:
		try {

			AutoGenCode(_FilePath, _FileSave, cpp_path);
		}
		catch (std::exception & e)
		{
			printf("[error]:%s\r\n", e.what());
		}
		break;
	default:
		std::cout << "Unknown command" << std::endl;
		break;
	}

	return 0;
}