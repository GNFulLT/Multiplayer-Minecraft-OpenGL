#pragma once

#include <map>
#include <unordered_map>
#include <typeindex>
#include <any>
#include <memory>
#include <functional>
#include <format>

#ifndef DEBUG_NEW_MC
#define DEBUG_NEW_MC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

namespace GNF::Common::IoC
{
	class Container
	{
		public:
			inline static Container* GetInstance()
			{
				return g_instance.get();
			}

			inline static Container* Build()
			{
				g_instance.reset(new Container());
				return g_instance.get();

			}

			template<class T>
			Container* RegisterSingleton(std::function<std::shared_ptr<T>()> generatorMethod)
			{
				std::shared_ptr<T> generated = generatorMethod();

				m_container[typeid(T)] = std::make_pair(true,generated);
				return g_instance.get();
			}

			template<class T>
			Container* RegisterScoped(std::function<std::shared_ptr<T>()> generatorMethod)
			{
				m_container[typeid(T)] = std::make_pair(false,generatorMethod);
				return g_instance.get();
			}

			template<class T>
			std::shared_ptr<T> Resolve()
			{
				//!: Type Founded in container
				if (const auto i = m_container.find(typeid(T)); i != m_container.end())
				{
					//!: Check If desired variable is singleton
					if (i->second.first)
					{
						//!: Variable is singleton so second value is a shared_ptr
						return std::any_cast<std::shared_ptr<T>>(i->second.second);
					}
					else
					{
						//!: Variable is not singleton so second value is a method
						return std::any_cast<std::function<std::shared_ptr<T>()>>(i->second.second)();
					}
				}	
				else
				{
					throw std::runtime_error{ std::format("Could not find factory method for type [{}] in container",typeid(T).name()) };
				}
			}
			~Container() {
				int a = 5;
			}
		private:
			Container() = default;
			
		private:
			//!: Bool Value Checks it is singleton or scoped
			std::unordered_map<std::type_index, std::pair<bool, std::any>> m_container;
		private:
			inline static std::unique_ptr<Container> g_instance;
	};
}