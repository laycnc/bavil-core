#pragma once

#include <cmath>
#include "bavil_type.h"
#include "math/bavil_quaternion.h"

namespace bavil::math::details
{

	template<class T>
		requires(std::is_floating_point_v<T>)
	struct Rotator
	{
		using SelfType  = Rotator<T>;
		using ValueType = T;

		ValueType pitch;
		ValueType yaw;
		ValueType roll;

		/**
		 * @brief コンストラクタ
		*/
		constexpr Rotator() noexcept
		    : pitch()
		    , yaw()
		    , roll()
		{
		}

		/**
		 * @brief コンストラクタ
		 * @param pitch_ X軸周りの回転量.
		 * @param yaw_   Y軸周りの回転量.
		 * @param roll_  Z軸周りの回転量.
		 * @return 
		*/
		constexpr Rotator(ValueType pitch_, ValueType yaw_, ValueType roll_) noexcept
		    : pitch(pitch_)
		    , yaw(yaw_)
		    , roll(roll_)
		{
		}

		SelfType& identity() noexcept
		{
			pitch = yaw = roll = static_cast<ValueType>(0.0);
			return *this;
		}
	};

} // namespace bavil::math::details

namespace bavil::math
{

	using Rotator = bavil::math::details::Rotator<f32>;

	extern bavil::math::Quaternion ToQuaternion(Rotator _rotator);

} // namespace bavil::math
