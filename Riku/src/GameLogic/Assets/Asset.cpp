//
// Created by kamil-hp on 15.10.2021.
//

#include "Asset.h"

#include <memory>
#include <filesystem>
#include <fstream>
#include <hash-library/sha256.h>

namespace logic {

	std::map<std::string, AssetData> getData(const sol::table& table) {
		std::map<std::string, AssetData> data;
		for (const std::pair<sol::object, sol::object>& v : table) {
			std::string key = v.first.as<std::string>();
			auto& value = v.second;
			switch (value.get_type()) {
			case sol::type::nil:
			case sol::type::none:
				data[key] = AssetData();
				break;
			case sol::type::boolean:
				data[key] = value.as<bool>();
				break;
			case sol::type::string:
				data[key] = value.as<std::string>();
				break;
			case sol::type::number:
				data[key] = value.as<double>();
				break;
			case sol::type::table: {
				auto readTable = getData(value.as<sol::table>());
				data[key] = std::map<std::string, AssetData>();
				for (const auto& v : readTable) {
					data[key][v.first] = v.second;
				}
			}
				break;
			case sol::type::lightuserdata:
			case sol::type::userdata:
				std::cout << "User data is not allowed here.\n";
				break;
				//ignored data types:
			case sol::type::function:
			case sol::type::thread:
			case sol::type::poly:
				break;
			}
		}
		return data;
	}

	void Asset::load(const std::string& path, const std::string& fileName) {
		this->path = path;
		//load file and calculate hash
		std::ifstream file(path + "/" + fileName);
		std::string fileContent(std::istreambuf_iterator<char>{file}, {});
		SHA256 sha;
		hash = sha(fileContent);
		file.close();
		//init lua
		lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::io);

		lua.load(fileContent);
		lua.script_file(path + "/" + fileName);

		type = lua["asset_type"];
		//get name from file
		sol::optional<std::string> pn = lua["name"];
		if (pn.has_value())
			name = *pn;
		else
			name = type;
		//get parent name from file
		sol::optional<std::string> op = lua["parent"];
		if (op.has_value())
			parent_name = *op;
		else if (name != type)
			parent_name = type; //direct child of asset type object
		else if (name != "root")
			parent_name = "root"; //it is root of asset type
		else
			parent_name = ""; //it is root
		//get is abstract name from file
		sol::optional<bool> ab = lua["is_abstract"];
		if (ab.has_value())
			abstract = *ab;
		else {
			abstract = (name == type) || (name == "root");
		}
		sol::table parameterTable = lua[type];
		data = getData(parameterTable);
		//load functions
		for (const auto& v : lua) {
			auto key = v.first.as<std::string>();
			if (v.second.get_type() == sol::type::function) {
				//it is a function
				functions[key] = v.second.as<sol::function>();
			}
		}
	}


	Asset& Asset::operator=(Asset&& other) noexcept {
		this->name = other.name;
		this->parent_name = other.parent_name;
		this->type = other.type;
		this->abstract = other.abstract;
		this->data = std::move(other.data);
		return *this;
	}

	void Asset::updateFromParent(const Asset& parent) {
		for (const auto& d : parent.data) {
			auto& key = d.first;
			auto& value = d.second;
			if (data.find(key) == data.end()) {
				//key is not in data yet
				data[key] = value;
			}
		}
		for (const auto& f : parent.functions) {
			const std::string& key = f.first;
			auto& value = f.second;
			if (functions.find(key) == functions.end()) {
				//key is not in data yet
				functions[key] = value;
			}
			else {
				//using parent function as "_{parent_name}_{function_name}
				if (key[0] == '_') //already derived function
					functions[key] = value;
				else
					functions["_" + parent_name + "_" + key] = value;
			}
		}
	}
}