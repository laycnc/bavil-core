#include "math/bavil_matrix44.h"
#include "math/bavil_vector2.h"
#include "math/bavil_vector3.h"
#include "math/bavil_vector4.h"
#include "math/bavil_matrix33.h"
#include "math/bavil_quaternion.h"

namespace bavil::math
{
	static constexpr f32 MATRIX44_IDENTITY[] = {1.f,
	                                            0.f,
	                                            0.f,
	                                            0.0f,
	                                            0.f,
	                                            1.f,
	                                            0.f,
	                                            0.f,
	                                            0.f,
	                                            0.f,
	                                            1.f,
	                                            0.f,
	                                            0.f,
	                                            0.f,
	                                            0.f,
	                                            1.f};

	static constexpr f32 MATRIX44_EMPTY[] = {0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f,
	                                         0.f};

	/// <summary>
	/// 単位行列.
	/// </summary>
	const Matrix44 Matrix44::IDENTITY =
	    *reinterpret_cast<const Matrix44*>(MATRIX44_IDENTITY);

	/// <summary>
	/// 空行列.
	/// </summary>
	const Matrix44 Matrix44::EMPTY =
	    *reinterpret_cast<const Matrix44*>(MATRIX44_EMPTY);

	/// <summary>
	/// コンストラクタ.
	/// </summary>
	/// <param name="M">行列.</param>
	Matrix44::Matrix44(const Matrix33& M)
	    : Matrix44(M._11,
	               M._12,
	               M._13,
	               0.f,
	               M._21,
	               M._22,
	               M._23,
	               0.f,
	               M._31,
	               M._32,
	               M._33,
	               0.f,
	               0.f,
	               0.f,
	               0.f,
	               1.f)
	{
	}

	/// <summary>
	/// コンストラクタ.
	/// </summary>
	/// <param name="q">クォータニオン.</param>
	Matrix44::Matrix44(const Quaternion& q)
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

		this->m[0][0] = 1.0f - (yy + zz);
		this->m[0][1] = xy + wz;
		this->m[0][2] = xz - wy;
		this->m[0][3] = 0.0f;

		this->m[1][0] = xy - wz;
		this->m[1][1] = 1.0f - (xx + zz);
		this->m[1][2] = yz + wx;
		this->m[1][3] = 0.0f;

		this->m[2][0] = xz + wy;
		this->m[2][1] = yz - wx;
		this->_33     = 1.0f - (xx + yy);
		this->m[2][3] = 0.0f;

		this->m[3][0] = 0.0f;
		this->m[3][1] = 0.0f;
		this->m[3][2] = 0.0f;
		this->m[3][3] = 1.0f;
	}

#pragma endregion

	/// <summary>
	/// 逆行列を求める.
	/// <para>逆行列が存在しない時はそのままの行列を返す.</para>
	/// </summary>
	/// <returns>逆行列を返す.</returns>
	Matrix44::self_type Matrix44::get_inverse() const
	{
		value_type a0 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
		value_type a1 = m[0][0] * m[1][2] - m[0][2] * m[1][0];
		value_type a2 = m[0][0] * m[1][3] - m[0][3] * m[1][0];
		value_type a3 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
		value_type a4 = m[0][1] * m[1][3] - m[0][3] * m[1][1];
		value_type a5 = m[0][2] * m[1][3] - m[0][3] * m[1][2];
		value_type b0 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
		value_type b1 = m[2][0] * m[3][2] - _33 * m[3][0];
		value_type b2 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
		value_type b3 = m[2][1] * m[3][2] - _33 * m[3][1];
		value_type b4 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
		value_type b5 = _33 * m[3][3] - m[2][3] * m[3][2];

		const value_type det =
		    a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

		if ( det == 0.0f )
		{
			// 逆行列が存在しない.
			return *this;
		}
		value_type invDet = 1.0f / det;

		return {(m[1][1] * b5 - m[1][2] * b4 + m[1][3] * b3) * invDet,
		        (-m[0][1] * b5 + m[0][2] * b4 - m[0][3] * b3) * invDet,
		        (m[3][1] * a5 - m[3][2] * a4 + m[3][3] * a3) * invDet,
		        (-m[2][1] * a5 + _33 * a4 - m[2][3] * a3) * invDet,
		        (-m[1][0] * b5 + m[1][2] * b2 - m[1][3] * b1) * invDet,
		        (m[0][0] * b5 - m[0][2] * b2 + m[0][3] * b1) * invDet,
		        (-m[3][0] * a5 + m[3][2] * a2 - m[3][3] * a1) * invDet,
		        (m[2][0] * a5 - _33 * a2 + m[2][3] * a1) * invDet,
		        (m[1][0] * b4 - m[1][1] * b2 + m[1][3] * b0) * invDet,
		        (-m[0][0] * b4 + m[0][1] * b2 - m[0][3] * b0) * invDet,
		        (m[3][0] * a4 - m[3][1] * a2 + m[3][3] * a0) * invDet,
		        (-m[2][0] * a4 + m[2][1] * a2 - m[2][3] * a0) * invDet,
		        (-m[1][0] * b3 + m[1][1] * b1 - m[1][2] * b0) * invDet,
		        (m[0][0] * b3 - m[0][1] * b1 + m[0][2] * b0) * invDet,
		        (-m[3][0] * a3 + m[3][1] * a1 - m[3][2] * a0) * invDet,
		        (m[2][0] * a3 - m[2][1] * a1 + _33 * a0) * invDet};
	}

#pragma region SetterRotation

	/// <summary>
	/// 回転行列の設定.
	/// </summary>
	/// <param name="angle">角度.</param>
	/// <param name="axis">軸成分.</param>
	/// <returns>設定後の回転行列.</returns>
	Matrix44::self_type& Matrix44::set_rotation(Radian              angle,
	                                            const vector3_type& axis)
	{
		return this->set_rotation(quaternion_type{axis, angle});
	}

#pragma endregion

	/// <summary>
	/// 変換行列補間.
	/// </summary>
	/// <param name="start">開始行列.</param>
	/// <param name="end">終了行列.</param>
	/// <param name="amount">補完係数<para>.0.0(開始値)～1.0(終了値)</para>.</param>
	/// <returns>補間後の行列.</returns>
	Matrix44::self_type Matrix44::Slerp(const self_type& start,
	                                    const self_type& end,
	                                    value_type       amount)
	{
#if 1
		static_cast<void>(start);
		static_cast<void>(end);
		static_cast<void>(amount);
		return {};
#else
		// 拡大縮小の補間.
		Vector3 s = Vector3::Lerp(start.get_scale(), end.get_scale(), amount);

		// 回転の補間.
		Quaternion r = Quaternion::Slerp(Quaternion::Rotate(start).normalize(),
		                                 Quaternion::Rotate(end).normalize(),
		                                 amount);

		// 位置の補間.
		Vector3 p = Vector3::Lerp(start.get_position(), end.get_position(), amount);

		return Matrix44().set_scale(s) * r.rotate() * Matrix44().set_translate(p);
#endif
	}

} // namespace bavil::math

/********** End of File ******************************************************/
