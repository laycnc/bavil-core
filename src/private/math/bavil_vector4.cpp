#include "math/bavil_vector4.h"
#include "math/bavil_matrix44.h"

namespace bavil::math
{

	namespace
	{

		constexpr Vector4 VECTOR4_ZERO = {0.f, 0.f, 0.f, 0.f};

		constexpr Vector4 VECTOR4_ONE = {1.f, 1.f, 1.f, 1.f};

		constexpr Vector4 VECTOR4_UNIT_X = {1.f, 0.f, 0.f, 0.f};

		constexpr Vector4 VECTOR4_UNIT_Y = {0.0f, 1.0f, 0.0f, 0.0f};

		constexpr Vector4 VECTOR4_UNIT_Z = {0.0f, 0.0f, 1.0f, 0.0f};

		constexpr Vector4 VECTOR4_UNITW = {0.0f, 0.0f, 0.0f, 1.0f};

	} // namespace

	/// <summary>
	/// 全ての要素がゼロに設定された2次元ベクトル.
	/// </summary>
	const Vector4 Vector4::ZERO = VECTOR4_ZERO;
	/// <summary>
	/// 全ての要素が1に設定された2次元ベクトル.
	/// </summary>
	const Vector4 Vector4::ONE = VECTOR4_ONE;
	/// <summary>
	/// X軸のみ1に設定された2次元ベクトル.
	/// </summary>
	const Vector4 Vector4::UNIT_X = VECTOR4_UNIT_X;
	/// <summary>
	/// Y軸のみ1に設定された2次元ベクトル.
	/// </summary>
	const Vector4 Vector4::UNIT_Y = VECTOR4_UNIT_Y;
	/// <summary>
	/// Z軸のみ1に設定された2次元ベクトル.
	/// </summary>
	const Vector4 Vector4::UNIT_Z = VECTOR4_UNIT_Z;
	/// <summary>
	/// W軸のみ1に設定された2次元ベクトル.
	/// </summary>
	const Vector4 Vector4::UNIT_W = VECTOR4_UNITW;

	Vector4 Vector4::Transform(const Vector4& V, Matrix44 const& M) noexcept
	{
		return {
		    V.x * M.m[0][0] + V.y * M.m[1][0] + V.z * M.m[2][0] + V.w * M.m[3][0],
		    V.x * M.m[0][1] + V.y * M.m[1][1] + V.z * M.m[2][1] + V.w * M.m[3][1],
		    V.x * M.m[0][2] + V.y * M.m[1][2] + V.z * M.m[2][2] + V.w * M.m[3][2],
		    V.x * M.m[0][3] + V.y * M.m[1][3] + V.z * M.m[2][3] + V.w * M.m[3][3]};
	}

	Vector4 Vector4::TransformCoord(const Vector4& V, Matrix44 const& M)
	{
		Vector4 v;

		v.x = V.x * M.m[0][0] + V.y * M.m[1][0] + V.z * M.m[2][0] + V.w * M.m[3][0];
		v.y = V.x * M.m[0][1] + V.y * M.m[1][1] + V.z * M.m[2][1] + V.w * M.m[3][1];
		v.z = V.x * M.m[0][2] + V.y * M.m[1][2] + V.z * M.m[2][2] + V.w * M.m[3][2];
		v.w = V.x * M.m[0][3] + V.y * M.m[1][3] + V.z * M.m[2][3] + V.w * M.m[3][3];

		return v /= v.w;
	}

	Vector4 operator*(Matrix44 const& M, const Vector4& v)
	{
		const Matrix44::value_type x =
		    v.x * M.m[0][0] + v.y * M.m[1][0] + v.z * M.m[2][0] + v.w * M.m[3][0];
		const Matrix44::value_type y =
		    v.x * M.m[0][1] + v.y * M.m[1][1] + v.z * M.m[2][1] + v.w * M.m[3][1];
		const Matrix44::value_type z =
		    v.x * M.m[0][2] + v.y * M.m[1][2] + v.z * M.m[2][2] + v.w * M.m[3][2];
		const Matrix44::value_type w =
		    v.x * M.m[0][3] + v.y * M.m[1][3] + v.z * M.m[2][3] + v.w * M.m[3][3];

		return Vector4{x / w, y / w, z / w, w};
	}

	Vector4 Vector4::operator*(Matrix44 const& M) const
	{
		const value_type x = this->x * M.m[0][0] + this->y * M.m[0][1] +
		                     this->z * M.m[0][2] + this->w * M.m[0][3];
		const value_type y = this->x * M.m[1][0] + this->y * M.m[1][1] +
		                     this->z * M.m[1][2] + this->w * M.m[1][3];
		const value_type z = this->x * M.m[2][0] + this->y * M.m[2][1] +
		                     this->z * M.m[2][2] + this->w * M.m[2][3];
		const value_type w = this->x * M.m[3][0] + this->y * M.m[3][1] +
		                     this->z * M.m[3][2] + this->w * M.m[3][3];

		return Vector4{x / w, y / w, z / w, w};
	}

} // namespace bavil::math
