#pragma once

#include <cassert>
#include <utility>
#include <algorithm>
#include "bavil_type.h"
#include "math/bavil_math_function.h"
#include "math/bavil_math_def.h"
#include "math/bavil_vector3.h"

namespace bavil::math
{
	struct Matrix33;
	struct Matrix44;

	/// <summary>
	/// ４次元座標・４次元ベクトル構造体.
	/// </summary>
	struct Vector4
	{
		using value_type = f32;
		using value_array_type = f32[4];
		using size_type = u32;
		using vector2_type = Vector2;
		using vector3_type = Vector3;
	public:
#if __cpp_constexpr >= 201304
		union
		{
			struct
			{
#endif
				/// <summary>X座標.</summary>
				value_type x;
				/// <summary>Y座標.</summary>
				value_type y;
				/// <summary>Z座標.</summary>
				value_type z;
				/// <summary>W座標.</summary>
				value_type w;
#if __cpp_constexpr >= 201304
			};
			value_array_type v;
		};
#endif


		/// <summary>要素のサイズ数.</summary>
		static constexpr size_type SIZE = 4U;

		/// <summary>全ての要素がゼロに設定された2次元ベクトル.</summary>
		static const Vector4& ZERO;

		/// <summary>全ての要素が1に設定された2次元ベクトル.</summary>
		static const Vector4& ONE;

		/// <summary>X軸のみ1に設定された2次元ベクトル.</summary>
		static const Vector4& UNIT_X;

		/// <summary>Y軸のみ1に設定された2次元ベクトル.</summary>
		static const Vector4& UNIT_Y;

		/// <summary>Z軸のみ1に設定された2次元ベクトル.</summary>
		static const Vector4& UNIT_Z;

		/// <summary>W軸のみ1に設定された2次元ベクトル.</summary>
		static const Vector4& UNIT_W;

	public:
		/// <summary>
		/// デフォルトコンストラクタ.
		/// </summary>
		constexpr Vector4() noexcept
			: x(), y(), z(), w()
		{
		}

		/// <summary>
		/// 初期化無しコンストラクタ.
		/// </summary>
		/// <param name="_init">初期化なしタグ.</param>
		explicit Vector4(none_init_t _init) noexcept
		{
			static_cast<void>(_init);
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="_x">X成分.</param>
		/// <param name="_y">Y成分.</param>
		/// <param name="_z">Z成分.</param>
		/// <param name="_w">W成分.</param>
		constexpr Vector4(value_type _x, value_type _y, value_type _z, value_type _w) noexcept
			: x(_x), y(_y), z(_z), w(_w)
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="xyz">XYZ成分.</param>
		/// <param name="w">W成分.</param>
		constexpr Vector4(const vector3_type& xyz, const value_type w) noexcept
			: x{ xyz.x }, y{ xyz.y }, z{ xyz.z }, w{ w }
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="p">要素の配列.</param>
		explicit constexpr Vector4(const value_type* p) noexcept
			: x{ p[0] }, y{ p[1] }, z{ p[2] }, w{ p[3] }
		{
		}

		/// <summary>
		/// コピーコンストラクタ.
		/// </summary>
		/// <param name="_other">コピー元.</param>
		constexpr Vector4(const Vector4& _other) noexcept = default;

	public:
		/// <summary>
		/// ベクトルを正規化する.
		/// </summary>
		/// <returns>正規化後のベクトルの参照を取得.</returns>
		Vector4& normalize() noexcept
		{
			return *this /= std::sqrt(this->lengthSq());
		}

		/// <summary>
		/// 正規化したベクトルを取得する.
		/// </summary>
		/// <returns>正規化後のベクトルを取得.</returns>
		Vector4 getNormalized() const
		{
			return Vector4(*this).normalize();
		}

		/// <summary>
		/// ベクトルを正規化する.
		/// </summary>
		/// <returns>正規化後のベクトルの参照を取得.</returns>
		Vector4& safeNormalize() noexcept
		{
			if (const value_type len = this->lengthSq())
			{
				return *this /= std::sqrt(len);
			}
			return *this;
		}

		/// <summary>
		/// 正規化したベクトルを取得する.
		/// </summary>
		/// <returns>正規化後のベクトルを取得.</returns>
		Vector4 getSafeNormalized() const
		{
			return Vector4(*this).safeNormalize();
		}

		/// <summary>
		/// 内積を返す.
		/// </summary>
		/// <param name="V">ベクトル.</param>
		/// <returns>内積を返す.</returns>
		constexpr value_type dot(const Vector4& other) const noexcept
		{
			return (this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w);
		}

		/// <summary>
		/// 長さを求める.
		/// <para>2乗和のみ.</para>
		/// </summary>
		/// <returns>長さを返す.</returns>
		constexpr value_type lengthSq() const noexcept
		{
			return this->dot(*this);
		}

		/// <summary>
		/// 長さを求める.
		/// </summary>
		/// <returns>長さを返す.</returns>
		value_type length() const noexcept
		{
			return std::sqrt(this->lengthSq());
		}

		/// <summary>
		/// 小さい要素を求める.
		/// </summary>
		/// <param name="other">もう一つの要素.</param>
		/// <returns>小さい要素で作成されたベクトルを返す.</returns>
		Vector4& minimize(const Vector4& other) noexcept
		{
			this->x = (std::min)(this->x, other.x);
			this->y = (std::min)(this->y, other.y);
			this->z = (std::min)(this->z, other.z);
			this->w = (std::min)(this->w, other.w);
			return *this;
		}

		/// <summary>
		/// 大きい要素を求める.
		/// </summary>
		/// <param name="other">もう一つの要素.</param>
		/// <returns>大きい要素で作成されたベクトルを返す.</returns>
		Vector4& maximize(const Vector4& other) noexcept
		{
			this->x = (std::max)(this->x, other.x);
			this->y = (std::max)(this->y, other.y);
			this->z = (std::max)(this->z, other.z);
			this->w = (std::max)(this->w, other.w);
			return *this;
		}

		/// <summary>
		/// 最小値と最大値を取得する.
		/// <para>firstが最小値.</para>
		/// <para>secondが最大値.</para>
		/// </summary>
		/// <param name="other">相手ベクトル.</param>
		/// <returns>各要素の最小値で作られたベクトルと最大値で作られたベクトルのペアを返す.</returns>
		std::pair<Vector4, Vector4> minmax(const Vector4& other) const
		{
			const auto axisX = (std::minmax)(this->x, other.x);
			const auto axisY = (std::minmax)(this->y, other.y);
			const auto axisZ = (std::minmax)(this->z, other.z);
			const auto axisW = (std::minmax)(this->w, other.w);

			return std::make_pair(
				Vector4{ axisX.first, axisY.first, axisZ.first, axisW.first },
				Vector4{ axisX.second, axisY.second, axisZ.second, axisW.second }
			);
		}

	public:

		/// <summary>
		/// 線形補完.
		/// </summary>
		/// <param name="start">開始ベクトル.</param>
		/// <param name="end">終了ベクトル.</param>
		/// <param name="amount">時間<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		/// <returns>補間後のベクトルを返す.</returns>
		static Vector4 Lerp(const Vector4& start, const Vector4& end, value_type amount)
		{
			return start * (static_cast<value_type>(1.0) - amount) + end * amount;
		}

		/// <summary>
		/// 2次補間を行う.
		/// </summary>
		/// <param name="V1">ベクトル1.</param>
		/// <param name="V2">ベクトル2.</param>
		/// <param name="V3">ベクトル3.</param>
		/// <param name="amount">時間<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		/// <returns>補間後のベクトルを返す.</returns>
		static Vector4 Quadratic(const Vector4& V1, const Vector4& V2, const Vector4& V3, const value_type amount)
		{
			return
			{
				math::Quadratic(V1.x, V2.x, V3.x, amount),
				math::Quadratic(V1.y, V2.y, V3.y, amount),
				math::Quadratic(V1.z, V2.z, V3.z, amount),
				math::Quadratic(V1.w, V2.w, V3.w, amount)
			};
		}

		/// <summary>
		/// 直線の方程式の計算を行う.
		/// </summary>
		/// <param name="P">4Dベクトル.</param>
		/// <param name="V">4Dベクトル.</param>
		/// <param name="t">係数.</param>
		/// <returns>方程式の解を返す.</returns>
		static CONSTEXPR_CPP11 Vector4 LinearEquation(const Vector4& P, const Vector4& V, const value_type t)
		{
			return
			{
				V.x * t + P.x,
				V.y * t + P.y,
				V.z * t + P.z,
				V.w * t + P.w
			};
		}

		/// <summary>
		/// 方位角，仰角からベクトルを求める.
		/// </summary>
		/// <param name="Elavation">仰角.</param>
		/// <param name="Direction">方位角.</param>
		static Vector4 FromEleDir(Radian Elavation, Radian Direction) noexcept
		{
			return
			{
				Cos(Elavation) * Sin(Direction),
				-Sin(Elavation),
				Cos(Elavation) * Cos(Direction),
				static_cast<value_type>(1.0)
			};
		}

		/// <summary>
		/// 2点間の距離を求める.
		/// </summary>
		/// <param name="my">自身の座標.</param>
		/// <param name="target">ターゲット座標.</param>
		/// <returns>距離を返す.</returns>
		static value_type Distance(const Vector4& my, const Vector4& target)
		{
			return (target - my).length();
		}

		/// <summary>
		/// 2点間の距離を求める.
		/// <para>2乗和のみで平方根は取らない.</para>
		/// </summary>
		/// <param name="my">自身の座標.</param>
		/// <param name="target">ターゲット座標.</param>
		/// <returns>距離を返す.</returns>
		static value_type DistanceSq(const Vector4& my, const Vector4& target)
		{
			return (target - my).lengthSq();
		}


		/// <summary>
		/// ２つのベクトルの作る角度を求める.
		/// </summary>
		/// <param name="V1">ベクトル1.</param>
		/// <param name="V2">ベクトル2.</param>
		/// <returns>角度を返す.</returns>
		static value_type InnerDegree(const Vector4& V1, const Vector4& V2)
		{
			const value_type cos_theta = V1.dot(V2) / (V1.length() * V2.length());

			return std::acos(math::Clamp(cos_theta, -1.f, 1.f));
		}

		/// <summary>
		/// ベクトルの座標変換を行う.
		/// </summary>
		/// <param name="V">変換前のベクトル.</param>
		/// <param name="M">座標変換行列.</param>
		/// <returns>変換後のベクトル.</returns>
		static Vector4 Transform(const Vector4& V, Matrix44 const& M) noexcept;

		/// <summary>
		/// ベクトルの座標変換を行う.
		/// </summary>
		/// <param name="V">変換前のベクトル.</param>
		/// <param name="M">座標変換行列.</param>
		/// <returns>変換後のベクトル.</returns>
		static Vector4 TransformCoord(const Vector4& V, Matrix44 const& M);

	public:
		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>変換後の要素を返す.</returns>
		operator value_type* () noexcept
		{
#if __cpp_constexpr >= 201304
			return this->v;
#else //! __cpp_constexpr >= 201304
			return reinterpret_cast<value_type*>(this);
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>変換後の要素を返す.</returns>
		constexpr operator value_type const* () const noexcept
		{
#if __cpp_constexpr >= 201304
			return this->v;
#else //! __cpp_constexpr >= 201304
			return reinterpret_cast<const value_type*>(this);
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 要素アクセス演算子オーバーロード.
		/// </summary>
		/// <param name="index">アクセスする要素.</param>
		/// <returns>アクセスした要素の参照.</returns>
		constexpr value_type& operator [] (const size_type index)
		{
			assert(0 <= index && index <= 3 && "out of range");
#if __cpp_constexpr >= 201304
			return this->v[index];
#else //! __cpp_constexpr >= 201304
			return reinterpret_cast<value_array_type&>(*this)[index];
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 要素アクセス演算子オーバーロード.
		/// </summary>
		/// <param name="index">アクセスする要素.</param>
		/// <returns>アクセスした要素の参照.</returns>
		constexpr const value_type& operator [] (const size_type index) const noexcept
		{
			//assert( 0 <= index && index <= 3 && "out of range" );
#if __cpp_constexpr >= 201304
			return this->v[index];
#else //! __cpp_constexpr >= 201304
			return reinterpret_cast<const value_array_type&>(*this)[index];
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 加算単行演算子オーバーロード.
		/// </summary>
		/// <returns>加算ベクトルを返す.</returns>
		constexpr Vector4 operator + () const& noexcept
		{
			return Vector4(*this);
		}

		/// <summary>
		/// 加算単行演算子オーバーロード.
		/// </summary>
		/// <returns>加算ベクトルを返す.</returns>
		CONSTEXPR_CPP14 Vector4&& operator + () && noexcept
		{
			return std::move(*this);
		}

		/// <summary>
		/// 減算単行演算子オーバーロード.
		/// </summary>
		/// <returns>減算ベクトルを返す.</returns>
		constexpr Vector4 operator - () const& noexcept
		{
			return Vector4
			{
				-this->x,
				-this->y,
				-this->z,
				-this->w
			};
		}

		/// <summary>
		/// 減算単行演算子オーバーロード.
		/// </summary>
		/// <returns>減算ベクトルを返す.</returns>
		CONSTEXPR_CPP14 Vector4&& operator - () && noexcept
		{
			this->x = -this->x;
			this->y = -this->y;
			this->z = -this->z;
			this->w = -this->w;
			return std::move(*this);
		}

		/// <summary>
		/// 加算代入演算子オーバーロード.
		/// </summary>
		/// <param name="_other">加算相手ベクトル.</param>
		/// <returns>加算後のベクトルを返す.</returns>
		constexpr Vector4& operator += (const Vector4& _other) noexcept
		{
			this->x += _other.x;
			this->y += _other.y;
			this->z += _other.z;
			this->w += _other.w;
			return *this;
		}

		/// <summary>
		/// 減算代入演算子オーバーロード.
		/// </summary>
		/// <param name="_other">減算相手ベクトル.</param>
		/// <returns>減算後のベクトルを返す.</returns>
		CONSTEXPR_CPP14 Vector4& operator -= (const Vector4& _other) noexcept
		{
			this->x -= _other.x;
			this->y -= _other.y;
			this->z -= _other.z;
			this->w -= _other.w;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="_other">乗算相手ベクトル.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		CONSTEXPR_CPP14 Vector4& operator *= (const Vector4& _other) noexcept
		{
			this->x *= _other.x;
			this->y *= _other.y;
			this->z *= _other.z;
			this->w *= _other.w;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">乗算相手ベクトル.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		CONSTEXPR_CPP14 Vector4& operator /= (const Vector4& _other) noexcept
		{
			this->x /= _other.x;
			this->y /= _other.y;
			this->z /= _other.z;
			this->w /= _other.w;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="_scale">スカラー値.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		CONSTEXPR_CPP14 Vector4& operator *= (const value_type _scale) noexcept
		{
			this->x *= _scale;
			this->y *= _scale;
			this->z *= _scale;
			this->w *= _scale;
			return *this;
		}

		/// <summary>
		/// 除算代入演算子オーバーロード.
		/// </summary>
		/// <param name="_scale">スカラー値.</param>
		/// <returns>除算後のベクトルを返す.</returns>
		CONSTEXPR_CPP14 Vector4& operator /= (const value_type _scale) noexcept
		{
			this->x /= _scale;
			this->y /= _scale;
			this->z /= _scale;
			this->w /= _scale;
			return *this;
		}

	public:
		/// <summary>
		/// 2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <param name="v2">ベクトル2.</param>
		/// <returns>加算後のベクトルを返す.</returns>
		constexpr Vector4 operator + (const Vector4& _right) const& noexcept
		{
			return Vector4
			{
				this->x + _right.x,
				this->y + _right.y,
				this->z + _right.z,
				this->w + _right.w
			};
		}

		/// <summary>
		/// 2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <param name="v2">ベクトル2.</param>
		/// <returns>加算後のベクトルを返す.</returns>
		CONSTEXPR_CPP14 Vector4&& operator + (const Vector4& _right) && noexcept
		{
			return std::move(*this += _right);
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値1.</param>
		/// <returns>減算後のベクトルを返す.</returns>
		constexpr Vector4 operator - (const Vector4& right) const& noexcept
		{
			return Vector4
			{
				this->x - right.x,
				this->y - right.y,
				this->z - right.z,
				this->w - right.w
			};
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値1.</param>
		/// <returns>減算後のベクトルを返す.</returns>
		CONSTEXPR_CPP14 Vector4&& operator - (const Vector4& right) && noexcept
		{
			return std::move(*this -= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値1.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		constexpr Vector4 operator * (const value_type right) const& noexcept
		{
			return Vector4
			{
				this->x * right,
				this->y * right,
				this->z * right,
				this->w * right
			};
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値1.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		Vector4&& operator * (const value_type right) && noexcept
		{
			return std::move(*this *= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値1.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		CONSTEXPR_CPP11 Vector4 operator * (const Vector4& right) const& noexcept
		{
			return
			{
				this->x * right.x,
				this->y * right.y,
				this->z * right.z,
				this->w * right.w
			};
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値1.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		Vector4&& operator * (const Vector4& right) && noexcept
		{
			return std::move(*this *= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="_left">左辺値.</param>
		/// <param name="_right">右辺値1.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		friend Vector4 operator * (const value_type _left, const Vector4& _right) noexcept
		{
			return _right * _left;
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="M">行列.</param>
		/// <param name="v">ベクトル.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		friend Vector4 operator * (Matrix44 const& M, const Vector4& v);

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="v">ベクトル.</param>
		/// <param name="M">行列.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		Vector4 operator * (Matrix44 const& M) const;

		/// <summary>
		/// 等価2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>要素が違っていれば真を返す.</returns>
		constexpr bool operator == (const Vector4& right) const noexcept
		{
			return
				this->x == right.x &&
				this->y == right.y &&
				this->z == right.z &&
				this->w == right.w;
		}

		/// <summary>
		/// 非等価2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>要素が違っていれば真を返す.</returns>
		constexpr bool operator != (const Vector4& right) const noexcept
		{
			return	!(*this == right);
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <returns>要素2より大きければ真を返す.</returns>
		constexpr bool operator < (const Vector4& right) const noexcept
		{
			return
				this->x < right.x&&
				this->y < right.y&&
				this->z < right.z&&
				this->w < right.w;
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <returns>要素2より小さければ真を返す.</returns>
		constexpr bool operator >(const Vector4& right) const noexcept
		{
			return
				this->x > right.x &&
				this->y > right.y &&
				this->z > right.z &&
				this->w > right.w;
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <returns>要素2以下なら真を返す.</returns>
		constexpr bool operator <= (const Vector4& right) const noexcept
		{
			return	!(*this > right);
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <returns>要素2以上なら真を返す.</returns>
		constexpr bool operator >= (const Vector4& right) const noexcept
		{
			return	!(*this < right);
		}

	}; //! struct Vector4

}
