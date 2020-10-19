#include "math/gt_vector3.h"
#include "math/gt_matrix33.h"
#include "math/gt_matrix44.h"

namespace gt::math
{

	namespace
	{
		constexpr Vector3 vector3_zero =
		{
			0.f,
			0.f,
			0.f
		};

		constexpr Vector3 vector3_one =
		{
			1.f,
			1.f,
			1.f
		};

		constexpr Vector3 vector3_unit_x =
		{
			1.f,
			0.f,
			0.f
		};

		constexpr Vector3 vector3_unit_y =
		{
			0.f,
			1.f,
			0.f
		};

		constexpr Vector3 vector3_unit_z =
		{
			0.f,
			0.f,
			1.f
		};

	} //! namespace 


	/// <summary>
	/// 全ての要素がゼロに設定された2次元ベクトル.
	/// </summary>
	const Vector3 Vector3::ZERO = vector3_zero;
	/// <summary>
	/// 全ての要素が1に設定された2次元ベクトル.
	/// </summary>
	const Vector3 Vector3::ONE = vector3_one;
	/// <summary>
	/// X軸のみ1に設定された2次元ベクトル.
	/// </summary>
	const Vector3 Vector3::UNIT_X = vector3_unit_x;
	/// <summary>
	/// Y軸のみ1に設定された2次元ベクトル.
	/// </summary>
	const Vector3 Vector3::UNIT_Y = vector3_unit_y;
	/// <summary>
	/// Z軸のみ1に設定された2次元ベクトル.
	/// </summary>
	const Vector3 Vector3::UNIT_Z = vector3_unit_z;

	Vector3 Vector3::Transform(const Vector3& v, const Matrix44& M)
	{
		return
		{
			v.x * M.m[0][0] + v.y * M.m[1][0] + v.z * M.m[2][0] + M.m[3][0],
			v.x * M.m[0][1] + v.y * M.m[1][1] + v.z * M.m[2][1] + M.m[3][1],
			v.x * M.m[0][2] + v.y * M.m[1][2] + v.z * M.m[2][2] + M.m[3][2]
		};
	}

	Vector3 Vector3::TransformCoord(const Vector3& v, const Matrix44& M)
	{
		return Vector3
		{
			v.x * M.m[0][0] + v.y * M.m[1][0] + v.z * M.m[2][0] + M.m[3][0],
			v.x * M.m[0][1] + v.y * M.m[1][1] + v.z * M.m[2][1] + M.m[3][1],
			v.x * M.m[0][2] + v.y * M.m[1][2] + v.z * M.m[2][2] + M.m[3][2]
		} /= v.x * M.m[0][3] + v.y * M.m[1][3] + v.z * M.m[2][3] + M.m[3][3];
	}

	Vector3 Vector3::TransformNormal(const Vector3& v, const Matrix44& M)
	{
		return
		{
			v.x * M.m[0][0] + v.y * M.m[1][0] + v.z * M.m[2][0],
			v.x * M.m[0][1] + v.y * M.m[1][1] + v.z * M.m[2][1],
			v.x * M.m[0][2] + v.y * M.m[1][2] + v.z * M.m[2][2]
		};
	}

	Vector3 operator * (const Matrix33& M, const Vector3& v) noexcept
	{
		return
		{
			v.x * M.m[0][0] + v.y * M.m[0][1] + v.z * M.m[0][2],
			v.x * M.m[1][0] + v.y * M.m[1][1] + v.z * M.m[1][2],
			v.x * M.m[2][0] + v.y * M.m[2][1] + v.z * M.m[2][2]
		};
	}

	Vector3 Vector3::operator * (const Matrix33& M) const noexcept
	{
		return
		{
			this->x * M.m[0][0] + this->y * M.m[1][0] + this->z * M.m[2][0],
			this->x * M.m[0][1] + this->y * M.m[1][1] + this->z * M.m[2][1],
			this->x * M.m[0][2] + this->y * M.m[1][2] + this->z * M.m[2][2]
		};
	}

}
