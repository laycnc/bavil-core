#include "core/bavil_object_system.h"

//#include <optick.h>

bavil::ObjectArrayItem* __debug__bavil_object_array_top = nullptr;

namespace bavil
{

	void ObjectSystem::initialize(bavil::core::SystemManager& _system_manager)
	{
		//OPTICK_CATEGORY("ObjectSystem::initialize", Optick::Category::GameLogic);

		// 0クリアで初期化しておく
		std::memset(m_objects.data(), 0, m_objects.size() * sizeof(ObjectArrayItem));

		__debug__bavil_object_array_top = m_objects.data();
	}

	void ObjectSystem::finalize()
	{
		for ( ObjectArrayItem& item : m_objects )
		{
			if ( item.ObjectPtr )
			{
				delete item.ObjectPtr;
				item.ObjectPtr = nullptr;
			}
		}
	}

	[[nodiscard]] ObjectBase* ObjectSystem::get_object_internal(
	    ObjectHandleBase _handle) const
	{
		if ( !_handle.is_valid() )
		{
			return nullptr;
		}

		const int32_t index = _handle.m_index;
		if ( m_objects.size() > index )
		{
			const ObjectArrayItem& item = m_objects[index];
			return item.ObjectPtr;
		}
		return nullptr;
	}

	ObjectHandleBase ObjectSystem::create_object_internal(int32_t     _free_index,
	                                                      ObjectBase* new_object)
	{
		int32_t index  = _free_index;
		auto&   item   = m_objects[index];
		item.ObjectPtr = new_object;

		// 構築を行う
		new_object->construct();

		return ObjectHandleBase(index);
	}

	int32_t ObjectSystem::generated_free_index()
	{
		int32_t result = -1;

		// オブジェクトの配列から空いている配列を検索する
		while ( m_objects.size() > m_free_index )
		{
			ObjectArrayItem& item = m_objects[m_free_index];
			if ( item.ObjectPtr == nullptr )
			{
				result = m_free_index;
				m_free_index++;
				break;
			}
			m_free_index++;
		}

		return result;
	}

} // namespace bavil
