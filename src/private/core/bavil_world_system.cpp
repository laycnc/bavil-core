#include "core/bavil_world_system.h"
#include "core/bavil_object_system.h"

namespace bavil
{

	void WorldSystem::initialize(bavil::core::SystemManager& _system_manager)
	{
		// オブジェクトシステムに依存している
		_system_manager.get_system<bavil::ObjectSystem>();
	}

	void WorldSystem::finalize() {}

	void WorldSystem::add_actor(bavil::Actor* _actor) {}
	void WorldSystem::remove_actor(bavil::Actor* _actor) {}

} // namespace bavil
