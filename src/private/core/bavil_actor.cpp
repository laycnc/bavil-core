#include "core/bavil_actor.h"
#include "core/bavil_world_system.h"

namespace bavil
{
	void Transform::recash() noexcept
	{
		if ( m_is_recash_request )
		{
			m_cash_matrix = math::Matrix44::Scaling(m_scale);
			m_cash_matrix *= math::Matrix44(math::ToQuaternion(m_rotation));
			m_cash_matrix *= math::Matrix44::Translate(m_position);
		}
		m_is_recash_request = false;
	}

	/**
	 * @brief オブジェクトの構築時に呼ばれる
	 */
	void Actor::construct()
	{
		SuperType::construct();

		WorldSystem::Get().add_actor(this);
	}

	/**
	 * @brief オブジェクトの削除時に呼ばれる
	 */
	void Actor::destruct()
	{
		SuperType::destruct();

		WorldSystem::Get().remove_actor(this);
	}

} // namespace bavil
