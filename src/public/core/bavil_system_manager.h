#pragma once

#include <cstddef>
#include <concepts>
#include <unordered_map>
#include "core/bavil_system.h"

namespace bavil::core
{

	class SystemManager
	{
	public:
		SystemManager() noexcept;
		~SystemManager() noexcept;

		static SystemManager& Get();

		template<SystemConcepts T>
		static T* GetSystem()
		{
			return Get().get_system<T>();
		}

		template<SystemConcepts T>
		T* get_system()
		{
			const size_t id = T::GetSystemId();

			auto result = system_maps.find(id);
			if ( result != system_maps.end() )
			{
				SystemInterface* result_system = result->second;
				return static_cast<T*>(result_system);
			}

			T* new_system = new T();

			system_maps.emplace(id, new_system);

			new_system->initialize(*this);

			return new_system;
		}

		void finalize();

		template<SystemConcepts T>
		static size_t GetneratedSystemId()
		{
			static size_t s_id = GetneratedSystemIdInternal();
			return s_id;
		}

	private:
		static size_t GetneratedSystemIdInternal();

	private:
		std::unordered_map<size_t, SystemInterface*> system_maps;

		// singleton
		static inline SystemManager* m_instance;
	};

	/**
	 * システム基底クラス
	 * @tparam Derive システムクラス
	 */
	template<class Derive>
	class SystemBase : public SystemInterface
	{
	public:
		virtual ~SystemBase() {}

		static Derive& Get()
		{
			return *SystemManager::GetSystem<Derive>();
		}

		virtual size_t get_system_id() const override final
		{
			return Derive::GetSystemId();
		}

		static size_t GetSystemId()
		{
			return SystemManager::GetneratedSystemId<Derive>();
		}
	};

} // namespace bavil::core
