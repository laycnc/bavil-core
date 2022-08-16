#pragma once

#include "bavil_type.h"
#include "math/bavil_math_def.h"
#include "math/bavil_math_function.h"
#include "math/bavil_vector2.h"
#include "math/bavil_vector3.h"

namespace bavil::math
{

	struct Quaternion;

	/// <summary>
	/// 3行3列座標変換マトリクス構造体.
	/// </summary>
	struct Matrix33
	{
		using value_type = f32;
		using size_type  = u32;
	public:
#pragma warning(push)
#pragma warning(disable : 4201) // 無名構造体・無名共有体の利用
		union
		{
#if 0
			struct
			{
				/// <summary>X軸.</summary>
				Vector3	xaxis;
				/// <summary>Y軸.</summary>
				Vector3	yaxis;
				/// <summary>Z軸.</summary>
				Vector3	zaxis;
			};
#endif
			struct
			{
				/// <summary>X軸.</summary>
				value_type _11, _12, _13;

				/// <summary>Y軸.</summary>
				value_type _21, _22, _23;

				/// <summary>Z軸.</summary>
				value_type _31, _32, _33;
			};
			/// <summary>
			/// ３行３列の行列.
			/// </summary>
			value_type m[3][3];

			/// <summary>
			/// ３行３列の行列.
			/// </summary>
			value_type v[9];
		};
#pragma warning(pop)

	public:
		/// <summary>
		/// 単位行列.
		/// </summary>
		static const Matrix33 IDENTITY;
		/// <summary>
		/// 全てがゼロで初期化された行列.
		/// </summary>
		static const Matrix33 EMPTY;
	public:
		/// <summary>
		/// デフォルトコンストラクタ.
		/// </summary>
		Matrix33() noexcept
		    : Matrix33{1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f}
		{
		}

		/// <summary>
		/// 初期化無しコンストラクタ.
		/// </summary>
		explicit Matrix33(none_init_t) noexcept {}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="_array">配列.</param>
		explicit Matrix33(value_type const* _array) noexcept
		    : Matrix33{_array[0],
		               _array[1],
		               _array[2],
		               _array[3],
		               _array[4],
		               _array[5],
		               _array[6],
		               _array[7],
		               _array[8]}
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="m11">1行1列成分</param>
		/// <param name="m12">1行2列成分</param>
		/// <param name="m13">1行3列成分</param>
		/// <param name="m21">2行1列成分</param>
		/// <param name="m22">2行2列成分</param>
		/// <param name="m23">2行3列成分</param>
		/// <param name="m31">3行1列成分</param>
		/// <param name="m32">3行2列成分</param>
		/// <param name="m33">3行3列成分</param>
		Matrix33(value_type m11,
		         value_type m12,
		         value_type m13,
		         value_type m21,
		         value_type m22,
		         value_type m23,
		         value_type m31,
		         value_type m32,
		         value_type m33)
		    : _11{m11}
		    , _12{m12}
		    , _13{m13}
		    , _21{m21}
		    , _22{m22}
		    , _23{m23}
		    , _31{m31}
		    , _32{m32}
		    , _33{m33}
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// <para>３行３列座標変換マトリクス構造体の新規作成.</para>
		/// </summary>
		/// <param name="axisX">X軸</param>
		/// <param name="axisY">Y軸</param>
		/// <param name="axisZ">Z軸</param>
		Matrix33(const Vector3& axisX, const Vector3& axisY, const Vector3& axisZ)
		    : Matrix33{axisX.x,
		               axisX.y,
		               axisX.z,
		               axisY.x,
		               axisY.y,
		               axisY.z,
		               axisZ.x,
		               axisZ.y,
		               axisZ.z}
		{
		}

		/// <summary>
		/// 単位行列化する.
		/// </summary>
		/// <returns>単位行列化した行列の参照を返す.</returns>
		Matrix33& identity() noexcept
		{
			return *this = Matrix33::IDENTITY;
		}

		/// <summary>
		/// 逆行列にする.
		/// </summary>
		/// <returns>逆行列化した行列の参照を返す.</returns>
		Matrix33& inverse()
		{
			Matrix33 m;

			m._11 = this->_22 * this->_33 - this->_23 * this->_32;
			m._12 = this->_13 * this->_32 - this->_12 * this->_33;
			m._13 = this->_12 * this->_23 - this->_13 * this->_22;
			m._21 = this->_23 * this->_31 - this->_21 * this->_33;
			m._22 = this->_11 * this->_33 - this->_13 * this->_31;
			m._23 = this->_13 * this->_21 - this->_11 * this->_23;
			m._31 = this->_21 * this->_32 - this->_22 * this->_31;
			m._32 = this->_12 * this->_31 - this->_11 * this->_32;
			m._33 = this->_11 * this->_22 - this->_12 * this->_21;

			const value_type fdet =
			    this->_11 * m._11 + this->_12 * m._21 + this->_13 * m._31;

			if ( fdet == 0.0 )
			{
				// 逆行列を求める事ができない.
				return *this = Matrix33::IDENTITY;
			}

			value_type f_Inv_det = 1.0f / fdet;
			m *= f_Inv_det;

			return *this = m;
		}

		/// <summary>
		/// 転置行列にする.
		/// </summary>
		/// <returns>転置行列化した行列の参照を返す.</returns>
		Matrix33& transpose() noexcept
		{
			Matrix33 m;

			/* マトリクスの行と列を交換する */
			m._11 = this->_11;
			m._21 = this->_12;
			m._31 = this->_13;

			m._12 = this->_21;
			m._22 = this->_22;
			m._32 = this->_23;

			m._13 = this->_31;
			m._23 = this->_32;
			m._33 = this->_33;

			*this = m;
			return *this;
		}

		/// <summary>
		/// 転置逆行列にする.
		/// </summary>
		/// <returns>転置逆行列化した行列の参照を返す.</returns>
		Matrix33& inverse_transpose()
		{
			return this->inverse().transpose();
		}

		/// <summary>
		/// 逆行列を取得.
		/// </summary>
		/// <returns>逆行列を返す.</returns>
		Matrix33 get_inverse() const
		{
			return Matrix33(*this).inverse();
		}

		/// <summary>
		/// 転置行列を取得.
		/// </summary>
		/// <returns>転置行列を返す.</returns>
		Matrix33 get_transpose() const
		{
			return Matrix33(*this).transpose();
		}

		/// <summary>
		/// 転置逆行列を取得.
		/// </summary>
		/// <returns>転置逆行列を返す.</returns>
		Matrix33 get_inverse_transpose() const
		{
			return Matrix33(*this).inverse_transpose();
		}

		/// <summary>
		/// 拡大縮小行列を乗算.
		/// </summary>
		/// <param name="x">X成分.</param>
		/// <param name="y">Y成分.</param>
		/// <param name="z">Z成分.</param>
		/// <returns>拡大後の行列の参照を返す.</returns>
		Matrix33& scale(value_type x, value_type y, value_type z)
		{
			return *this *= Matrix33(none_init_v).set_scale(x, y, z);
		}

		/// <summary>
		/// 拡大縮小行列を乗算.
		/// </summary>
		/// <param name="scaleFactor">スケール値.</param>
		/// <returns>拡大後の行列の参照を返す.</returns>
		Matrix33& scale(const Vector3& scaleFactor)
		{
			return this->scale(scaleFactor.x, scaleFactor.y, scaleFactor.z);
		}

		/// <summary>
		/// 拡大縮小行列を乗算.
		/// </summary>
		/// <param name="scaleFactor">スケール値.</param>
		/// <returns>拡大後の行列の参照を返す.</returns>
		Matrix33& scale(value_type scaleFactor)
		{
			return this->scale(scaleFactor, scaleFactor, scaleFactor);
		}

		/// <summary>
		/// 行列を回転させる.
		/// </summary>
		/// <param name="radian">角度.</param>
		/// <param name="axisX">X軸成分.</param>
		/// <param name="axisY">Y軸成分.</param>
		/// <param name="axisZ">Z軸成分.</param>
		/// <returns>回転後の行列を返す.</returns>
		Matrix33& rotate(Radian     radian,
		                 value_type axisX,
		                 value_type axisY,
		                 value_type axisZ)
		{
			return *this *=
			       Matrix33(none_init_v).set_rotation(radian, axisX, axisY, axisZ);
		}

		/// <summary>
		/// 行列を回転させる.
		/// </summary>
		/// <param name="radian">角度.</param>
		/// <param name="axis">軸成分.</param>
		/// <returns>回転後の行列を返す.</returns>
		Matrix33& rotate(Radian radian, const Vector3& axis)
		{
			return this->rotate(radian, axis.x, axis.y, axis.z);
		}

		/// <summary>
		/// 行列を回転させる.
		/// </summary>
		/// <param name="q">クォータニオン.</param>
		/// <returns>回転後の行列を返す.</returns>
		Matrix33& rotate(const Quaternion& q)
		{
			return *this *= Matrix33::Rotate(q);
		}

		/// <summary>
		/// 行列のX軸を回転させる.
		/// </summary>
		/// <param name="degree">角度.</param>
		/// <returns>回転後の行列を返す.</returns>
		Matrix33& rotate_x(Radian radian) noexcept
		{
			return *this *= Matrix33{none_init_v}.set_rotation_x(radian);
		}

		/// <summary>
		/// 行列のY軸を回転させる.
		/// </summary>
		/// <param name="degree">角度.</param>
		/// <returns>回転後の行列を返す.</returns>
		Matrix33& rotate_y(Radian radian) noexcept
		{
			return *this *= Matrix33{none_init_v}.set_rotation_y(radian);
		}

		/// <summary>
		/// 行列のZ軸を回転させる.
		/// </summary>
		/// <param name="degree">角度.</param>
		/// <returns>回転後の行列を返す.</returns>
		Matrix33& rotate_z(Radian radian) noexcept
		{
			return *this *= Matrix33{none_init_v}.set_rotation_z(radian);
		}

		/// <summary>
		/// 行列を回転させる.
		/// </summary>
		/// <param name="yaw">ヨー.</param>
		/// <param name="pitch">ピッチ.</param>
		/// <param name="roll">ロール.</param>
		/// <returns>回転後の行列を返す.</returns>
		Matrix33& rotate_yaw_pitch_roll(Radian yaw,
		                                Radian pitch,
		                                Radian roll) noexcept
		{
			return *this *= Matrix33{none_init_v}.set_rotation_yaw_pitch_roll(
			           yaw, pitch, roll);
		}

		/// <summary>
		/// 行列を平行移動.
		/// </summary>
		/// <param name="x">X成分.</param>
		/// <param name="y">Y成分.</param>
		Matrix33& translate(value_type x, value_type y) noexcept
		{
			return *this *= Matrix33{none_init_v}.set_translation(x, y);
		}

		/// <summary>
		/// 行列を平行移動.
		/// </summary>
		/// <param name="translation">2次元ベクトル.</param>
		Matrix33& translate(const Vector2& translation)
		{
			return this->translate(translation.x, translation.y);
		}

		/// <summary>
		/// スケール値の設定.
		/// </summary>
		/// <param name="x">X成分.</param>
		/// <param name="y">Y成分.</param>
		/// <param name="z">Z成分.</param>
		Matrix33& set_scale(value_type x, value_type y, value_type z)
		{
			this->_11 = x;
			this->_12 = 0.f;
			this->_13 = 0.f;

			this->_21 = 0.f;
			this->_22 = y;
			this->_23 = 0.f;

			this->_31 = 0.f;
			this->_32 = 0.f;
			this->_33 = z;
			return *this;
		}

		/// <summary>
		/// スケール値の設定.
		/// </summary>
		/// <param name="scaleFactor">スケール値.</param>
		Matrix33& set_scale(const Vector3& scaleFactor)
		{
			return this->set_scale(scaleFactor.x, scaleFactor.y, scaleFactor.z);
		}

		/// <summary>
		/// スケール値の設定.
		/// </summary>
		/// <param name="scaleFactor">スケール値.</param>
		Matrix33& set_scale(value_type scaleFactor)
		{
			return this->set_scale(scaleFactor, scaleFactor, scaleFactor);
		}

		/// <summary>
		/// 回転角度の設定.
		/// </summary>
		/// <param name="radian">角度.</param>
		/// <param name="axisX">X軸.</param>
		/// <param name="axisY">Y軸.</param>
		/// <param name="axisZ">Z軸.</param>
		Matrix33& set_rotation(Radian     radian,
		                       value_type axisX,
		                       value_type axisY,
		                       value_type axisZ)
		{
			const value_type sin_angle           = Sin(radian);
			const value_type cos_angle           = Cos(radian);
			const value_type one_minus_cos_angle = 1.0f - cos_angle;

			if ( const value_type len =
			         std::sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ) )
			{
				axisX *= (1.f / len);
				axisY *= (1.f / len);
				axisZ *= (1.f / len);
			}

			this->_11 = (axisX * axisX) + cos_angle * (1.0f - (axisX * axisX));
			this->_21 = (axisX * axisY) * one_minus_cos_angle - sin_angle * axisZ;
			this->_31 = (axisX * axisZ) * one_minus_cos_angle + sin_angle * axisY;

			this->_12 = (axisX * axisY) * one_minus_cos_angle + sin_angle * axisZ;
			this->_22 = (axisY * axisY) + cos_angle * (1.0f - (axisY * axisY));
			this->_32 = (axisY * axisZ) * one_minus_cos_angle - sin_angle * axisX;

			this->_13 = (axisX * axisZ) * one_minus_cos_angle - sin_angle * axisY;
			this->_23 = (axisY * axisZ) * one_minus_cos_angle + sin_angle * axisX;
			this->_33 = (axisZ * axisZ) + cos_angle * (1.0f - (axisZ * axisZ));

			return *this;
		}

		/// <summary>
		/// 回転角度の設定.
		/// </summary>
		/// <param name="radian">角度.</param>
		/// <param name="axis">軸.</param>
		Matrix33& set_rotation(Radian radian, const Vector3& axis) noexcept
		{
			return this->set_rotation(radian, axis.x, axis.y, axis.z);
		}

		/// <summary>
		/// 回転角度の設定.
		/// </summary>
		/// <param name="q">クォータニオン.</param>
		Matrix33& set_rotation(const Quaternion& q)
		{
			return *this = Matrix33::Rotate(q);
		}

		/// <summary>
		/// X軸の回転角度の設定.
		/// </summary>
		/// <param name="radian">角度.</param>
		Matrix33& set_rotation_x(Radian radian) noexcept
		{
			this->_11 = 1.0f;
			this->_12 = 0.0f;
			this->_13 = 0.0f;

			this->_21 = 0.0f;

			this->_31 = 0.0f;

			this->_22 = Cos(radian);
			this->_23 = Sin(radian);
			this->_32 = -this->_23;
			this->_33 = this->_22;

			return *this;
		}

		/// <summary>
		/// Y軸の回転角度の設定.
		/// </summary>
		/// <param name="radian">角度.</param>
		Matrix33& set_rotation_y(Radian radian) noexcept
		{
			this->_12 = 0.0f;

			this->_21 = 0.0f;
			this->_22 = 1.0f;
			this->_23 = 0.0f;

			this->_32 = 0.0f;

			this->_11 = Cos(radian);
			this->_31 = Sin(radian);
			this->_13 = -this->_31;
			this->_33 = this->_11;

			return *this;
		}

		/// <summary>
		/// Z軸の回転角度の設定.
		/// </summary>
		/// <param name="radian">角度.</param>
		Matrix33& set_rotation_z(Radian radian) noexcept
		{
			this->_13 = 0.0f;

			this->_23 = 0.0f;

			this->_31 = 0.0f;
			this->_32 = 0.0f;
			this->_33 = 1.0f;

			this->_11 = Cos(radian);
			this->_12 = Sin(radian);
			this->_21 = -this->_12;
			this->_22 = this->_11;

			return *this;
		}

		/// <summary>
		/// 回転角度の設定.
		/// </summary>
		/// <param name="yaw">ヨー.</param>
		/// <param name="pitch">ピッチ.</param>
		/// <param name="roll">ロール.</param>
		Matrix33& set_rotation_yaw_pitch_roll(Radian yaw, Radian pitch, Radian roll)
		{
			// ロール，ピッチ，ヨーから回転マトリクスを求める.
			*this = Matrix33{none_init_v}.set_rotation_z(roll) *
			        Matrix33{none_init_v}.set_rotation_x(pitch) *
			        Matrix33{none_init_v}.set_rotation_y(yaw);

			return *this;
		}

		/// <summary>
		/// 平行移動量の設定.
		/// </summary>
		/// <param name="x">X成分.</param>
		/// <param name="y">Y成分.</param>
		Matrix33& set_translation(value_type x, value_type y)
		{
			this->_11 = 1.f;
			this->_12 = 0.f;
			this->_13 = 0.f;

			this->_21 = 0.f;
			this->_22 = 1.f;
			this->_23 = 0.f;

			this->_31 = x;
			this->_32 = y;
			this->_33 = 1.f;

			return *this;
		}

		/// <summary>
		/// 平行移動量の設定.
		/// </summary>
		/// <param name="translation">平行移動量.</param>
		Matrix33& set_translation(const Vector2& translation)
		{
			return this->set_translation(translation.x, translation.y);
		}

		/// <summary>
		/// X軸，位置の設定.
		/// </summary>
		/// <param name="axisX">X軸成分.</param>
		Matrix33& set_axis_x(const Vector3& axisX) noexcept
		{
			this->_11 = axisX.x;
			this->_12 = axisX.y;
			this->_13 = axisX.z;
			return *this;
		}

		/// <summary>
		/// Y軸，位置の設定.
		/// </summary>
		/// <param name="axisY">Y軸成分.</param>
		Matrix33& set_axis_y(const Vector3& axisY) noexcept
		{
			this->_21 = axisY.x;
			this->_22 = axisY.y;
			this->_23 = axisY.z;
			return *this;
		}

		/// <summary>
		/// Z軸，位置の設定.
		/// </summary>
		/// <param name="axisZ">Z軸成分.</param>
		Matrix33& set_axis_z(const Vector3& axisZ) noexcept
		{
			this->_31 = axisZ.x;
			this->_32 = axisZ.y;
			this->_33 = axisZ.z;
			return *this;
		}

		/// <summary>
		/// 位置の設定.
		/// </summary>
		/// <param name="position">座標.</param>
		void set_position(const Vector2& position) noexcept
		{
			this->_31 = position.x;
			this->_32 = position.y;
		}

		/// <summary>
		/// 位置の設定.
		/// </summary>
		/// <param name="position">座標.</param>
		void set_position(const Vector3& position) noexcept
		{
			this->_31 = position.x;
			this->_32 = position.y;
			this->_33 = position.z;
		}

		/// <summary>
		/// ロールの取得.
		/// </summary>
		/// <returns>ロール値を返す.</returns>
		value_type get_roll() const noexcept
		{
			return std::atan2(this->_12, this->_22);
		}

		/// <summary>
		/// ピッチの取得.
		/// </summary>
		/// <returns>ピッチ値を返す.</returns>
		value_type get_pitch() const noexcept
		{
			return std::asin(-this->_32);
		}

		/// <summary>
		/// ヨーを取得.
		/// </summary>
		/// <returns>ヨー値を返す.</returns>
		value_type get_yaw() const noexcept
		{
			return std::atan2(this->_31, this->_33);
		}

		/// <summary>
		/// X軸を取得.
		/// </summary>
		/// <returns>軸ベクトルを返す.</returns>
		const Vector3& get_axis_x() const noexcept
		{
			return *reinterpret_cast<const Vector3*>(&this->_11);
		}

		/// <summary>
		/// Y軸を取得.
		/// </summary>
		/// <returns>軸ベクトルを返す.</returns>
		const Vector3& get_axis_y() const noexcept
		{
			return *reinterpret_cast<const Vector3*>(&this->_21);
		}

		/// <summary>
		/// Z軸を取得.
		/// </summary>
		/// <returns>軸ベクトルを返す.</returns>
		const Vector3& get_axis_z() const noexcept
		{
			return *reinterpret_cast<const Vector3*>(&this->_31);
		}

		/// <summary>
		/// 左方向のベクトルを取得.
		/// </summary>
		/// <returns>左方向を返す.</returns>
		const Vector3& get_left() const noexcept
		{
			return *reinterpret_cast<const Vector3*>(&this->_11);
		}

		/// <summary>
		/// 上方向のベクトルを取得.
		/// </summary>
		/// <returns>上方向を返す.</returns>
		const Vector3& get_up() const noexcept
		{
			return *reinterpret_cast<const Vector3*>(&this->_21);
		}

		/// <summary>
		/// 前方向のベクトルを取得.
		/// </summary>
		/// <returns>前方向を返す.</returns>
		const Vector3& get_front() const noexcept
		{
			return *reinterpret_cast<const Vector3*>(&this->_31);
		}

		/// <summary>
		/// 位置を取得.
		/// </summary>
		/// <returns>位置を返す.</returns>
		const Vector2& get_position() const noexcept
		{
			return *reinterpret_cast<const Vector2*>(&this->_31);
		}

		/// <summary>
		/// 座標変換.
		/// </summary>
		/// <param name="v">変換する座標.</param>
		/// <returns>変換後の座標を返す.</returns>
		Vector2 transform(const Vector2& target) const noexcept
		{
			return {target.x * this->_11 + target.y * this->_21 + this->_31,
			        target.x * this->_12 + target.y * this->_22 + this->_32};
		}

		/// <summary>
		/// 座標変換.
		/// </summary>
		/// <param name="v">変換する座標.</param>
		/// <returns>変換後の座標を返す.</returns>
		Vector3 transform(const Vector3& target) const noexcept
		{
			return {(this->_11 * target.x) + (this->_21 * target.y) +
			            (this->_31 * target.z),
			        (this->_12 * target.x) + (this->_22 * target.y) +
			            (this->_32 * target.z),
			        (this->_13 * target.x) + (this->_23 * target.y) +
			            (this->_33 * target.z)};
		}

		/// <summary>
		/// 法線ベクトルの座標変換を行う.
		/// </summary>
		/// <param name="v">変換する座標.</param>
		/// <returns>変換後の座標を返す.</returns>
		Vector2 transform_normal(const Vector2& target) const
		{
			return {target.x * this->_11 + target.y * this->_21,
			        target.x * this->_12 + target.y * this->_22};
		}

		/// <summary>
		/// 絶対値を取得.
		/// </summary>
		/// <returns>絶対値にした行列を返す.</returns>
		Matrix33& abs()
		{
			for ( auto& value : v )
			{
				value = std::abs(value);
			}
			return *this;
		}

	public:
		/// <summary>
		/// 平行移動量の設定.
		/// </summary>
		/// <param name="translation">平行移動量.</param>
		static Matrix33 Translation(const Vector2& translation)
		{
			return Matrix33{none_init_v}.set_translation(translation);
		}

		/// <summary>
		/// 4行4列行列から行列を作成.
		/// </summary>
		static Matrix33 Rotate(Matrix44 const& mat);

		/// <summary>
		/// クォータニオンから行列を作成.
		/// </summary>
		/// <param name="q">クォータニオン</param>
		static Matrix33 Rotate(const Quaternion& q);

		/// <summary>
		/// X軸から行列を求める.
		/// </summary>
		/// <param name="radian">角度.</param>
		/// <returns>作成した行列を返す.</returns>
		static Matrix33 RotationX(Radian radian) noexcept
		{
			return Matrix33{none_init_v}.set_rotation_x(radian);
		}

		/// <summary>
		/// Y軸から行列を求める.
		/// </summary>
		/// <param name="degree">角度.</param>
		/// <returns>作成した行列を返す.</returns>
		static Matrix33 RotationY(Radian radian) noexcept
		{
			return Matrix33{none_init_v}.set_rotation_y(radian);
		}

		/// <summary>
		/// Z軸から行列を求める.
		/// </summary>
		/// <param name="degree">角度.</param>
		/// <returns>作成した行列を返す.</returns>
		static Matrix33 RotationZ(Radian radian) noexcept
		{
			return Matrix33{none_init_v}.set_rotation_z(radian);
		}

		/// <summary>
		/// クロス行列を作成する.
		/// </summary>
		/// <param name="v">ベクトル.</param>
		/// <returns>作成した行列を返す.</returns>
		static Matrix33 CrossMatrix(const Vector3& v) noexcept
		{
			return {0.0f, v.z, -v.y, -v.z, 0.0f, v.x, v.y, -v.x, 0.0f};
		}

		/// <summary>
		/// 拡大縮小行列を作成する.
		/// </summary>
		/// <param name="scaleFactor">スケール値.</param>
		/// <returns>作成した行列を返す.</returns>
		static Matrix33 Scaling(const Vector3& scaleFactor)
		{
			return Matrix33{none_init_v}.set_scale(scaleFactor);
		}
	public:
		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>変換後のポインタを返す.</returns>
		operator value_type*()
		{
			return reinterpret_cast<value_type*>(this->v);
		}
		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>変換後のポインタを返す.</returns>
		operator const value_type*() const
		{
			return reinterpret_cast<value_type const*>(this->v);
		}

		/// <summary>
		/// 加算単項演算子オーバーロード.
		/// </summary>
		Matrix33 operator+() const
		{
			return Matrix33{*this};
		}

		/// <summary>
		/// 減算演算子オーバーロード.
		/// </summary>
		Matrix33 operator-() const
		{
			Matrix33 result{none_init_v};
			for ( size_type i = 0; i < 9; ++i )
			{
				result.v[i] = -this->v[i];
			}
			return result;
		}

		/// <summary>
		/// 加算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">代入相手行列.</param>
		/// <returns>計算後の行列を返す.</returns>
		Matrix33& operator+=(const Matrix33& other)
		{
			for ( size_type i = 0; i < 9; ++i )
			{
				this->v[i] += other.v[i];
			}
			return *this;
		}

		/// <summary>
		/// 減算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">代入相手行列.</param>
		/// <returns>計算後の行列を返す.</returns>
		Matrix33& operator-=(const Matrix33& other)
		{
			for ( size_type i = 0; i < 9; ++i )
			{
				this->v[i] -= other.v[i];
			}
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">代入相手行列.</param>
		/// <returns>計算後の行列を返す.</returns>
		Matrix33& operator*=(const Matrix33& other)
		{
			Matrix33 m;

			for ( int i = 0; i < 3; i++ )
			{
				for ( int j = 0; j < 3; j++ )
				{
					m.m[i][j] = this->m[i][0] * other.m[0][j] +
					            this->m[i][1] * other.m[1][j] +
					            this->m[i][2] * other.m[2][j];
				}
			}

			*this = m;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">代入相手行列.</param>
		/// <returns>計算後の行列を返す.</returns>
		Matrix33& operator*=(value_type s)
		{
			for ( size_type i = 0; i < 9; ++i )
			{
				this->v[i] *= s;
			}
			return *this;
		}

		/// <summary>
		/// 除算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">代入相手行列.</param>
		/// <returns>計算後の行列を返す.</returns>
		Matrix33& operator/=(value_type s)
		{
			return *this *= (1.0f / s);
		}

	public:
		/// <summary>
		/// 加算2項演算子オーバーロード.
		/// </summary>
		/// <returns>加算後の行列.</returns>
		Matrix33 operator+(const Matrix33& right) const
		{
			return Matrix33(*this) += right;
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		/// <param name="m1">行列1.</param>
		/// <param name="m2">行列2.</param>
		/// <returns>減算後の行列.</returns>
		Matrix33 operator-(const Matrix33& right) const
		{
			return Matrix33(*this) -= right;
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="m1">行列1.</param>
		/// <param name="m2">行列2.</param>
		/// <returns>乗算後の行列.</returns>
		Matrix33 operator*(const Matrix33& right) const
		{
			return Matrix33(*this) *= right;
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="m">行列.</param>
		/// <param name="s">スカラー値.</param>
		/// <returns>乗算後の行列.</returns>
		Matrix33 operator*(value_type right) const
		{
			return Matrix33(*this) *= right;
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="m">行列.</param>
		/// <param name="V">ベクトル.</param>
		/// <returns>乗算後の行列.</returns>
		Vector3 operator*(const Vector3& V) const
		{
			return this->transform(V);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="s">スカラー値.</param>
		/// <param name="m">行列.</param>
		/// <returns>乗算後の行列.</returns>
		friend Matrix33 operator*(value_type left, const Matrix33& right) noexcept
		{
			//return Matrix33{ right } *= left;
			return right * left;
		}

		/// <summary>
		/// 比較演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>等しければ真を返す.</returns>
		bool operator==(const Matrix33& right) const noexcept
		{
			for ( size_type i = 0; i < 9; ++i )
			{
				if ( this->v[i] != right.v[i] )
					return false;
			}
			return true;
		}

		/// <summary>
		/// 比較演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺値.</param>
		/// <returns>等しくなければ真を返す.</returns>
		bool operator!=(const Matrix33& right) const noexcept
		{
			return !(*this == right);
		}

	}; //! struct Matrix33

} // namespace bavil::math
