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
		// オブジェクトを示すポインタ
		ObjectBase* ObjectPtr = nullptr;
		// オブジェクトの参照数
		size_t ReferenceNum = 0;
	};

	class ObjectSystem : public bavil::core::SystemBase<ObjectSystem>
	{
	public:
		virtual void initialize(
		    bavil::core::SystemManager& _system_manager) override;

		virtual void finalize() override;

		/**
		 * @brief オブジェクトの総数を取得する
		 * @return 生成されたオブジェクト数を返す
		*/
		size_t get_object_num() const
		{
			return m_object_num;
		}

		template<ObjectConcepts T>
		[[nodiscard]] ObjectHandle<T> create_object()
		{
			int32_t free_index = generated_free_index();
			T*      new_obj    = new T();

			return create_object_internal(free_index, new_obj);
		}

		[[nodiscard]] ObjectBase* get_object_internal(
		    const ObjectHandleBase& _handle) const;
		[[nodiscard]] ObjectArrayItem* get_object_array_internal(
		    const ObjectHandleBase& _handle);
		[[nodiscard]] const ObjectArrayItem* get_object_array_internal(
		    const ObjectHandleBase& _handle) const;

		// オブジェクトの参照を加算する
		void object_reference_increment_internal(const ObjectHandleBase& _handle);
		// オブジェクトの参照を減算する
		void object_reference_decrement_internal(const ObjectHandleBase& _handle);

	private:
		ObjectHandleBase create_object_internal(int32_t     _free_index,
		                                        ObjectBase* new_object);
		int32_t          generated_free_index();

	private:
		std::array<ObjectArrayItem, 1024> m_objects;
		size_t                            m_free_index = 0;
		size_t                            m_object_num = 0;
	};

} // namespace bavil
