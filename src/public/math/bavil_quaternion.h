#pragma once

#include "bavil_type.h"
#include "math/bavil_math_function.h"
#include "math/bavil_math_def.h"
#include "math/bavil_vector3.h"

namespace bavil::math
{
	struct Matrix33;
	struct Matrix44;

	/// <summary>
	/// クオータニオン.
	/// </summary>
	struct Quaternion
	{
		using value_type   = f32;
		using size_type    = u32;
		using vector3_type = Vector3;

	public:
#pragma warning(push)
#pragma warning(disable : 4201) // 無名構造体・無名共有体の利用
		union
		{
			struct
			{
				/// <summary>
				/// x成分.
				/// </summary>
				value_type x;
				/// <summary>
				/// y成分.
				/// </summary>
				value_type y;
				/// <summary>
				/// z成分.
				/// </summary>
				value_type z;
				/// <summary>
				/// w成分.
				/// </summary>
				value_type w;
			};
			/// <summary>
			/// XYZW成分.
			/// </summary>
			value_type v[4];
		};
#pragma warning(pop)
	public:
		/// <summary>
		/// 単位クォータニオン.
		/// </summary>
		static const Quaternion IDENTITY;
		/// <summary>
		/// 全てがゼロで初期化されたクォータニオン.
		/// </summary>
		static const Quaternion EMPTY;
	public:
		/// <summary>
		/// デフォルトコンストラクタ.
		/// </summary>
		constexpr Quaternion() noexcept
		    : x()
		    , y()
		    , z()
		    , w()
		{
		}

		/// <summary>
		/// 初期化無しコンストラクタ.
		/// </summary>
		explicit Quaternion(none_init_t) noexcept {}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="_x">X成分.</param>
		/// <param name="_y">Y成分.</param>
		/// <param name="_z">Z成分.</param>
		/// <param name="_w">W成分.</param>
		constexpr Quaternion(value_type _x,
		                     value_type _y,
		                     value_type _z,
		                     value_type _w) noexcept
		    : x(_x)
		    , y(_y)
		    , z(_z)
		    , w(_w)
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="axis">回転軸.</param>
		/// <param name="angle">角度.</param>
		 Quaternion(const vector3_type& axis, Radian angle) noexcept
		{
			value_type sin = Sin(angle / 2.0f);
			*this          = Quaternion{
                sin * axis.x, sin * axis.y, sin * axis.z, Cos(angle / 2.0f)};
		}

		/// <summary>
		/// 単位クォータニオン化する.
		/// </summary>
		/// <returns>単位クォータニオンを返す.</returns>
		constexpr Quaternion& identity(void) noexcept
		{
			return *this = Quaternion::IDENTITY;
		}

		/// <summary>
		/// 内積を求める.
		/// </summary>
		/// <param name="other">対象クォータニオン</param>
		/// <returns>内積を返す.</returns>
		constexpr value_type dot(const Quaternion& _other) const noexcept
		{
			return this->x * _other.x + this->y * _other.y + this->z * _other.z +
			       this->w * _other.w;
		}

		/// <summary>
		/// ノルムを求める.(2乗和のみ)
		/// </summary>
		/// <returns>長さを返す.</returns>
		value_type length_sqr() const noexcept
		{
			return this->dot(*this);
		}

		/// <summary>
		/// ノルムを求める.(長さ)
		/// </summary>
		/// <returns>長さを返す.</returns>
		value_type length() const noexcept
		{
			return std::sqrt(this->length_sqr());
		}

		/// <summary>
		/// 正規化する.
		/// </summary>
		/// <returns>正規化後のクォータニオンを返す.</returns>
		Quaternion& normalize() noexcept
		{
			return *this /= std::sqrt(this->length_sqr());
		}

		/// <summary>
		/// 正規化する.
		/// </summary>
		/// <returns>正規化後のクォータニオンを返す.</returns>
		Quaternion& safe_normalize() noexcept
		{
			if ( const value_type len = this->length_sqr() )
			{
				*this /= std::sqrt(len);
			}
			return *this;
		}

		/// <summary>
		/// 正規化後のクォータニオンを取得.
		/// </summary>
		/// <returns>正規化後のクォータニオンを返す.</returns>
		Quaternion get_normalize() const noexcept
		{
			return Quaternion(*this).normalize();
		}

		/// <summary>
		/// 逆クォータニオン化する.
		/// </summary>
		/// <returns>逆クォータニオンを返す.</returns>
		Quaternion& inverse() noexcept
		{
			value_type l = this->length();
			l            = (l > 0.0f) ? (1.0f / l) : 0.0f;

			this->x = -this->x * l;
			this->y = -this->y * l;
			this->z = -this->z * l;
			this->w = this->w * l;

			return *this;
		}

		/// <summary>
		/// 逆クォータニオン後のクォータニオンを取得.
		/// </summary>
		/// <returns>逆クォータニオンを返す.</returns>
		Quaternion get_inverse() const&
		{
			return Quaternion(*this).inverse();
		}

		/// <summary>
		/// 逆クォータニオン後のクォータニオンを取得.
		/// </summary>
		/// <returns>逆クォータニオンを返す.</returns>
		Quaternion&& get_inverse() &&
		{
			return std::move(this->inverse());
		}

		/// <summary>
		/// 回転角度からクォータニオンを設定.
		/// </summary>
		/// <param name="angle">角度</param>
		/// <param name="_x">X軸</param>
		/// <param name="_y">Y軸</param>
		/// <param name="_z">Z軸</param>
		Quaternion& set_rotate(Radian           angle,
		                       const value_type _x,
		                       const value_type _y,
		                       const value_type _z)
		{
			return *this = Quaternion{Vector3(_x, _y, _z), angle};
		}

		/// <summary>
		/// 回転角度からクォータニオンを設定.
		/// </summary>
		/// <param name="radian">角度</param>
		/// <param name="axis">軸</param>
		Quaternion& set_rotate(Radian radian, const Vector3& axis)
		{
			return *this = Quaternion(axis, radian);
		}

		/// <summary>
		/// 回転角度からクォータニオンを設定.
		/// </summary>
		/// <param name="yaw">ヨー</param>
		/// <param name="pitch">ピッチ</param>
		/// <param name="roll">ロール</param>
		Quaternion& set_rotate_yaw_pitch_roll(Radian yaw,
		                                      Radian pitch,
		                                      Radian roll) noexcept
		{
			const value_type sin_yaw   = Sin(yaw / 2.0f);
			const value_type sin_pitch = Sin(pitch / 2.0f);
			const value_type sin_roll  = Sin(roll / 2.0f);
			const value_type cos_yaw   = Cos(yaw / 2.0f);
			const value_type cos_pitch = Cos(pitch / 2.0f);
			const value_type cos_roll  = Cos(roll / 2.0f);

			this->x =
			    sin_roll * cos_pitch * cos_yaw - cos_roll * sin_pitch * sin_yaw;
			this->y =
			    cos_roll * sin_pitch * cos_yaw + sin_roll * cos_pitch * sin_yaw;
			this->z =
			    cos_roll * cos_pitch * sin_yaw - sin_roll * sin_pitch * cos_yaw;
			this->w =
			    cos_roll * cos_pitch * cos_yaw + sin_roll * sin_pitch * sin_yaw;

			return *this;
		}

		/// <summary>
		/// 回転行列を設定.
		/// </summary>
		/// <param name="m">回転行列.</param>
		/// <returns>クォータニオンを返す.</returns>
		Quaternion& set_matrix(Matrix44 const& m);

		/// <summary>
		/// 軸の取得.
		/// </summary>
		/// <returns>回転軸を返す.</returns>
		Vector3 get_axis() const noexcept
		{
			const value_type angle = std::acos(this->w) * 2.0f;
			return Vector3(this->x / std::sin(angle / 2.0f),
			               this->y / std::sin(angle / 2.0f),
			               this->z / std::sin(angle / 2.0f));
		}

		/// <summary>
		/// 角度の取得.
		/// </summary>
		/// <returns>角度を返す.</returns>
		value_type get_angle() const noexcept
		{
			return std::acos(w) * 2.0f;
		}

		/// <summary>
		/// ヨーの取得.
		/// </summary>
		/// <returns>ヨー値を返す.</returns>
		value_type get_yaw() const noexcept
		{
			return std::asin(-2.0f * (x * z - w * y));
		}

		/// <summary>
		/// ピッチの取得.
		/// </summary>
		/// <returns>ピッチ値を返す.</returns>
		value_type get_pitch() const noexcept
		{
			return std::atan2(2.0f * (y * z + w * x), w * w - x * x - y * y + z * z);
		}

		/// <summary>
		/// ロールの取得.
		/// </summary>
		/// <returns>ロール値を返す.</returns>
		value_type get_roll(void) const noexcept
		{
			return std::atan2(2.0f * (x * y + w * z), w * w + x * x - y * y - z * z);
		}

		/// <summary>
		/// クオータニオンから回転行列に変換.
		/// </summary>
		/// <returns>回転行列を返す.</returns>
		Matrix44 rotate() const noexcept;

		/// <summary>
		/// ベクトルを回転させる.
		/// </summary>
		/// <param name="target">回転させるベクトル.</param>
		/// <returns>回転後のベクトルを返す.</returns>
		Vector3 rotate(const Vector3& target) const noexcept
		{
			const value_type tmp_x =
			    (this->w * target.x) + (this->y * target.z) - (this->z * target.y);
			const value_type tmp_y =
			    (this->w * target.y) + (this->z * target.x) - (this->x * target.z);
			const value_type tmp_z =
			    (this->w * target.z) + (this->x * target.y) - (this->y * target.x);
			const value_type tmp_w =
			    (this->x * target.x) + (this->y * target.y) + (this->z * target.z);
			return {(tmp_w * this->x) + (tmp_x * this->w) - (tmp_y * this->z) +
			            (tmp_z * this->y),
			        (tmp_w * this->y) + (tmp_y * this->w) - (tmp_z * this->x) +
			            (tmp_x * this->z),
			        (tmp_w * this->z) + (tmp_z * this->w) - (tmp_x * this->y) +
			            (tmp_y * this->x)};
		}

	public:
		/// <summary>
		/// 要素の先頭を示すポインタを取得.
		/// </summary>
		value_type* begin() noexcept
		{
			return std::begin(this->v);
		}

		/// <summary>
		/// 要素の先頭を示すポインタを取得.
		/// </summary>
		value_type const* begin() const noexcept
		{
			return std::begin(this->v);
		}
		/// <summary>
		/// 要素の最後の次を示すポインタを取得.
		/// </summary>
		value_type* end() noexcept
		{
			return std::end(this->v);
		}

		/// <summary>
		/// 要素の最後の次を示すポインタを取得.
		/// </summary>
		value_type const* end() const noexcept
		{
			return std::end(this->v);
		}

	public:
		/// <summary>
		/// 回転行列からクォータニオンを作成.
		/// </summary>
		/// <param name="m">回転行列.</param>
		static Quaternion Rotation(Matrix33 const& m);

		/// <summary>
		/// 回転行列からクォータニオンを作成.
		/// </summary>
		/// <param name="m">回転行列.</param>
		static Quaternion Rotation(Matrix44 const& m);

		/// <summary>
		/// X軸からクォータニオンを求める.
		/// </summary>
		/// <param name="radians">ラジアン.</param>
		/// <returns>作成したクォータニオンを返す.</returns>
		static Quaternion RotationX(value_type radians)
		{
			const value_type angle = (radians * 0.5f);
			return {std::sin(angle), 0.0f, 0.0f, std::cos(angle)};
		}

		/// <summary>
		/// Y軸からクォータニオンを求める.
		/// </summary>
		/// <param name="radians">ラジアン.</param>
		/// <returns>作成したクォータニオンを返す.</returns>
		static Quaternion RotationY(value_type radians)
		{
			const value_type angle = (radians * 0.5f);
			return {0.0f, std::sin(angle), 0.0f, std::cos(angle)};
		}

		/// <summary>
		/// Z軸からクォータニオンを求める.
		/// </summary>
		/// <param name="radians">ラジアン.</param>
		/// <returns>作成したクォータニオンを返す.</returns>
		static Quaternion RotationZ(value_type radians)
		{
			value_type angle = (radians * 0.5f);
			return Quaternion(0.0f, 0.0f, std::sin(angle), std::cos(angle));
		}

		/// <summary>
		/// 任意軸周りの回転行列を求める.
		/// </summary>
		/// <param name="axis">任意軸.</param>
		/// <param name="angle">角度.</param>
		/// <returns>回転行列を返す.</returns>
		static Matrix44 Rotate(const Vector3& axis, Radian angle);

		/// <summary>
		/// 線形補完.
		/// </summary>
		/// <param name="start">開始クォータニオン.</param>
		/// <param name="end">終了クォータニオン.</param>
		/// <param name="amount">補完係数<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		/// <returns>補間後のクォータニオン.</returns>
		static Quaternion Lerp(const Quaternion& start,
		                       const Quaternion& end,
		                       value_type        amount)
		{
			Quaternion result;
			result.x = math::Lerp(start.x, end.x, amount);
			result.y = math::Lerp(start.y, end.y, amount);
			result.z = math::Lerp(start.z, end.z, amount);
			result.w = math::Lerp(start.w, end.w, amount);

			return result.normalize();
		}

		/// <summary>
		/// 球面線形補完.
		/// </summary>
		/// <param name="start">開始クォータニオン.</param>
		/// <param name="end">終了クォータニオン.</param>
		/// <param name="amount">補完係数<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		/// <returns>補間後のクォータニオン.</returns>
		static Quaternion Slerp(Quaternion const& start,
		                        Quaternion const& end,
		                        value_type        amount)
		{
			value_type cos = start.dot(end);
			auto       t2  = end;
			if ( cos < 0.0f )
			{
				cos = -cos;
				t2  = -end;
			}
			value_type k0 = 1.0f - amount;
			value_type k1 = amount;
			if ( (1.0f - cos) > 0.001f )
			{
				value_type theta = std::acos(cos);
				k0               = std::sin(theta * k0) / std::sin(theta);
				k1               = std::sin(theta * k1) / std::sin(theta);
			}

			return start * k0 + t2 * k1;
		}

	public:
		/// <summary>
		/// 加算単項演算子オーバーロード.
		/// </summary>
		Quaternion operator+(void) const& noexcept
		{
			return Quaternion{*this};
		}

		/// <summary>
		/// 加算単項演算子オーバーロード.
		/// </summary>
		Quaternion&& operator+(void) && noexcept
		{
			return std::move(*this);
		}

		/// <summary>
		/// 減算単項演算子オーバーロード.
		/// </summary>
		Quaternion operator-(void) const& noexcept
		{
			return {-this->x, -this->y, -this->z, -this->w};
		}

		/// <summary>
		/// 減算単項演算子オーバーロード.
		/// </summary>
		Quaternion&& operator-(void) && noexcept
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
		/// <param name="other">加算相手.</param>
		/// <returns>加算後の参照を返す.</returns>
		Quaternion& operator+=(const Quaternion& other) noexcept
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;
			return *this;
		}

		/// <summary>
		/// 減算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">加算相手.</param>
		/// <returns>減算後の参照を返す.</returns>
		Quaternion& operator-=(const Quaternion& other) noexcept
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			this->w -= other.w;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">加算相手.</param>
		/// <returns>乗算後の参照を返す.</returns>
		Quaternion& operator*=(const Quaternion& other) noexcept
		{
			return *this = Quaternion{this->x * other.w + this->y * other.z -
			                              this->z * other.y + this->w * other.x,
			                          -this->x * other.z + this->y * other.w +
			                              this->z * other.x + this->w * other.y,
			                          this->x * other.y - this->y * other.x +
			                              this->z * other.w + this->w * other.z,
			                          -this->x * other.x - this->y * other.y -
			                              this->z * other.z + this->w * other.w};
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="scale">スケール値.</param>
		/// <returns>乗算後の参照を返す.</returns>
		Quaternion& operator*=(value_type scale) noexcept
		{
			this->x *= scale;
			this->y *= scale;
			this->z *= scale;
			this->w *= scale;
			return *this;
		}

		/// <summary>
		/// 除算代入演算子オーバーロード.
		/// </summary>
		/// <param name="scale">スケール値.</param>
		/// <returns>除算後の参照を返す.</returns>
		Quaternion& operator/=(value_type scale)
		{
			return *this *= 1.0f / scale;
		}

		/// <summary>
		/// 加算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>加算後のクォータニオンを返す.</returns>
		Quaternion operator+(const Quaternion& right) const& noexcept
		{
			return {this->x + right.x,
			        this->y + right.y,
			        this->z + right.z,
			        this->w + right.w};
		}

		/// <summary>
		/// 加算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>加算後のクォータニオンを返す.</returns>
		Quaternion&& operator+(const Quaternion& right) && noexcept
		{
			return std::move(*this += right);
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>減算後のクォータニオンを返す.</returns>
		Quaternion operator-(const Quaternion& right) const& noexcept
		{
			return {this->x - right.x,
			        this->y - right.y,
			        this->z - right.z,
			        this->w - right.w};
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>減算後のクォータニオンを返す.</returns>
		Quaternion&& operator-(const Quaternion& right) && noexcept
		{
			return std::move(*this -= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>乗算後のクォータニオンを返す.</returns>
		Quaternion operator*(const Quaternion& right) const& noexcept
		{
			return {this->x * right.x,
			        this->y * right.y,
			        this->z * right.z,
			        this->w * right.w};
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>乗算後のクォータニオンを返す.</returns>
		Quaternion&& operator*(const Quaternion& right) && noexcept
		{
			return std::move(*this *= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>乗算後のクォータニオンを返す.</returns>
		constexpr Quaternion operator*(value_type _right) const& noexcept
		{
			return Quaternion{this->x * _right,
			                  this->y * _right,
			                  this->z * _right,
			                  this->w * _right};
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>乗算後のクォータニオンを返す.</returns>
		Quaternion&& operator*(value_type right) && noexcept
		{
			return std::move(*this *= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="scale">スケール値.</param>
		/// <param name="q">クォータニオン.</param>
		/// <returns>乗算後のクォータニオンを返す.</returns>
		friend Quaternion operator*(value_type        left,
		                            const Quaternion& right) noexcept
		{
			return right * left;
		}

		/// <summary>
		/// 除算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>除算後のクォータニオンを返す.</returns>
		Quaternion operator/(value_type right) const&
		{
			return {
			    this->x / right, this->y / right, this->z / right, this->w / right};
		}

		/// <summary>
		/// 除算2項演算子オーバーロード.
		/// </summary>
		/// <param name="_scale">右辺値.</param>
		/// <returns>除算後のクォータニオンを返す.</returns>
		Quaternion&& operator/(value_type _scale) &&
		{
			return std::move(*this /= _scale);
		}

		/// <summary>
		/// 比較演算子オーバーロード.
		/// </summary>
		/// <param name="_right">右辺値.</param>
		/// <returns>等しいなら真を返す.</returns>
		constexpr bool operator==(const Quaternion& _right) const noexcept
		{
			return this->x == _right.x && this->y == _right.y &&
			       this->z == _right.z && this->w == _right.w;
		}

		/// <summary>
		/// 比較演算子オーバーロード.
		/// </summary>
		/// <param name="_right">右辺値.</param>
		/// <returns>等しいなら真を返す.</returns>
		constexpr bool operator!=(const Quaternion& _right) const noexcept
		{
			return !(*this == _right);
		}
	};

} // namespace bavil::math
