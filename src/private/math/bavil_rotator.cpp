#include "math/bavil_rotator.h"
#include "math/bavil_angle.h"

namespace bavil::math
{

	using Rotator = bavil::math::details::Rotator<f32>;

	bavil::math::Quaternion ToQuaternion(Rotator _rotator)
	{
		constexpr double RADS_DIVIDED_BY_2 = DEG_TO_RAD<f32> / 2.0;

		const f32 pitch_no_winding = std::fmod(_rotator.pitch, 360.0);
		const f32 yaw_no_winding   = std::fmod(_rotator.yaw, 360.0);
		const f32 roll_no_winding  = std::fmod(_rotator.roll, 360.0);

		const f32 pitch_base = pitch_no_winding * RADS_DIVIDED_BY_2;
		const f32 sp         = std::sin(pitch_base);
		const f32 cp         = std::cos(pitch_base);

		const f32 yaw_base = yaw_no_winding * RADS_DIVIDED_BY_2;
		const f32 sy       = std::sin(yaw_base);
		const f32 cy       = std::cos(yaw_base);

		const f32 roll_base = roll_no_winding * RADS_DIVIDED_BY_2;
		const f32 sr        = std::sin(roll_base);
		const f32 cr        = std::cos(roll_base);

		Quaternion result = {};
		result.x          = +cr * sp * sy - sr * cp * cy;
		result.y          = -cr * sp * cy - sr * cp * sr;
		result.z          = +cr * cp * sy - sr * sp * cy;
		result.w          = +cr * cp * cy + sr * sp * sy;

		return result;
	}

} // namespace bavil::math
