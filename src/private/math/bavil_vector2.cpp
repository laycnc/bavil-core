#include "math/bavil_vector2.h"
#include "math/bavil_matrix33.h"
#include "math/bavil_matrix44.h"

namespace bavil::math
{

	namespace
	{

		constexpr Vector2 VECTOR2_ZERO = {0.f, 0.f};

		constexpr Vector2 VECTOR2_ONE = {1.f, 1.f};

		constexpr Vector2 VECTOR2_UNIT_X = {1.f, 0.f};

		constexpr Vector2 VECTOR2_UNIT_Y = {0.f, 1.f};

	} // namespace

	/// <summary>
	/// 全ての要素がゼロに設定された2次元ベクトル.
	/// </summary>
	const Vector2 Vector2::ZERO = VECTOR2_ZERO;

	/// <summary>
	/// 全ての要素が1に設定された2次元ベクトル.
	/// </summary>
	const Vector2 Vector2::ONE = VECTOR2_ONE;

	/// <summary>
	/// X軸のみ1に設定された2次元ベクトル.
	/// </summary>
	const Vector2 Vector2::UNIT_X = VECTOR2_UNIT_X;

	/// <summary>
	/// Y軸のみ1に設定された2次元ベクトル.
	/// </summary>
	const Vector2 Vector2::UNIT_Y = VECTOR2_UNIT_Y;

	Vector2 Vector2::Transform(const Vector2& v, const Matrix33& M) noexcept
	{
		return {v.x * M.m[0][0] + v.y * M.m[1][0] + M.m[2][0],
		        v.x * M.m[0][1] + v.y * M.m[1][1] + M.m[2][1]};
	}

	Vector2 Vector2::TransformNormal(const Vector2& v, const Matrix33& M) noexcept
	{
		return {v.x * M.m[0][0] + v.y * M.m[1][0],
		        v.x * M.m[0][1] + v.y * M.m[1][1]};
	}

	Vector2 Vector2::TransformCoord(const Vector2&  target,
	                                const Matrix44& M) noexcept
	{
		return Vector2{target.x * M.m[0][0] + target.y * M.m[1][0] + M.m[3][0],
		               target.x * M.m[0][1] + target.y * M.m[1][1] + M.m[3][1]} /=
		       (target.x * M.m[0][3] + target.y * M.m[1][3] + M.m[3][3]);
	}

	Vector2 operator*(const Matrix33& M, const Vector2& v) noexcept
	{
		return {v.x * M.m[0][0] + v.y * M.m[1][0] + M.m[2][0],
		        v.x * M.m[0][1] + v.y * M.m[1][1] + M.m[2][1]};
	}

	Vector2 Vector2::operator*(const Matrix33& M) const noexcept
	{
		return {this->x * M.m[0][0] + this->y * M.m[0][1] + M.m[0][2],
		        this->x * M.m[1][0] + this->y * M.m[1][1] + M.m[1][2]};
	}

	Vector2 operator*(const Matrix44& left, const Vector2& right)
	{
		return Vector2{
		           right.x * left.m[0][0] + right.y * left.m[1][0] + left.m[3][0],
		           right.x * left.m[0][1] + right.y * left.m[1][1] + left.m[3][1]} /=
		       right.x * left.m[0][3] + right.y * left.m[1][3] + left.m[3][3];
	}

	Vector2 Vector2::operator*(const Matrix44& right) const
	{
		return Vector2{this->x * right.m[0][0] + this->y * right.m[0][1] +
		                   right.m[0][3],
		               this->x * right.m[1][0] + this->y * right.m[1][1] +
		                   right.m[1][3]} /=
		       this->x * right.m[3][0] + this->y * right.m[3][1] + right.m[3][3];
	}

} // namespace bavil::math
