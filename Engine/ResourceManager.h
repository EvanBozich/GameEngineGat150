#pragma once
#include "Resource.h"
#include <map>
#include <string>
#include "Singleton.h"
#include <iostream>



namespace nu
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:

		template<typename T, typename ... Args>
		requires std::derived_from<T, Resource>
		res_t<T>Get(const std::string& name, Args&&...args);

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};


	template<typename T, typename ...Args>
	requires std::derived_from<T, Resource>
	inline res_t<T> ResourceManager::Get(const std::string& name, Args && ...args) 
	{
		auto iter = m_resources.find(name);
		if (iter != m_resources.end())
		{
			auto& base = iter->second;
			auto resource = std::dynamic_pointer_cast<T>(base);

			if (resource == nullptr)
			{
				std::cerr << "Type mismatch: " << name << std::endl;
				return res_t<T>();
			}

			return resource;
		}

		//resoucre doesn't exist, load

		res_t<T> resource = std::make_shared<T>();

		if (!resource->Load(name, std::forward<Args>(args)...))
		{
			std::cerr << "Couldn't load resource: " << name << std::endl;
			return res_t<T>();
		}

		m_resources[name] = resource;

		return resource;
	
	}

	inline ResourceManager& Resources() {return ResourceManager::Instance(); }
}