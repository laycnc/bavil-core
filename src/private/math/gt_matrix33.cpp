#include "math/gt_matrix33.h"
#include "math/gt_matrix44.h"
#include "math/gt_quaternion.h"

namespace gt::math
{
	namespace
	{

		static constexpr f32 matrix33_identity[] =
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};

		static constexpr f32 matrix33_empty[] =
		{
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f
		};

	} //! namespace 


	/// <summary>
	/// 単位行列.
	/// </summary>
	const Matrix33& Matrix33::IDENTITY = *reinterpret_cast<const Matrix33*>(matrix33_identity);

	/// <summary>
	/// 全てがゼロで初期化された行列.
	/// </summary>
	const Matrix33& Matrix33::EMPTY = *reinterpret_cast<const Matrix33*>(matrix33_empty);

	Matrix33 Matrix33::Rotate(Matrix44 const& mat)
	{
		return
		{
			mat.m[0][0], mat.m[0][1], mat.m[0][2],
			mat.m[1][0], mat.m[1][1], mat.m[1][2],
			mat.m[2][0], mat.m[2][1], mat.m[2][2]
		};
	}

	Matrix33 Matrix33::Rotate(const Quaternion& q)
	{
		value_type xx = q.x * q.x * 2.0f;
		value_type yy = q.y * q.y * 2.0f;
		value_type zz = q.z * q.z * 2.0f;
		value_type xy = q.x * q.y * 2.0f;
		value_type xz = q.x * q.z * 2.0f;
		value_type yz = q.y * q.z * 2.0f;
		value_type wx = q.w * q.x * 2.0f;
		value_type wy = q.w * q.y * 2.0f;
		value_type wz = q.w * q.z * 2.0f;

		return
		{
			1.f - (yy + zz), xy + wz, xz - wy,
			xy - wz, 1.f - (xx + zz), yz + wx,
			xz + wy, yz - wx, 1.f - (xx + yy)
		};
	}

}
