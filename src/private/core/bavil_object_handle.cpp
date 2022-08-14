#include "core/bavil_object_handle.h"

#include "core/bavil_object_system.h"

namespace bavil
{

	ObjectHandleBase::ObjectHandleBase(const ObjectHandleBase& _other)
	    : m_index(_other.m_index)
	{
		construct();
	}
	void ObjectHandleBase::operator=(const ObjectHandleBase& _other)
	{
		destruct();
		m_index = _other.m_index;
		construct();
	}

	ObjectBase* ObjectHandleBase::get_object_internal() const
	{
		// オブジェクトシステム経由でオブジェクトを取得する
		auto& object_system = ObjectSystem::Get();
		return object_system.get_object_internal(*this);
	}

	void ObjectHandleBase::construct()
	{
		if ( is_valid() )
		{
		}
	}

	void ObjectHandleBase::destruct()
	{
		m_index = -1;
	}

} // namespace bavil
