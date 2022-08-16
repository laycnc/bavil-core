#pragma once

#include "core/bavil_object_base.h"
#include "math/bavil_vector3.h"
#include "math/bavil_rotator.h"
#include "math/bavil_matrix44.h"

namespace bavil
{

	class Transform
	{
	public:
		const bavil::math::Matrix44& get_matrix() const noexcept
		{
			return m_cash_matrix;
		}

		bavil::math::Vector3 get_position() const noexcept
		{
			return m_position;
		}
		bavil::math::Rotator get_rotation() const noexcept
		{
			return m_rotation;
		}
		bavil::math::Vector3 get_scale() const noexcept
		{
			return m_scale;
		}

		void set_position(bavil::math::Vector3 _position) noexcept
		{
			m_position = _position;
			recash();
		}
		void get_rotation(bavil::math::Rotator _rotation) noexcept
		{
			m_rotation = _rotation;
			recash();
		}
		void set_scale(bavil::math::Vector3 _scale) noexcept
		{
			m_scale = _scale;
			recash();
		}

	private:
		void recash() noexcept;

	private:
		bavil::math::Vector3  m_position;
		bavil::math::Rotator  m_rotation;
		bavil::math::Vector3  m_scale;
		bavil::math::Matrix44 m_cash_matrix;
		bool                  m_is_recash_request = false;
	};

	class Actor : public ObjectBase
	{
	public:
		using SuperType = ObjectBase;

		Actor() {}

		/**
		 * @brief オブジェクトの構築時に呼ばれる
		 */
		virtual void construct() override;
		/**
		 * @brief オブジェクトの削除時に呼ばれる
		 */
		virtual void destruct() override;

		Transform& get_transform() noexcept
		{
			return m_transform;
		}

		const Transform& get_transform() const noexcept
		{
			return m_transform;
		}

	protected:
		Transform m_transform;
	};

	template<class T> concept ActorConcepts = requires(T obj)
	{
		std::derived_from<T, Actor>;
	};

} // namespace bavil
