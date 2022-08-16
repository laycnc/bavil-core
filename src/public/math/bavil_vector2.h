#pragma once

#include <utility>
#include "bavil_type.h"
#include "bavil_utility.h"
#include "math/bavil_math_function.h"
#include "math/bavil_math_def.h"

#pragma warning(push)
#pragma warning(disable : 4201)

namespace bavil::math
{

	/// <summary>
	/// 2次元ベクトル構造体.
	/// </summary>
	struct Vector2
	{
		using value_type       = f32;
		using value_array_type = f32[2];
		using size_type        = u32;
	public:
		union
		{
			struct
			{
				/// <summary>
				/// X成分.
				/// </summary>
				value_type x;
				/// <summary>
				/// Y成分
				/// </summary>
				value_type y;
			};
			value_array_type v;
		};
	public:
		/// <summary>
		/// 要素のサイズ数.
		/// </summary>
		static constexpr size_type SIZE = 2;
		/// <summary>
		/// 全ての要素がゼロに設定された2次元ベクトル.
		/// </summary>
		static const Vector2 ZERO;
		/// <summary>
		/// 全ての要素が1に設定された2次元ベクトル.
		/// </summary>
		static const Vector2 ONE;
		/// <summary>
		/// X軸のみ1に設定された2次元ベクトル.
		/// </summary>
		static const Vector2 UNIT_X;
		/// <summary>
		/// Y軸のみ1に設定された2次元ベクトル.
		/// </summary>
		static const Vector2 UNIT_Y;

	public:
		/// <summary>
		/// 2点間の距離を求める.
		/// </summary>
		/// <param name="my">自身の座標.</param>
		/// <param name="target">ターゲット座標.</param>
		/// <returns>距離を返す.</returns>
		static value_type Distance(const Vector2& my, const Vector2& target) noexcept
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
		static value_type DistanceSqr(const Vector2& my,
		                              const Vector2& target) noexcept
		{
			return (target - my).length_sqr();
		}

		/// <summary>
		/// ターゲット方向への移動量を求める.
		/// </summary>
		/// <param name="my">自身の座標.</param>
		/// <param name="target">ターゲット座標.</param>
		/// <returns>移動量を返す.</returns>
		static Vector2 Velocity(const Vector2& my,
		                        const Vector2& target,
		                        value_type     speed = 1.0f) noexcept
		{
			return (target - my).get_normalized() * speed;
		}

		/// <summary>
		/// 指定方向への移動量を求める.
		/// <para>角度からベクトルを求める.</para>
		/// </summary>
		/// <param name="radian">角度</param>
		/// <param name="speed">速度</param>
		/// <returns>移動量を返す</returns>
		static Vector2 Velocity(Radian radian, value_type speed = 1.0f) noexcept
		{
			return Vector2{Cos(radian) * speed, Sin(radian) * speed};
		}

		/// <summary>
		/// 線形補完.
		/// </summary>
		/// <param name="">開始ベクトル.</param>
		/// <param name="">終了ベクトル.</param>
		/// <param name="">時間<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		static Vector2 Lerp(const Vector2& start,
		                    const Vector2& end,
		                    value_type     t) noexcept
		{
			return start * (static_cast<value_type>(1.0) - t) + end * t;
		}

		/// <summary>
		/// 直線の方程式の計算を行う.
		/// </summary>
		/// <param name="P">2Dベクトル.</param>
		/// <param name="V">2Dベクトル.</param>
		/// <param name="t">係数.</param>
		static Vector2 LinearEquation(const Vector2& P,
		                              const Vector2& V,
		                              value_type     t) noexcept
		{
			return Vector2{V.x * t + P.x, V.y * t + P.y};
		}

		/// <summary>
		/// ベクトルの向いている角度を求める.
		/// <para>ベクトルから角度を求める.</para>
		/// </summary>
		/// <param name="v">ベクトル</param>
		/// <returns>角度を返す</returns>
		static Radian Angle(const Vector2& v) noexcept
		{
			return Radian::Create(std::atan2(v.y, v.x));
		}

		/// <summary>
		/// ターゲット方向への角度を求める.
		/// </summary>
		/// <param name="my">自身のベクトル</param>
		/// <param name="target">相手のベクトル</param>
		/// <returns>角度を返す</returns>
		static Radian Angle(const Vector2& my, const Vector2& target) noexcept
		{
			return Vector2::Angle(target - my);
		}

		/// <summary>
		/// 2つのベクトルの作る角度を求める.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <param name="v2">ベクトル1.</param>
		/// <returns>角度を返す.</returns>
		static value_type InnerDegree(const Vector2& v1, const Vector2& v2)
		{
			value_type cos_theta = v1.dot(v2) / (v1.length() * v2.length());

			return std::acos(std::clamp(cos_theta, -1.0f, 1.0f));
		}

		/// <summary>
		/// ベクトルの座標変換を行う.
		/// </summary>
		/// <param name="pV">変換前のベクトル.</param>
		/// <param name="pM">座標変換行列.</param>
		/// <returns>返還後のベクトルを返す.</returns>
		static Vector2 Transform(const Vector2& v, const Matrix33& M) noexcept;

		/// <summary>
		/// 法線ベクトルの座標変換を行う.
		/// </summary>
		/// <typeparam name="Mat33">行列型.</typeparam>
		/// <typeparam name="">3行3列の行列か判定.</typeparam>
		/// <param name="pV">変換前のベクトル.</param>
		/// <param name="pM">座標変換行列.</param>
		/// <returns>変換後の法線ベクトル.</returns>
		static Vector2 TransformNormal(const Vector2& v, const Matrix33& M) noexcept;

		/// <summary>
		/// 座標変換を行う．
		/// <para>3D変換行列を使用する.</para>
		/// </summary>
		/// <param name="pV">変換前のベクトル.</param>
		/// <param name="pM">座標変換行列.</param>
		/// <returns>変換後の法線ベクトル.</returns>
		static Vector2 TransformCoord(const Vector2&  target,
		                              const Matrix44& M) noexcept;

	public:
		/// <summary>
		/// コンストラクタ.
		/// </summary>
		constexpr Vector2() noexcept
		    : x()
		    , y()
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="">初期化無視型.</param>
		explicit Vector2(none_init_t) noexcept {}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="_xy">XY成分.</param>
		constexpr Vector2(const value_type _xy) noexcept
		    : x(_xy)
		    , y(_xy)
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="_x">X成分.</param>
		/// <param name="_y">Y成分.</param>
		constexpr Vector2(const value_type _x, const value_type _y) noexcept
		    : x(_x)
		    , y(_y)
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="p">要素の配列の先頭ポインタ.</param>
		explicit constexpr Vector2(const value_type* p) noexcept
		    : x(p[0])
		    , y(p[1])
		{
		}

		/// <summary>
		/// コピーコンストラクタ.
		/// </summary>
		/// <param name="_other">コピー元.</param>
		constexpr Vector2(const Vector2& _other) noexcept = default;

		/// <summary>
		/// デストラクタ.
		/// </summary>
		~Vector2() noexcept = default;

		/// <summary>
		/// 正規化.
		/// </summary>
		/// <returns>正規化後の参照を返す.</returns>
		Vector2& normalize() noexcept
		{
			if ( const value_type len = this->length_sqr() )
			{
				*this *= 1.f / std::sqrt(len);
			}

			return *this;
		}

		/// <summary>
		/// 正規化したベクトルを取得する.
		/// </summary>
		/// <returns>正規化したベクトルを返す.</returns>
		Vector2 get_normalized() const noexcept
		{
			return Vector2(*this).normalize();
		}

		/// <summary>
		/// 内積を求める.
		/// <para>a・b = |a||b|cosθ</para>
		/// </summary>
		/// <param name="other">ベクトル</param>
		/// <returns>内積を返す.</returns>
		constexpr value_type dot(const Vector2& other) const noexcept
		{
			return this->x * other.x + this->y * other.y;
		}

		/// <summary>
		/// ベクトルの長さを求める.
		/// <para>二乗和のみで平方根をとらない.</para>
		/// </summary>
		/// <returns>ベクトルの長さを返す.</returns>
		value_type length_sqr() const noexcept
		{
			return this->dot(*this);
		}

		/// <summary>
		/// ベクトルの長さを求める.
		/// </summary>
		/// <returns>ベクトルの長さを返す.</returns>
		value_type length() const noexcept
		{
			return std::sqrt(this->length_sqr());
		}

		/// <summary>
		/// ２点間の距離を求める.
		/// </summary>
		/// <param name="endPoint">終点.</param>
		/// <returns>距離を返す.</returns>
		value_type distance(const Vector2& endPoint) const
		{
			return (*this - endPoint).length();
		}

		/// <summary>
		/// ２点間の距離を求める.
		/// <para>二乗和だけで平方根を取らない.</para>
		/// </summary>
		/// <param name="endPoint">終点.</param>
		/// <returns>距離を返す.</returns>
		value_type distance_sqr(const Vector2& endPoint) const noexcept
		{
			return (*this - endPoint).length_sqr();
		}

		/// <summary>
		/// ベクトルの外積を求める.
		/// </summary>
		/// <param name="other">ベクトル</param>
		/// <returns>外積を返す.</returns>
		constexpr value_type ccw(const Vector2& other) const noexcept
		{
			return this->x * other.y - this->y * other.x;
		}

		/// <summary>
		/// 各要素の最小値を求めたベクトルを返す.
		/// </summary>
		constexpr Vector2& minimize(const Vector2& other) && noexcept
		{
			this->x = (this->x < other.x) ? this->x : other.x;
			this->y = (this->y < other.y) ? this->y : other.y;

			return *this;
		}

		/// <summary>
		/// 各要素の最小値を求めたベクトルを返す.
		/// </summary>
		constexpr Vector2 minimize(const Vector2& other) const& noexcept
		{
			return {(this->x < other.x) ? this->x : other.x,
			        (this->y < other.y) ? this->y : other.y};
		}

		/// <summary>
		/// 2つのベクトルの各要素の最大値から作成されたベクトルを求める.
		/// </summary>
		/// <returns>各要素の最大値を求めたベクトルを返す.</returns>
		constexpr Vector2& maximize(const Vector2& other) && noexcept
		{
			this->x = (this->x > other.x) ? this->x : other.x;
			this->y = (this->y > other.y) ? this->y : other.y;

			return *this;
		}

		/// <summary>
		/// 2つのベクトルの各要素の最大値から作成されたベクトルを求める.
		/// </summary>
		/// <returns>各要素の最大値を求めたベクトルを返す.</returns>
		constexpr Vector2 maximize(const Vector2& other) const& noexcept
		{
			return {(this->x > other.x) ? this->x : other.x,
			        (this->y > other.y) ? this->y : other.y};
		}

		/// <summary>
		/// 線形補間を行う.
		/// </summary>
		/// <param name="start">開始時のベクトル.</param>
		/// <param name="end">終了時のベクトル.</param>
		/// <param name="amount">補間値(0.0~1.0).</param>
		/// <returns>補間後の参照を返す.</returns>
		constexpr Vector2& lerp(const Vector2& start,
		                        const Vector2& end,
		                        value_type     amount) noexcept
		{
			*this = (start * (1.f - amount)) + end * amount;

			return *this;
		}

		/// <summary>
		/// 2次補間を行う.
		/// </summary>
		/// <param name="V1">ベクトル.</param>
		/// <param name="V2">ベクトル.</param>
		/// <param name="V3">ベクトル.</param>
		/// <param name="amount">補間値(0.0~1.0).</param>
		/// <returns>補間後の参照を返す.</returns>
		constexpr Vector2& quadratic(const Vector2& V1,
		                             const Vector2& V2,
		                             const Vector2& V3,
		                             value_type     amount)
		{
			this->x = math::Quadratic(V1.x, V2.x, V3.x, amount);
			this->y = math::Quadratic(V1.y, V2.y, V3.y, amount);
			return *this;
		}

		/// <summary>
		/// 反射ベクトルを求める.
		/// </summary>
		/// <param name="I">入射ベクトル.</param>
		/// <param name="N">法線ベクトル.</param>
		constexpr Vector2& reflect(const Vector2& I, const Vector2& N)
		{
			/* Out = 2 * ( -I dot N ) * N + I */
			const Vector2 t = N * ((-I).dot(N) * 2.0f);
			*this           = t + I;

			return *this;
		}

		/// <summary>
		/// 屈折ベクトルを求める.
		/// </summary>
		/// <param name="I">入射ベクトル.</param>
		/// <param name="N">反射ベクトル.</param>
		/// <param name="Eta">屈折比率.</param>
		constexpr Vector2& refract(const Vector2& I,
		                           const Vector2& N,
		                           value_type     Eta)
		{
			Vector2          t1     = -I;
			const value_type cos_i  = t1.dot(N);
			const value_type cos_t2 = 1.f - Eta * Eta * (1.0f - cos_i * cos_i);

			if ( cos_t2 <= 0.0f )
			{
				return *this = Vector2();
			}

			t1               = I * Eta;
			const Vector2 t2 = N * (Eta * cos_i - std::sqrt(std::abs(cos_t2)));
			*this            = t1 + t2;
			return *this;
		}

		/// <summary>
		/// 2つのベクトルの作る角度を求める.
		/// </summary>
		/// <param name="V">ベクトル.</param>
		/// <returns>角度を返す.</returns>
		value_type degree(const Vector2& V) const
		{
			return Vector2::InnerDegree(*this, V);
		}

		/// <summary>
		/// 方位角を求める.
		/// </summary>
		value_type get_direction() const noexcept
		{
			if ( const value_type len = this->length() )
			{
				// ベクトルを正規化する.
				// 方角の計算を行う.
				return std::atan2(this->x / len, this->y / len);
			}
			// 長さが０の場合は０にする.
			return 0.f;
		}

		/// <summary>
		/// 方位角からベクトルを求める.
		/// </summary>
		/// <param name="direction">方位角.</param>
		Vector2& from_direction(Radian direction) noexcept
		{
			this->x = Sin(direction);
			this->y = Cos(direction);

			return *this;
		}

		/// <summary>
		/// 要素の先頭を示すポインタを取得.
		/// </summary>
		constexpr value_type* begin() noexcept
		{
#if __cpp_constexpr >= 201304
			return std::begin(this->v);
#else  //! __cpp_constexpr >= 201304
			return std::begin(reinterpret_cast<value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 要素の先頭を示すポインタを取得.
		/// </summary>
		CONSTEXPR_CPP11 const value_type* begin() const noexcept
		{
#if __cpp_constexpr >= 201304
			return std::begin(this->v);
#else  //! __cpp_constexpr >= 201304
			return std::begin(reinterpret_cast<const value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 要素の最後の次を示すポインタを取得.
		/// </summary>
		constexpr value_type* end() noexcept
		{
#if __cpp_constexpr >= 201304
			return std::end(this->v);
#else  //! __cpp_constexpr >= 201304
			return std::end(reinterpret_cast<value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 要素の最後の次を示すポインタを取得.
		/// </summary>
		CONSTEXPR_CPP11 const value_type* end() const
		{
#if __cpp_constexpr >= 201304
			return std::end(this->v);
#else  //! __cpp_constexpr >= 201304
			return std::end(reinterpret_cast<const value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 代入演算子オーバーロード.
		/// </summary>
		Vector2& operator=(const Vector2&) = default;

		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>変換後の要素を返す.</returns>
		explicit operator value_type*(void)
		{
#if __cpp_constexpr >= 201304
			return this->v;
#else  //! __cpp_constexpr >= 201304
			return reinterpret_cast<value_type*>(this);
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>変換後の要素を返す.</returns>
		explicit operator const value_type*() const
		{
#if __cpp_constexpr >= 201304
			return this->v;
#else  //! __cpp_constexpr >= 201304
			return reinterpret_cast<const value_type*>(this);
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 要素アクセス演算子オーバーロード.
		/// </summary>
		/// <param name="_index">アクセスする要素.</param>
		/// <returns>アクセスした要素の参照.</returns>
		constexpr value_type& operator[](const size_type _index) noexcept
		{
#if __cpp_constexpr >= 201304
			return this->v[_index];
#else  //! __cpp_constexpr >= 201304
			return reinterpret_cast<value_array_type&>(*this)[_index];
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 要素アクセス演算子オーバーロード.
		/// </summary>
		/// <param name="_index">アクセスする要素.</param>
		/// <returns>アクセスした要素の参照.</returns>
		constexpr const value_type& operator[](const size_type _index) const noexcept
		{
#if __cpp_constexpr >= 201304
			return this->v[_index];
#else  //! __cpp_constexpr >= 201304
			return reinterpret_cast<const value_array_type&>(*this)[_index];
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 加算単行演算子オーバーロード.
		/// </summary>
		/// <returns>加算ベクトルを返す.</returns>
		constexpr Vector2 operator+() const& noexcept
		{
			return *this;
		}

		/// <summary>
		/// 加算単行演算子オーバーロード.
		/// </summary>
		/// <returns>加算ベクトルを返す.</returns>
		constexpr Vector2&& operator+() && noexcept
		{
			return std::move(*this);
		}

		/// <summary>
		/// 減算単行演算子オーバーロード.
		/// </summary>
		/// <returns>減算ベクトルを返す.</returns>
		constexpr Vector2 operator-() const& noexcept
		{
			return {-x, -y};
		}

		/// <summary>
		/// 減算単行演算子オーバーロード.
		/// </summary>
		/// <returns>減算ベクトルを返す.</returns>
		constexpr Vector2&& operator-() && noexcept
		{
			this->x = -x;
			this->y = -y;
			return std::move(*this);
		}

		/// <summary>
		/// 加算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">加算相手ベクトル.</param>
		/// <returns>加算後のベクトルを返す.</returns>
		constexpr Vector2& operator+=(const Vector2& other) noexcept
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		/// <summary>
		/// 減算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">減算相手ベクトル.</param>
		/// <returns>減算後のベクトルを返す.</returns>
		constexpr Vector2& operator-=(const Vector2& other) noexcept
		{
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">乗算相手ベクトル.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		constexpr Vector2& operator*=(const Vector2& other) noexcept
		{
			this->x *= other.x;
			this->y *= other.y;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">乗算相手ベクトル.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		constexpr Vector2& operator/=(const Vector2& other) noexcept
		{
			this->x /= other.x;
			this->y /= other.y;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="scale">スカラー値.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		constexpr Vector2& operator*=(value_type other) noexcept
		{
			this->x *= other;
			this->y *= other;
			return *this;
		}

		/// <summary>
		/// 除算代入演算子オーバーロード.
		/// </summary>
		/// <param name="scale">スカラー値.</param>
		/// <returns>除算後のベクトルを返す.</returns>
		constexpr Vector2& operator/=(value_type other) noexcept
		{
			return *this *= 1.f / other;
		}

		/// <summary>
		/// 加算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>加算後のベクトルを返す.</returns>
		constexpr Vector2&& operator+(const Vector2& right) && noexcept
		{
			return std::move(*this += right);
		}

		/// <summary>
		/// 加算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>加算後のベクトルを返す.</returns>
		constexpr Vector2 operator+(const Vector2& right) const& noexcept
		{
			return Vector2{this->x + right.x, this->y + right.y};
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>減算後のベクトルを返す.</returns>
		constexpr Vector2&& operator-(const Vector2& right) && noexcept
		{
			return std::move(*this -= right);
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>減算後のベクトルを返す.</returns>
		constexpr Vector2 operator-(const Vector2& right) const& noexcept
		{
			return {this->x - right.x, this->y - right.y};
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		constexpr Vector2&& operator*(const Vector2& right) && noexcept
		{
			return std::move(*this *= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		constexpr Vector2 operator*(const Vector2& right) const& noexcept
		{
			return {this->x * right.x, this->y * right.y};
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		constexpr Vector2&& operator*(value_type right) && noexcept
		{
			return std::move(*this *= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		constexpr Vector2 operator*(value_type right) const& noexcept
		{
			return {this->x * right, this->y * right};
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>乗算後のベクトルを返す.</returns>
		friend Vector2 operator*(value_type left, const Vector2& right) noexcept
		{
			return right * left;
		}

		friend Vector2 operator*(const Matrix33& M, const Vector2& v) noexcept;

		Vector2 operator*(const Matrix33& M) const noexcept;

		friend Vector2 operator*(const Matrix44& left, const Vector2& right);

		Vector2 operator*(const Matrix44& right) const;

		/// <summary>
		/// 等価2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <param name="v2">ベクトル2.</param>
		/// <returns>要素が違っていれば真を返す.</returns>
		constexpr bool operator==(const Vector2& right) const noexcept
		{
			return this->x == right.x && this->y == right.y;
		}

		/// <summary>
		/// 非等価2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <param name="v2">ベクトル2.</param>
		/// <returns>要素が違っていれば真を返す.</returns>
		constexpr bool operator!=(const Vector2& right) const noexcept
		{
			return !(*this == right);
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <param name="v2">ベクトル2.</param>
		/// <returns>要素2より大きければ真を返す.</returns>
		constexpr bool operator<(const Vector2& right) const noexcept
		{
			return (this->x < right.x) && (this->y < right.y);
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <param name="v2">ベクトル2.</param>
		/// <returns>要素2より小さければ真を返す.</returns>
		constexpr bool operator>(const Vector2& right) const noexcept
		{
			return (this->x > right.x) && (this->y > right.y);
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <param name="v2">ベクトル2.</param>
		/// <returns>要素2以下なら真を返す.</returns>
		constexpr bool operator<=(const Vector2& right) const noexcept
		{
			return !(*this > right);
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="v1">ベクトル1.</param>
		/// <param name="v2">ベクトル2.</param>
		/// <returns>要素2以上なら真を返す.</returns>
		constexpr bool operator>=(const Vector2& right) const noexcept
		{
			return !(*this < right);
		}

	}; //! struct Vector2

} // namespace bavil::math

#pragma warning(pop)
