#pragma once

#include <cstddef>
#include <concepts>
#include <unordered_map>
#include "core/bavil_system.h"

namespace bavil::core
{

	class system_manager
	{
	public:
		system_manager() noexcept;
		~system_manager() noexcept;

		static system_manager& Get();

		template <system_concepts T>
		static T* GetSystem()
		{
			return Get().get_system<T>();
		}

		template <system_concepts T>
		T* get_system()
		{
			const size_t id = T::GetSystemId();

			auto result = system_maps.find(id);
			if (result != system_maps.end())
			{
				system_interface* result_system = result->second;
				return static_cast<T*>(result_system);
			}

			T* new_system = new T();

			system_maps.emplace(id, new_system);

			new_system->initialize(*this);

			return new_system;
		}

		void finalize();

		template <system_concepts T>
		static size_t GetneratedSystemId()
		{
			static size_t s_id = GetneratedSystemIdInternal();
			return s_id;
		}

	private:
		static size_t GetneratedSystemIdInternal();

	private:
		std::unordered_map<size_t, system_interface*> system_maps;

		// singleton
		static inline system_manager* s_instance;
	};

}  // namespace bavil::core
