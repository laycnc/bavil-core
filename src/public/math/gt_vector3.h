#pragma once

#include <cmath>
#include <utility>
#include "gt_type.h"
#include "math/gt_math_function.h"
#include "math/gt_math_def.h"
#include "math/gt_vector2.h"


namespace gt::math
{

	struct Matrix33;
	struct Matrix44;

	/// <summary>
	/// 3次元ベクトル構造体.
	/// </summary>
	struct Vector3
	{
		using vector2_type = Vector2;
		using matrix44_type = Matrix44;
		using value_type = f32;
		using value_array_type = f32[3];
		using size_type = u32;
	public:
#if __cpp_constexpr >= 201304
		union
		{
			struct
			{
#endif
				/// <summary>
				/// X成分.
				/// </summary>
				value_type	x;
				/// <summary>
				/// Y成分.
				/// </summary>
				value_type	y;
				/// <summary>
				/// Z成分.
				/// </summary>
				value_type	z;
#if __cpp_constexpr >= 201304
			};
			value_array_type v;
		};
#endif
	public:
		/// <summary>
		/// 要素のサイズ数.
		/// </summary>
		static constexpr size_type SIZE = 3;
		/// <summary>
		/// 全ての要素がゼロに設定された2次元ベクトル.
		/// </summary>
		static const Vector3 ZERO;
		/// <summary>
		/// 全ての要素が1に設定された2次元ベクトル.
		/// </summary>
		static const Vector3 ONE;
		/// <summary>
		/// X軸のみ1に設定された2次元ベクトル.
		/// </summary>
		static const Vector3 UNIT_X;
		/// <summary>
		/// Y軸のみ1に設定された2次元ベクトル.
		/// </summary>
		static const Vector3 UNIT_Y;
		/// <summary>
		/// Z軸のみ1に設定された2次元ベクトル.
		/// </summary>
		static const Vector3 UNIT_Z;

	public:
		/// <summary>
		/// デフォルトコンストラクタ.
		/// </summary>
		constexpr Vector3() noexcept
			: x{}, y{}, z{}
		{
		}

		/// <summary>
		/// 初期化無しコンストラクタ.
		/// </summary>
		/// <param name="_init">初期化なしタグ.</param>
		explicit Vector3(none_init_t _init) noexcept
		{
			static_cast<void>(_init);
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <remarks>初期化</remarks>
		/// <param name="v">XYZ成分.</param>
		constexpr explicit Vector3(const value_type v) noexcept
			: x{ v }, y{ v }, z{ v }
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="X">X成分</param>
		/// <param name="Y">Y成分</param>
		/// <param name="Z">Z成分</param>
		constexpr Vector3(value_type X, value_type Y, value_type Z) noexcept
			: x{ X }, y{ Y }, z{ Z }
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="xy">XY成分.</param>
		/// <param name="z">Z成分.</param>
		constexpr Vector3(Vector2& xy, value_type z) noexcept
			: x{ xy.x }, y{ xy.y }, z{ z }
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="V">成分の配列</param>
		constexpr Vector3(const value_type* V) noexcept
			: x{ V[0] }, y{ V[1] }, z{ V[2] }
		{
		}


		/// <summary>
		/// コピーコンストラクタ.
		/// </summary>
		/// <param name="other">コピー対象.</param>
		constexpr Vector3(const Vector3& other) noexcept = default;

		/// <summary>
		/// デストラクタ.
		/// </summary>
		~Vector3() noexcept = default;

	public:

		/// <summary>
		/// ノルムを求める.
		/// </summary>
		/// <returns>ノルムを返す.</returns>
		value_type length() const noexcept
		{
			return std::sqrt(this->lengthSqr());
		}

		/// <summary>
		/// ノルムを求める.
		/// <para>ベクトルの長さを求める.</para>
		/// <para>2乗和のみで平方根をとらない.</para>
		/// </summary>
		/// <returns>ノルムを返す.</returns>
		constexpr value_type lengthSqr() const noexcept
		{
			//return this->dot(*this);
			return (this->x * this->x + this->y * this->y + this->z * this->z);
		}

		/// <summary>
		/// 正規化する.
		/// </summary>
		/// <returns>正規化したベクトルを返す.</returns>
		Vector3& normalize() noexcept
		{
			return *this /= std::sqrt(this->lengthSqr());
		}

		/// <summary>
		/// 正規化したベクトルを返す.
		/// </summary>
		/// <returns>正規化したベクトルを返す.</returns>
		Vector3 getNormalize() const& noexcept
		{
			return Vector3(*this).normalize();
		}

		/// <summary>
		/// 正規化したベクトルを返す.
		/// </summary>
		/// <returns>正規化したベクトルを返す.</returns>
		Vector3&& getNormalize() && noexcept
		{
			return std::move(this->normalize());
		}

		/// <summary>
		/// 安全に正規化する.
		/// </summary>
		/// <returns>正規化したベクトルを返す.</returns>
		Vector3& safeNormalize() noexcept
		{
			if (const value_type len = this->lengthSqr())
			{
				return *this /= std::sqrt(len);
			}
			return *this;
		}

		/// <summary>
		/// 正規化したベクトルを返す.
		/// </summary>
		/// <returns>正規化したベクトルを返す.</returns>
		Vector3 getSafeNormalize() const& noexcept
		{
			return Vector3(*this).safeNormalize();
		}

		/// <summary>
		/// 正規化したベクトルを返す.
		/// </summary>
		/// <returns>正規化したベクトルを返す.</returns>
		Vector3&& getSafeNormalize() && noexcept
		{
			return std::move(this->safeNormalize());
		}

		/// <summary>
		/// 内積を求める.
		/// </summary>
		/// <param name="V">ベクトル</param>
		/// <returns>内積を返す.</returns>
		constexpr value_type dot(const Vector3& V) const noexcept
		{
			return (this->x * V.x + this->y * V.y + this->z * V.z);
		}

		/// <summary>
		/// 外積を求める.
		/// </summary>
		/// <param name="V">ベクトル</param>
		/// <returns>外積を返す.</returns>
		constexpr Vector3 cross(const Vector3& V) const noexcept
		{
			return
			{
				this->y * V.z - this->z * V.y,
				this->z * V.x - this->x * V.z,
				this->x * V.y - this->y * V.x
			};
		}

		/// <summary>
		/// 小さい要素を求める.
		/// </summary>
		/// <param name="other">もう一つの要素</param>
		Vector3 minimize(const Vector3& other) const
		{
			return
			{
				(std::min)(this->x, other.x),
				(std::min)(this->y, other.y),
				(std::min)(this->z, other.z)
			};
		}

		/// <summary>
		/// 大きい要素を求める.
		/// </summary>
		/// <param name="other">もう一つの要素</param>
		Vector3 maximize(const Vector3& other) const
		{
			return
			{
				(std::max)(this->x, other.x),
				(std::max)(this->y, other.y),
				(std::max)(this->z, other.z)
			};
		}

		/// <summary>
		/// 絶対値ベクトルを求める.
		/// </summary>
		/// <returns>絶対値ベクトルを返す.</returns>
		Vector3& abs() noexcept
		{
			this->x = std::abs(this->x);
			this->y = std::abs(this->y);
			this->z = std::abs(this->z);
			return *this;
		}

		/// <summary>
		/// 絶対値ベクトルを求める.
		/// </summary>
		/// <returns>絶対値ベクトルを返す.</returns>
		Vector3 getAbs() const noexcept
		{
			return std::move(Vector3(*this).abs());
		}


		/// <summary>
		/// 3次元ベクトルのピッチを求める.
		/// </summary>
		/// <returns>ピッチを返す.</returns>
		value_type getPitch() const noexcept
		{
			if (const value_type len = this->length())
			{
				return std::asin(-this->y / std::sqrt(len));
			}
			return static_cast<value_type>(0.0);
		}

		/// <summary>
		/// 3次元ベクトルのヨーを求める.
		/// </summary>
		/// <returns>ヨーを返す.</returns>
		value_type getYaw() const
		{
			if (this->length() == static_cast<value_type>(0.0))
			{
				return static_cast<value_type>(0.0);
			}
			return std::atan2(this->x, this->z);
		}

		/// <summary>
		/// ベクトルから仰角と方位角を求める.
		/// </summary>
		/// <param name="pElevation">[out]仰角.</param>
		/// <param name="pDirection">[out]方位角.</param>
		/// <param name="V">ベクトル.</param>
		void toEleDir(value_type* pElevation, value_type* pDirection) const
		{
			if (pElevation)
			{
				*pElevation = this->getPitch();
			}
			if (pDirection)
			{
				*pDirection = this->getYaw();
			}
		}

		/// <summary>
		/// 2次元ベクトル型に変換する.
		/// </summary>
		/// <returns>参照を返す.</returns>
		const Vector2& toVector2() const noexcept
		{
			return reinterpret_cast<const Vector2&>(*this);
		}


	public:
		/// <summary>
		/// 要素の先頭を示すポインタを取得.
		/// </summary>
		value_type* begin() noexcept
		{
#if __cpp_constexpr >= 201304
			return std::begin(this->v);
#else //! __cpp_constexpr >= 201304
			return gt::begin(reinterpret_cast<value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 要素の先頭を示すポインタを取得.
		/// </summary>
		constexpr const value_type* begin() const noexcept
		{
#if __cpp_constexpr >= 201304
			return std::begin(this->v);
#else //! __cpp_constexpr >= 201304
			return gt::begin(reinterpret_cast<const value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}
		/// <summary>
		/// 要素の最後の次を示すポインタを取得.
		/// </summary>
		value_type* end() noexcept
		{
#if __cpp_constexpr >= 201304
			return std::end(this->v);
#else //! __cpp_constexpr >= 201304
			return gt::end(reinterpret_cast<value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 要素の最後の次を示すポインタを取得.
		/// </summary>
		constexpr const value_type* end() const noexcept
		{
#if __cpp_constexpr >= 201304
			return std::end(this->v);
#else //! __cpp_constexpr >= 201304
			return gt::end(reinterpret_cast<const value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}

	public:
		/// <summary>
		/// 2点間の距離を求める.
		/// </summary>
		/// <param name="my">自身の座標.</param>
		/// <param name="target">ターゲット座標.</param>
		/// <returns>距離を返す.</returns>
		static value_type Distance(const Vector3& my, const Vector3& target)
		{
			return (target - my).length();
		}

		/// <summary>
		/// 2点間の距離を求める.
		/// <para>２乗和のみ.</para>
		/// </summary>
		/// <param name="my">自身の座標.</param>
		/// <param name="target">ターゲット座標.</param>
		/// <returns>距離を返す.</returns>
		static value_type DistanceSqr(const Vector3& my, const Vector3& target)
		{
			return (target - my).lengthSqr();
		}

		/// <summary>
		/// ターゲット方向への移動量を求める.
		/// </summary>
		/// <param name="my">自身の座標.</param>
		/// <param name="target">ターゲット座標.</param>
		/// <returns>移動量を返す.</returns>
		static Vector3 Velocity(const Vector3& my, const Vector3& target, const value_type speed = 1.0)
		{
			return (target - my).getNormalize() * speed;
		}

		/// <summary>
		/// 線形補完.
		/// </summary>
		/// <param name="">開始ベクトル.</param>
		/// <param name="">終了ベクトル.</param>
		/// <param name="">時間<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		static Vector3 Lerp(const Vector3& start, const Vector3& end, value_type t)
		{
			return start * (static_cast<value_type>(1.0) - t) + end * t;
		}

		/// <summary>
		/// 反射ベクトルを求める.
		/// </summary>
		/// <param name="vIn">入射ベクトル.</param>
		/// <param name="vN">法線ベクトル.</param>
		/// <returns>反射ベクトルを返す.</returns>
		static Vector3 Reflection(const Vector3& vIn, const Vector3& vN)
		{
			// Out = 2 * ( -I dot N ) * N + I.
			return static_cast<value_type>(2.0) * vN.dot(-vIn) * vN + vIn;
		}

		/// <summary>
		/// 屈折ベクトルを求める.
		/// </summary>
		/// <param name="vIn">入射ベクトル.</param>
		/// <param name="vN">法線ベクトル.</param>
		/// <param name="eta">屈折率比.</param>
		/// <returns>反射ベクトル.</returns>
		static Vector3 Refraction(const Vector3& vIn, const Vector3& vN, const value_type eta)
		{
			const value_type cosI = vN.dot(-vIn);
			const value_type cosT2 = static_cast<value_type>(1.0) - eta * eta * (static_cast<value_type>(1.0) - cosI * cosI);

			if (cosT2 <= static_cast<value_type>(0.0))
			{
				return Vector3::ZERO;
			}

			return (vIn * eta) + vN * (eta * cosI - std::sqrt(std::abs(cosT2)));
		}

		/// <summary>
		/// ピッチとヨーからベクトルを求める.
		/// </summary>
		/// <param name="pitch">ピッチ.<para>X軸まわりの回転角度</para></param>
		/// <param name="yaw">ヨー.<para>Y軸まわりの回転角度</para></param>
		static Vector3 FromPitchYaw(Radian pitch, Radian yaw) noexcept
		{
			return
			{
				Cos(pitch) * Sin(yaw),
				-Sin(pitch),
				Cos(pitch) * Cos(yaw)
			};
		}

		/// <summary>
		/// 直線の方程式の計算を行う.
		/// </summary>
		/// <param name="p">3Dベクトル.</param>
		/// <param name="v">3Dベクトル.</param>
		/// <param name="t">係数.</param>
		static Vector3 LinearEquation(const Vector3& p, const Vector3& v, const value_type t)
		{
			return
			{
				v.x * t + p.x,
				v.y * t + p.y,
				v.z * t + p.z
			};
		}

		/// <summary>
		/// ベクトルの座標変換を行う.
		/// </summary>
		/// <param name="v">変換前のベクトル.</param>
		/// <param name="M">座標変換行列.</param>
		/// <returns>変換後のベクトル.</returns>
		static Vector3 Transform(const Vector3& v, const Matrix44& M);

		/// <summary>
		/// ベクトルの座標変換を行う.
		/// </summary>
		/// <param name="v">変換前のベクトル.</param>
		/// <param name="M">座標変換行列.</param>
		/// <returns>変換後のベクトル.</returns>
		static Vector3 TransformCoord(const Vector3& v, const Matrix44& M);

		/// <summary>
		/// 法線ベクトルの座標変換を行う.
		/// </summary>		
		/// <param name="v">変換前のベクトル.</param>
		/// <param name="M">座標変換行列.</param>
		/// <returns>変換後のベクトル.</returns>
		static Vector3 TransformNormal(const Vector3& v, const Matrix44& M);

		/// <summary>
		/// 面法線を求める.
		/// </summary>
		/// <param name="V0">三角形の頂点座標0.</param>
		/// <param name="V1">三角形の頂点座標1.</param>
		/// <param name="V2">三角形の頂点座標2.</param>
		/// <returns>法線ベクトル.</returns>
		static Vector3 CalculateNormal(const Vector3& V0, const Vector3& V1, const Vector3& V2)
		{
			/* ３角形の頂点からベクトルを求める */
			Vector3 _V1 = V0 - V1;
			Vector3 _V2 = V1 - V2;

			/* ２つのベクトルの外積を求める */
			/* ベクトルのを正規化する */
			return	_V1.cross(_V2).normalize();
		}

	public:
		/// <summary>
		/// 加算単行演算子オーバーロード.
		/// </summary>
		constexpr Vector3 operator + () const& noexcept
		{
			return Vector3{ *this };
		}

		/// <summary>
		/// 加算単行演算子オーバーロード.
		/// </summary>
		Vector3&& operator + ()&&
		{
			return std::move(*this);
		}

		/// <summary>
		/// 減算単行演算子オーバーロード.
		/// </summary>
		constexpr Vector3 operator - () const& noexcept
		{
			return
			{
				-this->x,
				-this->y,
				-this->z
			};
		}

		/// <summary>
		/// 減算単行演算子オーバーロード.
		/// </summary>
		Vector3&& operator - () && noexcept
		{
			this->x = -this->x;
			this->y = -this->y;
			this->z = -this->z;
			return std::move(*this);
		}

		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>キャスト後のポインタを返す.</returns>
		CONSTEXPR_CPP14 operator value_type* () noexcept
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
		/// <returns>キャスト後のポインタを返す.</returns>
		constexpr operator value_type const* () const noexcept
		{
#if __cpp_constexpr >= 201304
			return this->v;
#else //! __cpp_constexpr >= 201304
			return reinterpret_cast<const value_type*>(this);
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 加算代入演算子オーバーロード.
		/// </summary>
		/// <param name="V">加算相手ベクトル.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3& operator += (const Vector3& V) noexcept
		{
			this->x += V.x;
			this->y += V.y;
			this->z += V.z;
			return *this;
		}

		/// <summary>
		/// 減算代入演算子オーバーロード.
		/// </summary>
		/// <param name="V">減算相手ベクトル.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3& operator -= (const Vector3& V) noexcept
		{
			this->x -= V.x;
			this->y -= V.y;
			this->z -= V.z;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="s">スカラー値.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3& operator *= (const value_type s) noexcept
		{
			this->x *= s;
			this->y *= s;
			this->z *= s;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="V">乗算相手ベクトル.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3& operator *= (const Vector3& V) noexcept
		{
			this->x *= V.x;
			this->y *= V.y;
			this->z *= V.z;
			return *this;
		}

		/// <summary>
		/// 除算代入演算子オーバーロード.
		/// </summary>
		/// <param name="s">スカラー値.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3& operator /= (const value_type s)
		{
			return *this *= static_cast<value_type>(1.0) / s;
		}

		/// <summary>
		/// 除算代入演算子オーバーロード.
		/// </summary>
		/// <param name="V">除算相手ベクトル.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3& operator /= (const Vector3& V)
		{
			this->x *= static_cast<value_type>(1.0) / V.x;
			this->y *= static_cast<value_type>(1.0) / V.y;
			this->z *= static_cast<value_type>(1.0) / V.z;
			return *this;
		}

		/// <summary>
		/// 加算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺1.</param>
		/// <returns>計算後のベクトル.</returns>
		constexpr Vector3 operator + (const Vector3& right) const& noexcept
		{
			return
			{
				this->x + right.x,
				this->y + right.y,
				this->z + right.z
			};
		}

		/// <summary>
		/// 加算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺1.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3&& operator + (const Vector3& right) && noexcept
		{
			return std::move(*this += right);
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3 operator - (const Vector3& right) const& noexcept
		{
			return
			{
				this->x - right.x,
				this->y - right.y,
				this->z - right.z
			};
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3&& operator - (const Vector3& right) && noexcept
		{
			return std::move(*this -= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺.</param>
		/// <returns>計算後のベクトル.</returns>
		constexpr Vector3 operator * (const value_type right) const& noexcept
		{
			return
			{
				this->x * right,
				this->y * right,
				this->z * right
			};
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3&& operator * (const value_type right) && noexcept
		{
			return std::move(*this *= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="s">スカラー値.</param>
		/// <param name="V">ベクトル.</param>
		/// <returns>計算後のベクトル.</returns>
		friend Vector3 operator * (const value_type left, const Vector3& right) noexcept
		{
			return right * left;
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺.</param>
		/// <returns>計算後のベクトル.</returns>
		constexpr Vector3 operator * (const Vector3& right) const& noexcept
		{
			return
			{
				this->x * right.x,
				this->y * right.y,
				this->z * right.z
			};
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3&& operator * (const Vector3& right) && noexcept
		{
			return std::move(*this *= right);
		}

		friend Vector3 operator * (const Matrix33& M, const Vector3& v) noexcept;

		Vector3 operator * (const Matrix33& M) const noexcept;

		/// <summary>
		/// 除算2項演算子オーバーロード.
		/// </summary>
		/// <param name="s">スカラー値.</param>
		/// <returns>計算後のベクトル.</returns>
		constexpr Vector3 operator / (const value_type right) const&
		{
			return{ this->x / right, this->y / right, this->z / right };
		}

		/// <summary>
		/// 除算2項演算子オーバーロード.
		/// </summary>
		/// <param name="s">スカラー値.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3&& operator / (const value_type right)&&
		{
			return std::move(*this /= right);
		}

		/// <summary>
		/// 除算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">スカラー値.</param>
		/// <returns>計算後のベクトル.</returns>
		constexpr Vector3 operator / (const Vector3& right) const&
		{
			return{ this->x / right.x, this->y / right.y, this->z / right.z };
		}

		/// <summary>
		/// 除算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">スカラー値.</param>
		/// <returns>計算後のベクトル.</returns>
		Vector3&& operator / (const Vector3& right)&&
		{
			return std::move(*this /= right);
		}

		/// <summary>
		/// 等価2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>要素が違っていれば真を返す.</returns>
		constexpr bool operator == (const Vector3& right) const noexcept
		{
			return
				this->x == right.x &&
				this->y == right.y &&
				this->z == right.z;
		}

		/// <summary>
		/// 非等価2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>要素が違っていれば真を返す.</returns>
		constexpr bool operator != (const Vector3& right) const noexcept
		{
			return	!(*this == right);
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>要素2より大きければ真を返す.</returns>
		constexpr bool operator < (const Vector3& right) const noexcept
		{
			return
				this->x < right.x&&
				this->y < right.y&&
				this->z < right.z;
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>要素2より小さければ真を返す.</returns>
		constexpr bool operator >(const Vector3& right) const noexcept
		{
			return
				this->x > right.x &&
				this->y > right.y &&
				this->z > right.z;
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>要素2以下なら真を返す.</returns>
		constexpr bool operator <= (const Vector3& right) const noexcept
		{
			return	!(*this > right);
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>要素2以上なら真を返す.</returns>
		constexpr bool operator >= (const Vector3& right) const noexcept
		{
			return	!(*this < right);
		}
	};

}
