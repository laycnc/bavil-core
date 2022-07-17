#include "core/bavil_system_manager.h"

namespace bavil::core
{

	system_manager::system_manager() noexcept
	{
		s_instance = this;
	}

	system_manager::~system_manager() noexcept
	{
		s_instance = nullptr;
	}

	system_manager& system_manager::Get()
	{
		return *s_instance;
	}


	void system_manager::finalize()
	{
		for (auto& [id, system] : system_maps)
		{
			system->finalize();
			delete system;
		}

		system_maps.clear();
	}


	size_t system_manager::GetneratedSystemIdInternal()
	{
		static size_t s_id = 0;
		s_id++;
		return s_id;
	}


}  // namespace bavil::core
