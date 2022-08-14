#include "core/bavil_object_handle.h"

#include "core/bavil_object_system.h"

namespace bavil
{

	ObjectHandleBase ::~ObjectHandleBase()
	{
		object_reference_decrement();
	}

	ObjectHandleBase::ObjectHandleBase(int64_t _index) noexcept
	    : m_index(_index)
	{
		object_reference_increment();
	}

	ObjectHandleBase::ObjectHandleBase(const ObjectHandleBase& _other)
	    : m_index(_other.m_index)
	{
		object_reference_increment();
	}
	void ObjectHandleBase::operator=(const ObjectHandleBase& _other)
	{
		object_reference_decrement();
		m_index = _other.m_index;
		object_reference_increment();
	}

	ObjectBase* ObjectHandleBase::get_object_internal() const
	{
		// オブジェクトシステム経由でオブジェクトを取得する
		auto& object_system = ObjectSystem::Get();
		return object_system.get_object_internal(*this);
	}

	void ObjectHandleBase::object_reference_increment()
	{
		// オブジェクトシステム経由でオブジェクトを取得する
		auto& object_system = ObjectSystem::Get();
		object_system.object_reference_increment_internal(*this);
	}

	void ObjectHandleBase::object_reference_decrement()
	{
		// IDが有効か確認する
		if ( is_valid() )
		{
			// オブジェクトシステム経由でオブジェクトを取得する
			auto& object_system = ObjectSystem::Get();
			object_system.object_reference_decrement_internal(*this);
			m_index = -1;
		}
	}

} // namespace bavil
