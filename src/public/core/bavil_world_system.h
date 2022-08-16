#pragma once

#include <core/bavil_multicast_delegate.h>

#include <list>
#include "core/bavil_actor.h"
#include "core/bavil_system_manager.h"

namespace bavil
{

	class WorldSystem : public bavil::core::SystemBase<WorldSystem>
	{
	public:
		virtual void initialize(
		    bavil::core::SystemManager& _system_manager) override;

		virtual void finalize() override;

		void add_actor(bavil::Actor* _actor);
		void remove_actor(bavil::Actor* _actor);

	private:
		std::list<bavil::Actor*> actor_lists;
	};

} // namespace bavil
