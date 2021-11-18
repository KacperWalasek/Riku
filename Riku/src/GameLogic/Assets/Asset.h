//
// Created by kamil-hp on 15.10.2021.
//
#pragma once

#include <map>
#include <variant>
#include <any>
#include <optional>
#include <vector>
#include <string>
#include "sol/sol.hpp"
#include "AssetData.h"

namespace logic {
	class Asset {
		std::shared_ptr<sol::state> lua;
		std::string name;
		std::string parent_name;
		std::string type;
		std::string path;
		std::string hash;
		bool abstract=false;
		void updateFromParent(const Asset& parent);
		std::map<std::string, AssetData> data;
		std::map<std::string, sol::function> functions;
		friend class AssetHandler;
	public:
		Asset(const std::string& path, const std::string& fileName) { load(path, fileName);}
		Asset(const Asset& asset);
		Asset()=default;
		Asset& operator=(Asset&& other) noexcept;
		void load(const std::string& path, const std::string& fileName);
		[[nodiscard]] const std::string& getName() const {return name;}
		[[nodiscard]] const std::string& getType() const {return type;}
		[[nodiscard]] const std::string& getPath() const {return path;}
		[[nodiscard]] bool isAbstract() const {return abstract;}

		[[nodiscard]] bool hasData(const std::string& key) const {return data.find(key)!=data.end();}
		[[nodiscard]] const std::map<std::string, AssetData>& getMap() const {return data;}
		[[nodiscard]] const AssetData& getByKey(const std::string& key) const {
			if (!hasData(key))
				throw std::out_of_range("No value with key: " + key);
			return data.at(key);
		}

		bool hasFunction(const std::string& key) {return functions.find(key)!=functions.end();}
		[[nodiscard]] const std::map<std::string, sol::function>& getFunctions() {return functions;}
		sol::function& getFunction(const std::string& key) {return functions[key];}
		[[nodiscard]] const sol::function& getFunction(const std::string& key) const {return functions.at(key);}
		const std::string& getHash() const {return hash;}
	};
}