#pragma once

#include <core/bavil_multicast_delegate.h>

#include <array>
#include <concepts>

#include "core/bavil_system_manager.h"
#include "core/bavil_object_base.h"
#include "core/bavil_object_handle.h"

namespace bavil
{

	struct ObjectArrayItem
	{
		ObjectBase* ObjectPtr = nullptr;
	};

	class ObjectSystem : public bavil::core::SystemBase<ObjectSystem>
	{
	public:
		virtual void initialize(
		    bavil::core::SystemManager& _system_manager) override;

		virtual void finalize() override;

		template<ObjectConcepts T>
		[[nodiscard]] ObjectHandle<T> create_object()
		{
			int32_t free_index = generated_free_index();
			T*      new_obj    = new T();

			return create_object_internal(free_index, new_obj);
		}

		[[nodiscard]] ObjectBase* get_object_internal(
		    ObjectHandleBase _handle) const;

	private:
		ObjectHandleBase create_object_internal(int32_t     _free_index,
		                                        ObjectBase* new_object);
		int32_t          generated_free_index();

	private:
		std::array<ObjectArrayItem, 1024> m_objects;
		size_t                            m_free_index = 0;
	};

} // namespace bavil
