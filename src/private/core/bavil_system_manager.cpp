#include "core/bavil_system_manager.h"

namespace bavil::core
{

	SystemManager::SystemManager() noexcept
	{
		m_instance = this;
	}

	SystemManager::~SystemManager() noexcept
	{
		m_instance = nullptr;
	}

	SystemManager& SystemManager::Get()
	{
		return *m_instance;
	}

	void SystemManager::finalize()
	{
		for ( auto& [id, system] : system_maps )
		{
			system->finalize();
			delete system;
		}

		system_maps.clear();
	}

	size_t SystemManager::GetneratedSystemIdInternal()
	{
		static size_t s_id = 0;
		s_id++;
		return s_id;
	}

} // namespace bavil::core
