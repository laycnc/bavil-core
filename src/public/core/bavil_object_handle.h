#pragma once

#include <cstdint>
#include <utility>

#include "core/bavil_object_base.h"

namespace bavil
{
	class ObjectBase;

	struct ObjectHandleBase
	{
		friend class ObjectSystem;

	public:
		~ObjectHandleBase();
		constexpr ObjectHandleBase() noexcept
		    : m_index(-1)
		{
		}
		ObjectHandleBase(const ObjectHandleBase& _other);
		void operator=(const ObjectHandleBase& _other);
		constexpr ObjectHandleBase(ObjectHandleBase&& _other) noexcept
		    : m_index(std::exchange(_other.m_index, -1))
		{
		}
		void operator=(ObjectHandleBase&& _other) noexcept
		{
			// 事前に前のフラグを開放しておく
			object_reference_decrement();
			m_index = std::exchange(_other.m_index, -1);
		}
		constexpr bool is_valid() const noexcept
		{
			return m_index != -1;
		}

	protected:
		ObjectHandleBase(int64_t _index) noexcept;
		ObjectBase* get_object_internal() const;
		void        object_reference_increment();
		void        object_reference_decrement();

	protected:
		int64_t m_index;
	};

	template<ObjectConcepts T>
	struct ObjectHandle : public ObjectHandleBase
	{
	public:
		T* get_object() const
		{
			return static_cast<T*>(get_object_internal());
		}

		T* operator->() const
		{
			return get_object();
		}

		constexpr ObjectHandle() noexcept
		    : ObjectHandleBase()
		{
		}

		constexpr ObjectHandle(ObjectHandleBase&& _other) noexcept
		    : ObjectHandleBase(std::move(_other))
		{
		}

		void operator=(ObjectHandleBase&& _other) noexcept
		{
			// 事前に前のフラグを開放しておく
			object_reference_decrement();
			m_index = std::exchange(_other.m_index, -1);
		}
	};

} // namespace bavil
