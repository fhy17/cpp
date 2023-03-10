#pragma once

#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <string>
#include <map>
#include <functional>
#include <memory>


class DllProxy {
public:
	DllProxy():DllProxy(""){
		
	}

	DllProxy(const std::string &dll_path): module_(nullptr){
		if(dll_path.size() > 0)
			load(dll_path);
	}

	~DllProxy() {
		unload();
	}
	
	bool load(const std::string &dll_path) {
		module_ = LoadLibraryA(dll_path.c_str());
		if (module_ == nullptr) {
			std::cout << "LoadLibrary " << dll_path << " failed" << std::endl;
			return false;
		}
		return true;
	}

	bool unload() {
		if (module_ == nullptr)
			return true;

		auto ret = FreeLibrary(module_);
		if (!ret)
			return false;

		module_ = nullptr;
		return true;
	}
	
	template<typename T>
	std::function<T> getFunc(const std::string &func_name) {
		auto it = func_.find(func_name);
		if (it == func_.end()) {
			auto addr = GetProcAddress(module_, func_name.c_str());
			if (!addr)
				return nullptr;
			func_.insert(std::make_pair(func_name, addr));
			it = func_.find(func_name);
		}

		return std::function<T>((T*)(it->second));
	}

	template<typename T, typename... Args>
	typename std::result_of<std::function<T>(Args...)>::type excecuteFunc(const std::string &func_name, Args&&... args) {
		auto func = getFunc<T>(func_name);
		if (func == nullptr) {
			std::string err = "can not find this function " + func_name;
			throw std::exception(err.c_str());
		}

		return func(std::forward<Args>(args)...);
	}

private:
	HMODULE module_;
	std::map<std::string, FARPROC> func_;
};

typedef std::shared_ptr<DllProxy> DllProxyPtr;
