#pragma once

#include "bavil_type.h"
#include "math/bavil_math_def.h"
#include "math/bavil_math_function.h"
#include "math/bavil_vector2.h"
#include "math/bavil_vector3.h"
#include "math/bavil_vector4.h"

namespace bavil::math
{

	/// <summary>
	/// 4行4列ベクトルの座標変換行列.
	/// </summary>
	struct Matrix44
	{
		using value_type = f32;
		using size_type = u32;
		using self_type = Matrix44;
		using vector2_type = Vector2;
		using vector3_type = Vector3;
		using vector4_type = Vector4;
		using quaternion_type = Quaternion;
	public:
#pragma warning(push)
#pragma warning(disable:4201) // 無名構造体・無名共有体の利用
		union
		{
			struct
			{
				/// <summary>
				/// X軸成分.
				/// </summary>
				value_type _11, _12, _13, _14;
				/// <summary>
				/// Y軸成分.
				/// </summary>
				value_type _21, _22, _23, _24;
				/// <summary>
				/// Z軸成分.
				/// </summary>
				value_type _31, _32, _33, _34;
				/// <summary>
				/// 平行移動成分.
				/// </summary>
				value_type _41, _42, _43, _44;
			};
#if 0 && _MSC_VER >= 1900
			struct
			{
				Vector4 _xaxis;
				Vector4 _yaxis;
				Vector4 _zaxis;
				Vector4 _waxis;
			};
#endif
			/// <summary>
			/// 4行4列の配列.
			/// </summary>
			value_type		m[4][4];
			/// <summary>
			/// 4行4列要素.
			/// </summary>
			value_type		v[16];
		};
#pragma warning(pop)

	public:
		/// <summary>
		/// 単位行列.
		/// </summary>
		static const Matrix44& IDENTITY;
		/// <summary>
		/// 空行列.
		/// </summary>
		static const Matrix44& EMPTY;

	public:
		/// <summary>
		/// デフォルトコンストラクタ.
		/// </summary>
		Matrix44()  noexcept
			: Matrix44{
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f }
		{
		}

		/// <summary>
		/// 初期化無しコンストラクタ.
		/// </summary>
		/// <param name="_init">初期化なしタグ.</param>
		explicit Matrix44(none_init_t _init) noexcept
		{
			static_cast<void>(_init);
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="m11">1行1列成分</param>
		/// <param name="m12">1行2列成分</param>
		/// <param name="m13">1行3列成分</param>
		/// <param name="m14">1行4列成分</param>
		/// <param name="m21">2行1列成分</param>
		/// <param name="m22">2行2列成分</param>
		/// <param name="m23">2行3列成分</param>
		/// <param name="m24">2行4列成分</param>
		/// <param name="m31">3行1列成分</param>
		/// <param name="m32">3行2列成分</param>
		/// <param name="m33">3行3列成分</param>
		/// <param name="m34">3行4列成分</param>
		/// <param name="m41">4行1列成分</param>
		/// <param name="m42">4行2列成分</param>
		/// <param name="m43">4行3列成分</param>
		/// <param name="m44">4行4列成分</param>
		Matrix44(
			value_type m11, value_type m12, value_type m13, value_type m14,
			value_type m21, value_type m22, value_type m23, value_type m24,
			value_type m31, value_type m32, value_type m33, value_type m34,
			value_type m41, value_type m42, value_type m43, value_type m44) noexcept
			: _11(m11), _12(m12), _13(m13), _14(m14)
			, _21(m21), _22(m22), _23(m23), _24(m24)
			, _31(m31), _32(m32), _33(m33), _34(m34)
			, _41(m41), _42(m42), _43(m43), _44(m44)
		{
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="M">行列.</param>
		explicit Matrix44(const Matrix33& M);
		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="q">クォータニオン.</param>
		explicit Matrix44(const Quaternion& q);

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="V">要素配列.</param>
		explicit Matrix44(const value_type* V) noexcept
			: Matrix44(
				V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7],
				V[8], V[9], V[10], V[11], V[12], V[13], V[14], V[15])
		{
		}


		/// <summary>
			/// 単位行列の設定.
			/// </summary>
			/// <returns>設定後の実体の参照を返す.</returns>
		self_type& identity() noexcept
		{
			return *this = self_type::IDENTITY;
		}

		/// <summary>
		/// 転置行列を求める.
		/// </summary>
		/// <returns>転置行列を返す.</returns>
		self_type getTranspose() const noexcept
		{
			return
			{
				_11, _21, _31, _41,
				_12, _22, _32, _42,
				_13, _23, _33, _43,
				_14, _24, _34, _44
			};
		}

		/// <summary>
		/// 逆行列を求める.
		/// <para>拡大縮小を除く、回転と平行移動のみ.</para>
		/// </summary>
		/// <returns>逆行列を返す.</returns>
		self_type getInverseFast() const noexcept
		{
			// 回転行列の作成
			self_type result = *this;

			result.setPosition(Vector3::ZERO);

			// 回転行列の逆行列を作成
			result = result.getTranspose();

			// 平行移動成分の逆変換
			const Vector3 invPosition = -this->getPosition() * result;

			// 逆行列を作成
			result.setPosition(invPosition);
			return result;
		}

		/// <summary>
		/// 逆行列を求める.
		/// <para>逆行列が存在しない時はそのままの行列を返す.</para>
		/// </summary>
		/// <returns>逆行列を返す.</returns>
		self_type getInverse() const;

		/// <summary>
		/// 回転行列の正規化.
		/// </summary>
		/// <returns>正規化後の参照を返す.</returns>
		self_type& normalize()
		{
			// 前方向のベクトルを取得.
			vector3_type front = this->getFront();

			// 上方向のベクトルを取得.
			vector3_type up = this->getUp();

			// 左方向のベクトルを求める.
			const vector3_type left = up.cross(front).normalize();

			// 上方向のベクトルを求める.
			up = front.cross(left).normalize();

			// 前方向のベクトルを求める.
			front = left.cross(up);

			this->setLeft(left);
			this->setUp(up);
			this->setFront(front);

			return *this;
		}

		/// <summary>
		/// 正規化したベクトルを取得.
		/// </summary>
		/// <returns></returns>
		self_type getNormalize() const noexcept
		{
			return self_type(*this).normalize();
		}

		/// <summary>
		/// 回転行列の正規化.
		/// </summary>
		/// <returns>正規化後の参照を返す.</returns>
		self_type& safeNormalize()
		{
			// 前方向のベクトルを取得.
			vector3_type front = this->getFront();

			// 上方向のベクトルを取得.
			vector3_type up = this->getUp();

			// 左方向のベクトルを求める.
			const vector3_type left = up.cross(front).safeNormalize();

			// 上方向のベクトルを求める.
			up = front.cross(left).safeNormalize();

			// 前方向のベクトルを求める.
			front = left.cross(up);

			this->setLeft(left);
			this->setUp(up);
			this->setFront(front);

			return *this;
		}


		/// <summary>
		/// 正規化したベクトルを取得.
		/// </summary>
		/// <returns></returns>
		self_type getSafeNormalize() const noexcept
		{
			return self_type(*this).safeNormalize();
		}

		/// <summary>
		/// 直角逆行列を求める.
		/// </summary>
		/// <returns>直角逆行列後の参照を求める.</returns>
		self_type& orthoInverse()
		{
			const vector3_type inv0 = Vector3(this->m[0][0], this->m[1][0], this->m[2][0]);
			const vector3_type inv1 = Vector3(this->m[0][1], this->m[1][1], this->m[2][1]);
			const vector3_type inv2 = Vector3(this->m[0][2], this->m[1][2], this->_33);
			const vector3_type inv3 = Vector3(
				(-((inv0 * this->m[3][0]) +
					((inv1 * this->m[3][1]) +
						(inv2 * this->m[3][2])))));


			return *this = self_type
			{
				inv0.x, inv0.y, inv0.z,
				inv1.x, inv1.y, inv1.z,
				inv2.x, inv2.y, inv2.z,
				inv3.x, inv3.y, inv3.z,
				0.0f, 0.0f, 0.0f, 1.0f
			};
		}

		/// <summary>
		/// 直角逆行列化した行列を取得.
		/// </summary>
		/// <returns>直角逆行列を求める.</returns>
		self_type getOrthoInverse() const
		{
			return self_type(*this).orthoInverse();
		}

#pragma region Scale

		/// <summary>
		/// 拡大縮小列の設定.
		/// </summary>
		/// <param name="x">X成分</param>
		/// <param name="y">Y成分</param>
		/// <param name="z">Z成分</param>
		/// <returns>設定後の行列を返す.</returns>
		self_type& setScale(value_type x, value_type y, value_type z) noexcept
		{
			_11 = x;	_12 = 0.f;	_13 = 0.f;	_14 = 0.f;
			_21 = 0.f;	_22 = y;	_23 = 0.f;	_24 = 0.f;
			_31 = 0.f;	_32 = 0.f;	_33 = z;	_34 = 0.f;
			_41 = 0.f;	_42 = 0.f;	_43 = 0.f;	_44 = 1.f;
			return *this;
		}

		/// <summary>
		/// 拡大縮小列の設定.
		/// </summary>
		/// <param name="scaleFactor">スケール値</param>
		/// <returns>設定後の行列を返す.</returns>
		self_type& setScale(const value_type scaleFactor)
		{
			return this->setScale(scaleFactor, scaleFactor, scaleFactor);
		}

		/// <summary>
		/// 拡大縮小列の設定.
		/// </summary>
		/// <param name="scaleFactor">スケール値</param>
		/// <returns>設定後の行列を返す.</returns>
		self_type& setScale(const vector3_type& scaleFactor)
		{
			return this->setScale(scaleFactor.x, scaleFactor.y, scaleFactor.z);
		}

#pragma endregion

#pragma region SetterRotete

		/// <summary>
		/// 回転行列の設定.
		/// </summary>
		/// <param name="radian">角度.</param>
		/// <param name="axisX">X軸成分.</param>
		/// <param name="axisY">Y軸成分.</param>
		/// <param name="axisZ">Z軸成分.</param>
		/// <returns>設定後の回転行列.</returns>
		self_type& setRotation(Radian radian, const value_type axisX, const value_type axisY, const value_type axisZ)
		{
			return this->setRotation(radian, { axisX, axisY, axisZ });
		}

		/// <summary>
		/// 回転行列の設定.
		/// </summary>
		/// <param name="radian">角度.</param>
		/// <param name="axis">軸成分.</param>
		/// <returns>設定後の回転行列.</returns>
		self_type& setRotation(Radian radian, const vector3_type& axis);

		/// <summary>
		/// 回転行列の設定.
		/// </summary>
		/// <param name="q">クォータニオン.</param>
		/// <returns>設定後の回転行列.</returns>
		self_type& setRotation(const quaternion_type& q)
		{
			return *this = self_type(q);
		}

		/// <summary>
		/// 回転行列の設定.
		/// <para>X軸周りの回転.</para>
		/// </summary>
		/// <param name="radian">角度</param>
		/// <returns>設定後の行列を返す.</returns>
		self_type& setRotateX(Radian radian) noexcept
		{
			m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0.0f;
			m[1][0] = 0.0f;									m[1][3] = 0.0f;
			m[2][0] = 0.0f;									m[2][3] = 0.0f;
			m[3][0] = 0.0f;	m[3][3] = 0.0f;	m[3][3] = 0.0f;	m[3][3] = 1.0f;

			m[1][1] = Cos(radian);
			m[1][2] = Sin(radian);
			m[2][1] = -m[1][2];
			_33 = m[1][1];
			return *this;
		}

		/// <summary>
		/// 回転行列の設定.
		/// <para>Y軸周りの回転.</para>
		/// </summary>
		/// <param name="radian">角度</param>
		/// <returns>設定後の行列を返す.</returns>
		self_type& setRotateY(Radian radian) noexcept
		{
			m[0][1] = 0.0f;					m[0][3] = 0.0f;
			m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;	m[1][3] = 0.0f;
			m[2][1] = 0.0f;					m[2][3] = 0.0f;
			m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;	m[3][3] = 1.0f;

			m[0][0] = Cos(radian);
			m[2][0] = Sin(radian);
			m[0][2] = -m[2][0];
			_33 = m[0][0];
			return *this;
		}

		/// <summary>
		/// 回転行列の設定.
		/// <para>Z軸周りの回転.</para>
		/// </summary>
		/// <param name="radian">角度</param>
		/// <returns>設定後の行列を返す.</returns>
		self_type& setRotateZ(Radian radian) noexcept
		{
			m[0][2] = 0.0f;	m[0][3] = 0.0f;
			m[1][2] = 0.0f;	m[1][3] = 0.0f;
			m[2][0] = 0.0f;	m[2][1] = 0.0f;	_33 = 1.0f;	m[2][3] = 0.0f;
			m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;	m[3][3] = 1.0f;

			m[0][0] = Cos(radian);
			m[0][1] = Sin(radian);
			m[1][0] = -m[0][1];
			m[1][1] = m[0][0];
			return *this;
		}

		/// <summary>
		/// 回転行列の設定.
		/// </summary>
		/// <param name="yaw">ヨー.</param>
		/// <param name="pitch">ピッチ.</param>
		/// <param name="roll">ロール.</param>
		/// <returns>設定後の行列を返す.</returns>
		self_type& setRotationYawPitchRoll(Radian yaw, Radian pitch, Radian roll) noexcept
		{
			/* 回転マトリクスを合成する */
			return *this = Matrix44{ none_init_v }.setRotateZ(roll) *
				Matrix44
			{
				none_init_v
			}.setRotateX(pitch)*
					Matrix44
				{
					none_init_v
				}.setRotateY(yaw);
		}

#pragma endregion

#pragma region Translate

		/// <summary>
		/// 平行移動行列の設定.
		/// </summary>
		/// <param name="translate">平行移動量</param>
		/// <returns>設定後の行列を返す.</returns>
		self_type& setTranslate(const vector3_type& translate)
		{
			m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0.0f;
			m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;	m[1][3] = 0.0f;
			m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;	m[2][3] = 0.0f;
			m[3][0] = translate.x;	m[3][1] = translate.y;	m[3][2] = translate.z;	m[3][3] = 1.0f;
			return *this;
		}

		/// <summary>
		/// 平行移動行列の設定.
		/// </summary>
		/// <param name="translate">平行移動量</param>
		/// <returns>設定後の行列を返す.</returns>
		self_type& setTranslate(const vector4_type& translate)
		{
			m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0.0f;
			m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;	m[1][3] = 0.0f;
			m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;	m[2][3] = 0.0f;
			m[3][0] = translate.x;	m[3][1] = translate.y;	m[3][2] = translate.z;	m[3][3] = translate.w;
			return *this;
		}

#pragma endregion

#pragma region getter

		/// <summary>
		/// 座標を取得.
		/// </summary>
		/// <returns>座標を返す.</returns>
		const vector3_type& getPosition() const noexcept
		{
			return *reinterpret_cast<const vector3_type*>(&this->_41);
		}

		/// <summary>
		/// 左方向のベクトルを取得.
		/// </summary>
		/// <returns>左方向を返す.</returns>
		const vector3_type& getLeft() const noexcept
		{
			return *reinterpret_cast<const vector3_type*>(&this->_11);
		}

		/// <summary>
		/// 上方向のベクトルを取得.
		/// </summary>
		/// <returns>上方向を返す.</returns>
		const vector3_type& getUp() const noexcept
		{
			return *reinterpret_cast<const vector3_type*>(&this->_21);
		}

		/// <summary>
		/// 前方向のベクトルを取得.
		/// </summary>
		/// <returns>前方向を返す.</returns>
		const vector3_type& getFront() const noexcept
		{
			return *reinterpret_cast<const vector3_type*>(&this->_31);
		}

		/// <summary>
		/// スケール値を取得.
		/// </summary>
		/// <returns>スケール値を返す.</returns>
		vector3_type getScale() const noexcept
		{
			return
			{
				this->getLeft().length(),
				this->getUp().length(),
				this->getFront().length()
			};
		}

#pragma endregion

#pragma region setter

		/// <summary>
		/// 座標を設定.
		/// </summary>
		/// <param name="position">設定するベクトル.</param>
		self_type& setPosition(const vector3_type& position) noexcept
		{
			_41 = position.x;
			_42 = position.y;
			_43 = position.z;
			return *this;
		}
		/// <summary>
		/// 左方向のベクトルを設定.
		/// </summary>
		/// <param name="left">設定するベクトル.</param>
		self_type& setLeft(const vector3_type& left) noexcept
		{
			_11 = left.x;
			_12 = left.y;
			_13 = left.z;
			return *this;
		}
		/// <summary>
		/// 左方向のベクトルを設定.
		/// </summary>
		/// <param name="up">設定するベクトル.</param>
		self_type& setUp(const vector3_type& up) noexcept
		{
			_21 = up.x;
			_22 = up.y;
			_23 = up.z;
			return *this;
		}

		/// <summary>
		/// 前方向のベクトルを設定.
		/// </summary>
		/// <param name="front">設定するベクトル.</param>
		self_type& setFront(const vector3_type& front) noexcept
		{
			_31 = front.x;
			_32 = front.y;
			_33 = front.z;
			return *this;
		}

#pragma endregion


		/// <summary>
		/// ピッチを取得.
		/// </summary>
		/// <returns>ピッチを返す.</returns>
		value_type pitch() const noexcept
		{
			return this->getFront().getPitch();
		}

		/// <summary>
		/// ヨーを取得.
		/// </summary>
		/// <returns>ヨーを取得.</returns>
		value_type getYaw() const noexcept
		{
			return this->getFront().getYaw();
		}

		/// <summary>
		/// ロールを取得.
		/// </summary>
		/// <returns>ロールを取得.</returns>
		value_type getRoll() const noexcept
		{
			return std::atan2(_12, _22);
		}

		/// <summary>
		/// 透視変換行列の設定.
		/// </summary>
		/// <param name="fov">視野角</param>
		/// <param name="aspect">画面の縦横比</param>
		/// <param name="znear">近クリップ面</param>
		/// <param name="zfar">遠クリップ面</param>
		/// <returns>設定後の行列を返す.</returns>
		self_type& setPerspective(Radian fov, const value_type aspect, const value_type znear, const value_type zfar) noexcept
		{
			value_type f = 1.0f / Tan(fov * 0.5f);
			this->m[0][0] = f / aspect;	this->m[0][1] = 0.0f;	this->m[0][2] = 0.0f;						this->m[0][3] = 0.0f;
			this->m[1][0] = 0.0f;		this->m[1][1] = f;		this->m[1][2] = 0.0f;						this->m[1][3] = 0.0f;
			this->m[2][0] = 0.0f;		this->m[2][1] = 0.0f;	this->_33 = (zfar + znear) / (znear - zfar);		this->m[2][3] = -1.0f;
			this->m[3][0] = 0.0f;		this->m[3][1] = 0.0f;	this->m[3][2] = (2 * zfar * znear) / (znear - zfar);	this->m[3][3] = 1.0f;

			return *this;
		}

		/// <summary>
		/// 視野変換行列の設定.
		/// </summary>
		/// <param name="eye">視点の正面方向のベクトル</param>
		/// <param name="at">視点の右向き方向のベクトル</param>
		/// <param name="up">視点の上向きの方向ベクトル</param>
		/// <returns>設定後の行列を返す.</returns>
		self_type& setLookAt(const vector3_type& eye, const vector3_type& at, const vector3_type& up)
		{
			vector3_type _e = vector3_type(eye - at);
			_e.normalize();
			vector3_type _v = vector3_type(up.cross(_e));
			_v.normalize();
			const vector3_type _u = _e.cross(_v);

			this->m[0][0] = _v.x;			this->m[0][1] = _u.x;			this->m[0][2] = _e.y;			this->m[0][3] = 0.0f;
			this->m[1][0] = _v.y;			this->m[1][1] = _u.y;			this->m[1][2] = _e.y;			this->m[1][3] = 0.0f;
			this->m[2][0] = _v.z;			this->m[2][1] = _u.z;			this->_33 = _e.z;			this->m[2][3] = 0.0f;
			this->m[3][0] = -eye.dot(_v);	this->m[3][1] = -eye.dot(_u);	this->m[3][2] = -eye.dot(_e);	this->m[3][3] = 1.0f;
			return *this;
		}

		/// <summary>
		/// 視野変換行列を求める.
		/// <para>右手座標系</para>
		/// </summary>
		/// <param name="from">視点の座標</param>
		/// <param name="at">目標点の座標</param>
		/// <param name="up">視点の上側の方向</param>
		void lookAtRH(const vector3_type& from, const vector3_type& at, const vector3_type& up)
		{
			this->lookAtLH(at, from, up);
		}

		/// <summary>
		/// 視野変換行列を求める.
		/// <para>左手座標系.</para>
		/// </summary>
		/// <param name="from">視点の座標.</param>
		/// <param name="at">目標点の座標.</param>
		/// <param name="up">視点の上側の方向</param>
		void lookAtLH(const vector3_type& from, const vector3_type& at, const vector3_type& up)
		{
			// ｚ方向のベクトルを求める.
			const vector3_type zaxis = (at - from).normalize();

			// ｘ方向のベクトルを求める.
			const vector3_type xaxis = up.cross(zaxis).normalize();

			// ｙ方向のベクトルを求める.
			const vector3_type yaxis = zaxis.cross(xaxis);

			// 回転行列に各ベクトルを設定する.
			this->m[0][0] = xaxis.x;
			this->m[0][1] = yaxis.x;
			this->m[0][2] = zaxis.x;
			this->m[0][3] = 0.0f;

			this->m[1][0] = xaxis.y;
			this->m[1][1] = yaxis.y;
			this->m[1][2] = zaxis.y;
			this->m[1][3] = 0.0f;

			this->m[2][0] = xaxis.z;
			this->m[2][1] = yaxis.z;
			this->m[2][2] = zaxis.z;
			this->m[2][3] = 0.0f;

			// 視点の位置を設定する.
			this->m[3][0] = -from.dot(xaxis);
			this->m[3][1] = -from.dot(yaxis);
			this->m[3][2] = -from.dot(zaxis);
			this->m[3][3] = 1.0f;
		}

		/// <summary>
		/// 視野変換行列に変換する.
		/// <para>右手座標系.</para>
		/// </summary>
		/// <param name="mat">変換する行列</param>
		void convViewRH(const self_type& mat) noexcept
		{
			this->m[0][0] = -mat.m[0][0];
			this->m[0][1] = -mat.m[1][0];
			this->m[0][2] = -mat.m[2][0];

			this->m[1][0] = mat.m[0][1];
			this->m[1][1] = mat.m[1][1];
			this->m[1][2] = mat.m[2][1];

			this->m[2][0] = -mat.m[0][2];
			this->m[2][1] = -mat.m[1][2];
			this->m[2][2] = -mat.m[2][2];

			this->m[3][0] = -(mat.m[3][0] * this->m[0][0]
				+ mat.m[3][1] * this->m[1][0]
				+ mat.m[3][2] * this->m[2][0]);
			this->m[3][1] = -(mat.m[3][0] * this->m[0][1]
				+ mat.m[3][1] * this->m[1][1]
				+ mat.m[3][2] * this->m[2][1]);
			this->m[3][2] = -(mat.m[3][0] * this->m[0][2]
				+ mat.m[3][1] * this->m[1][2]
				+ mat.m[3][2] * this->m[2][2]);

			this->m[0][3] = mat.m[0][3];
			this->m[1][3] = mat.m[1][3];
			this->m[2][3] = mat.m[2][3];
			this->m[3][3] = mat.m[3][3];

		}

		/// <summary>
		/// 視野変換行列に変換する.
		/// <para>左手座標系.</para>
		/// </summary>
		/// <param name="mat"></param>
		void convViewLH(const self_type& mat) noexcept
		{
			this->m[0][0] = mat.m[0][0];
			this->m[0][1] = mat.m[1][0];
			this->m[0][2] = mat.m[2][0];

			this->m[1][0] = mat.m[0][1];
			this->m[1][1] = mat.m[1][1];
			this->m[1][2] = mat.m[2][1];

			this->m[2][0] = mat.m[0][2];
			this->m[2][1] = mat.m[1][2];
			this->m[2][2] = mat.m[2][2];

			this->m[3][0] = -(mat.m[3][0] * this->m[0][0]
				+ mat.m[3][1] * this->m[1][0]
				+ mat.m[3][2] * this->m[2][0]);
			this->m[3][1] = -(mat.m[3][0] * this->m[0][1]
				+ mat.m[3][1] * this->m[1][1]
				+ mat.m[3][2] * this->m[2][1]);
			this->m[3][2] = -(mat.m[3][0] * this->m[0][2]
				+ mat.m[3][1] * this->m[1][2]
				+ mat.m[3][2] * this->m[2][2]);

			this->m[0][3] = mat.m[0][3];
			this->m[1][3] = mat.m[1][3];
			this->m[2][3] = mat.m[2][3];
			this->m[3][3] = mat.m[3][3];
		}

		/// <summary>
		/// 透視変換行列を求める.
		/// <para>右手座標系.</para>
		/// </summary>
		/// <param name="fov">視野角.</param>
		/// <param name="aspect">アスペクト比.</param>
		/// <param name="zNear">近クリップ面までの距離.</param>
		/// <param name="zFar">遠クリップ面までの距離.</param>
		void perspectiveRH(Radian fov, value_type aspect, value_type zNear, value_type zFar)
		{
			const value_type f = Cos(fov / 2.f) / Sin(fov / 2.f);

			this->m[0][0] = f / aspect;
			this->m[0][1] = 0;
			this->m[0][2] = 0;
			this->m[0][3] = 0;

			this->m[1][0] = 0;
			this->m[1][1] = f;
			this->m[1][2] = 0;
			this->m[1][3] = 0;

			this->m[2][0] = 0;
			this->m[2][1] = 0;
			this->m[2][2] = (zFar + zNear) / (zNear - zFar);
			this->m[2][3] = -1.0f;

			this->m[3][0] = 0;
			this->m[3][1] = 0;
			this->m[3][2] = (2.0f * zFar * zNear) / (zNear - zFar);
			this->m[3][3] = 0;
		}

		/// <summary>
		/// 透視変換行列を求める.
		/// <para>左手座標系.</para>
		/// </summary>
		/// <param name="fov">視野角.</param>
		/// <param name="aspect">アスペクト比.</param>
		/// <param name="zNear">近クリップ面までの距離.</param>
		/// <param name="zFar">遠クリップ面までの距離.</param>
		void perspectiveLH(Radian fov, value_type aspect, value_type zNear, value_type zFar)
		{
			//const value_type f = math::Cos( fov / 2.f ) / math::Sin( fov / 2.0f );
			//const value_type f = static_cast<value_type>( 1.0 ) / std::tan( fov / static_cast<value_type>( 2.0 ) );
			const value_type h = static_cast<value_type>(1.0) / Tan(fov / static_cast<value_type>(2.0));

			this->m[0][0] = h / aspect;
			this->m[0][1] = 0;
			this->m[0][2] = 0;
			this->m[0][3] = 0;

			this->m[1][0] = 0;
			this->m[1][1] = h;
			this->m[1][2] = 0;
			this->m[1][3] = 0;

			this->m[2][0] = 0;
			this->m[2][1] = 0;
			//this->m[2][2] = ( zFar + zNear ) / ( zNear - zFar );
			this->m[2][2] = zFar / (zFar - zNear);
			this->m[2][3] = 1.0f;

			this->m[3][0] = 0;
			this->m[3][1] = 0;
			//this->m[3][2] = ( 2.0f * zFar * zNear ) / ( zNear - zFar );
			this->m[3][2] = -zNear * zFar / (zFar - zNear);
			this->m[3][3] = 0;
		}

		/// <summary>
		/// 透視変換行列を求める.
		/// <para>右手座標系.</para>
		/// </summary>
		/// <param name="left">クリップ面の左側の座標.</param>
		/// <param name="right">クリップ面の右側の座標.</param>
		/// <param name="bottom">クリップ面の下側の座標.</param>
		/// <param name="top">クリップ面の上側の座標.</param>
		/// <param name="zNear">近クリップ面の座標.</param>
		/// <param name="zFar">遠クリップ面の座標.</param>
		void frustumRH(value_type left, value_type right, value_type bottom, value_type top, value_type zNear, value_type zFar)
		{
			this->m[0][0] = (2.0f * zNear) / (right - left);
			this->m[0][1] = 0.0f;
			this->m[0][2] = 0.0f;
			this->m[0][3] = 0.0f;

			this->m[1][0] = 0.0f;
			this->m[1][1] = (2.0f * zNear) / (top - bottom);
			this->m[1][2] = 0.0f;
			this->m[1][3] = 0.0f;

			this->m[2][0] = (right + left) / (right - left);
			this->m[2][1] = (top + bottom) / (top - bottom);
			this->m[2][2] = -(zFar + zNear) / (zFar - zNear);
			this->m[2][3] = -1.0f;

			this->m[3][0] = 0.0f;
			this->m[3][1] = 0.0f;
			this->m[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
			this->m[3][3] = 0.0f;
		}

		/// <summary>
		/// 透視変換行列を求める.
		/// <para>左手座標系.</para>
		/// </summary>
		/// <param name="left">クリップ面の左側の座標.</param>
		/// <param name="right">クリップ面の右側の座標.</param>
		/// <param name="bottom">クリップ面の下側の座標.</param>
		/// <param name="top">クリップ面の上側の座標.</param>
		/// <param name="zNear">近クリップ面の座標.</param>
		/// <param name="zFar">遠クリップ面の座標.</param>
		void frustumLH(value_type left, value_type right, value_type bottom, value_type top, value_type zNear, value_type zFar)
		{
			this->m[0][0] = (2.f * zNear) / (right - left);
			this->m[0][1] = 0.f;
			this->m[0][2] = 0.f;
			this->m[0][3] = 0.f;

			this->m[1][0] = 0.f;
			this->m[1][1] = (2.f * zNear) / (top - bottom);
			this->m[1][2] = 0.f;
			this->m[1][3] = 0.f;

			this->m[2][0] = (right + left) / (right - left);
			this->m[2][1] = (top + bottom) / (top - bottom);
			this->m[2][2] = -(zFar + zNear) / (zFar - zNear);
			this->m[2][3] = 1.f;

			this->m[3][0] = 0.f;
			this->m[3][1] = 0.f;
			this->m[3][2] = -(2.f * zFar * zNear) / (zFar - zNear);
			this->m[3][3] = 0.f;
		}

		/// <summary>
		/// 正射影変換行列を求める.
		/// <para>右手座標系.</para>
		/// </summary>
		/// <param name="left">クリップ面の左側の座標.</param>
		/// <param name="right">クリップ面の右側の座標.</param>
		/// <param name="bottom">クリップ面の下側の座標.</param>
		/// <param name="top">クリップ面の上側の座標.</param>
		/// <param name="zNear">近クリップ面の座標.</param>
		/// <param name="zFar">遠クリップ面の座標.</param>
		void orthoRH(value_type left, value_type right, value_type bottom, value_type top, value_type zNear, value_type zFar)
		{
			this->m[0][0] = 2.f / (right - left);
			this->m[0][1] = 0.f;
			this->m[0][2] = 0.f;
			this->m[0][3] = 0.f;

			this->m[1][0] = 0.f;
			this->m[1][1] = 2.f / (top - bottom);
			this->m[1][2] = 0.f;
			this->m[1][3] = 0.f;

			this->m[2][0] = 0.f;
			this->m[2][1] = 0.f;
			this->m[2][2] = -2.f / (zFar - zNear);
			this->m[2][3] = 0.f;

			this->m[3][0] = -(right + left) / (right - left);
			this->m[3][1] = -(top + bottom) / (top - bottom);
			this->m[3][2] = -(zFar + zNear) / (zFar - zNear);
			this->m[3][3] = 1.f;
		}

		/// <summary>
		/// 正射影変換行列を求める.
		/// <para>左手座標系.</para>
		/// </summary>
		/// <param name="left">クリップ面の左側の座標.</param>
		/// <param name="right">クリップ面の右側の座標.</param>
		/// <param name="bottom">クリップ面の下側の座標.</param>
		/// <param name="top">クリップ面の上側の座標.</param>
		/// <param name="zNear">近クリップ面の座標.</param>
		/// <param name="zFar">遠クリップ面の座標.</param>
		void orthoLH(value_type left, value_type right, value_type bottom, value_type top, value_type zNear, value_type zFar)
		{
			this->m[0][0] = 2.f / (right - left);
			this->m[0][1] = 0.f;
			this->m[0][2] = 0.f;
			this->m[0][3] = 0.f;

			this->m[1][0] = 0.f;
			this->m[1][1] = 2.f / (top - bottom);
			this->m[1][2] = 0.f;
			this->m[1][3] = 0.f;

			this->m[2][0] = 0.f;
			this->m[2][1] = 0.f;
			this->m[2][2] = 2.f / (zFar - zNear);
			this->m[2][3] = 0.f;

			this->m[3][0] = -(right + left) / (right - left);
			this->m[3][1] = -(top + bottom) / (top - bottom);
			this->m[3][2] = -(zFar + zNear) / (zFar - zNear);
			this->m[3][3] = 1.f;
		}

		/// <summary>
		/// 正射影変換行列を求める.
		/// <para>右手座標系.</para>
		/// </summary>
		/// <param name="left">クリップ面の左側の座標.</param>
		/// <param name="right">クリップ面の右側の座標.</param>
		/// <param name="bottom">クリップ面の下側の座標.</param>
		/// <param name="top">クリップ面の上側の座標.</param>
		void ortho2DRH(value_type left, value_type right, value_type bottom, value_type top)
		{
			this->orthoRH(left, right, bottom, top, -1.f, 1.f);
		}

		/// <summary>
		/// 正射影変換行列を求める.
		/// <para>右手座標系.</para>
		/// </summary>
		/// <param name="left">クリップ面の左側の座標.</param>
		/// <param name="right">クリップ面の右側の座標.</param>
		/// <param name="bottom">クリップ面の下側の座標.</param>
		/// <param name="top">クリップ面の上側の座標.</param>
		void ortho2DLH(value_type left, value_type right, value_type bottom, value_type top)
		{
			this->orthoLH(left, right, bottom, top, -1.f, 1.f);
		}


		/// <summary>
		/// 座標変換を行う.
		/// <para>ベクトルと行列の掛け算をする.</para>
		/// </summary>
		/// <param name="v">ベクトル</param>
		/// <returns>変換後のベクトル</returns>
		vector2_type transform(const vector2_type& target) const noexcept
		{
			return
			{
				target.x * _11 + target.y * _21 + _41,
				target.x * _12 + target.y * _22 + _42
			};
		}

		/// <summary>
		/// 座標変換を行う.
		/// <para>ベクトルと行列の掛け算をする.</para>
		/// </summary>
		/// <param name="target">ベクトル</param>
		/// <returns>変換後のベクトル</returns>
		vector3_type transform(const vector3_type& target) const noexcept
		{
			return
			{
				target.x * _11 + target.y * _21 + target.z * _31 + _41,
				target.x * _12 + target.y * _22 + target.z * _32 + _42,
				target.x * _13 + target.y * _23 + target.z * _33 + _43
			};
		}

		/// <summary>
		/// 座標変換を行う.
		/// <para>ベクトルと行列の掛け算をする.</para>
		/// </summary>
		/// <param name="target">ベクトル</param>
		/// <returns>変換後のベクトル</returns>
		vector4_type transform(const vector4_type& target) const noexcept
		{
			return
			{
				target.x * _11 + target.y * _21 + target.z * _31 + target.w * _41,
				target.x * _12 + target.y * _22 + target.z * _32 + target.w * _42,
				target.x * _13 + target.y * _23 + target.z * _33 + target.w * _43,
				target.x * _14 + target.y * _24 + target.z * _34 + target.w * _44
			};
		}

		/// <summary>
		/// ベクトルの座標変換を行う.
		/// </summary>
		/// <param name="target">ベクトル</param>
		/// <returns>変換後のベクトル</returns>
		vector3_type transformCoord(vector3_type const& target) const
		{
			const value_type w = target.x * _14 + target.y * _24 + target.z * _34 + _44;

			return
			{
				(target.x * _11 + target.y * _21 + target.z * _31) / w,
				(target.x * _12 + target.y * _22 + target.z * _32) / w,
				(target.x * _13 + target.y * _23 + target.z * _33) / w
			};
		}

		/// <summary>
		/// ベクトルの座標変換を行う.
		/// </summary>
		/// <param name="target">ベクトル</param>
		/// <returns>変換後のベクトル</returns>
		vector4_type transformCoord(vector4_type const& target) const
		{
			vector4_type result = this->transform(target);
			result *= 1.f / result.w;
			return result;
		}

		/// <summary>
		/// 座標変換を行う.
		/// <para>法線ベクトル用で回転のみで平行移動はさせない.</para>
		/// </summary>
		/// <param name="target">ベクトル</param>
		/// <returns>変換後のベクトル</returns>
		vector3_type transformNormal(const vector3_type& target) const noexcept
		{
			return
			{
				target.x * _11 + target.y * _21 + target.z * _31,
				target.x * _12 + target.y * _22 + target.z * _32,
				target.x * _13 + target.y * _23 + target.z * _33
			};
		}

		/// <summary>
		/// 絶対値を取得.
		/// </summary>
		/// <returns>絶対値にした行列の参照を返す.</returns>
		self_type& abs() noexcept
		{
			for (auto& value : v)
			{
				value = std::abs(value);
			}
			return *this;
		}

		/// <summary>
		/// 絶対値を取得.
		/// </summary>
		/// <returns>絶対値にした行列の参照を返す.</returns>
		self_type getAbs() const noexcept
		{
			return self_type(*this).abs();
		}

	public:
		/// <summary>
		/// スケール値から行列を求める.
		/// </summary>
		/// <param name="translate">スケール値.</param>
		static self_type Translate(vector3_type const& translate)
		{
			return
			{
				1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				translate.x, translate.y, translate.z, 1.f
			};
		}

		/// <summary>
		/// スケール値から行列を求める.
		/// </summary>
		/// <param name="scale">スケール値.</param>
		static self_type Scaling(vector3_type const& scale)
		{
			return self_type{ none_init_v }.setScale(scale);
		}

		/// <summary>
		/// X軸から行列を求める.
		/// </summary>
		/// <param name="radian">角度.</param>
		/// <returns>作成した行列を返す.</returns>
		static self_type RotationX(Radian radian)
		{
			return self_type{ none_init_v }.setRotateX(radian);
		}

		/// <summary>
		/// Y軸から行列を求める.
		/// </summary>
		/// <param name="radian">角度.</param>
		/// <returns>作成した行列を返す.</returns>
		static self_type RotationY(Radian radian)
		{
			return self_type{ none_init_v }.setRotateY(radian);
		}

		/// <summary>
		/// Z軸から行列を求める.
		/// </summary>
		/// <param name="radian">角度.</param>
		/// <returns>作成した行列を返す.</returns>
		static self_type RotationZ(Radian radian)
		{
			return self_type{ none_init_v }.setRotateZ(radian);
		}
		/// <summary>
		/// 正投影.
		/// </summary>
		/// <param name="left">.</param>
		/// <param name="right">.</param>
		/// <param name="bottom">.</param>
		/// <param name="top">.</param>
		/// <param name="zNear">近クリップ値.</param>
		/// <param name="zFar">遠クリップ値.</param>
		static self_type Orthographic(value_type left, value_type right, value_type bottom, value_type top, value_type zNear, value_type zFar)
		{
			const value_type sum_rl = (right + left);
			const value_type sum_tb = (top + bottom);
			const value_type sum_nf = (zNear + zFar);
			const value_type inv_rl = (1.0f / (right - left));
			const value_type inv_tb = (1.0f / (top - bottom));
			const value_type inv_nf = (1.0f / (zNear - zFar));
			return
			{
				(inv_rl + inv_rl), 0.0f, 0.0f, 0.0f,
				0.0f, (inv_tb + inv_tb), 0.0f, 0.0f,
				0.0f, 0.0f, (inv_nf + inv_nf), 0.0f,
				(-sum_rl * inv_rl), (-sum_tb * inv_tb), (sum_nf * inv_nf), 1.0f
			};
		}

		/// <summary>
		/// 変換行列補間.
		/// </summary>
		/// <param name="start">開始行列.</param>
		/// <param name="end">終了行列.</param>
		/// <param name="amount">補完係数<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		/// <returns>補間後の行列.</returns>
		static self_type Slerp(const self_type& start, const self_type& end, value_type amount);

		/// <summary>
		/// 前方向ベクトルと上向きのベクトルから回転行列を求める.
		/// <para>前方向を優先.</para>
		/// </summary>
		/// <param name="front">前方向ベクトル.</param>
		/// <param name="up">上方向ベクトル.</param>
		/// <returns>回転行列を返す.</returns>
		static self_type GetRotationFront(const vector3_type& front, const vector3_type& up)
		{
			// 行列は単位行列で初期化.
			self_type m = self_type::IDENTITY;

			// 左方向のベクトルを求める.
			const vector3_type left = up.cross(front).normalize();
			m.setLeft(left);

			// 上方向のベクトルを求める.
			m.setUp(front.cross(left).normalize());

			// 前方向のベクトルを求める.
			m.setFront(left.cross(up).normalize());

			return m;
		}

		/// <summary>
		/// 前方向ベクトルと上向きのベクトルから回転行列を求める.
		/// <para>上方向を優先.</para>
		/// </summary>
		/// <param name="front">前方向ベクトル.</param>
		/// <param name="up">上方向ベクトル.</param>
		/// <returns>回転行列を返す.</returns>
		static self_type GetRotationUp(const vector3_type& front, const vector3_type& up)
		{
			// 行列は単位行列で初期化.
			self_type m = self_type::IDENTITY;

			// 左方向のベクトルを求める.
			const vector3_type left = up.cross(front).normalize();
			m.setLeft(left);

			// 前方向のベクトルを求める.
			m.setFront(left.cross(up).normalize());

			// 上方向のベクトルを求める.
			m.setUp(front.cross(left).normalize());

			return m;
		}

		/// <summary>
		/// スクリーン座標変換行列を作成する.
		/// </summary>
		/// <param name="x">X座標.</param>
		/// <param name="y">Y座標.</param>
		/// <param name="width">横幅.</param>
		/// <param name="height">縦幅.</param>
		static self_type Screen(value_type x, value_type y, value_type width, value_type height)
		{
			const value_type w = width / static_cast<value_type>(2.0);
			const value_type h = height / static_cast<value_type>(2.0);
			return
			{
				w, 0.0f, 0.0f, 0.0f,
				0.0f, -h, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				w + x, h + y, 0.0f, 1.0f
			};
		}

		/// <summary>
		/// ローカル座標からスクリーン座標に変換する.
		/// </summary>
		/// <param name="position">ローカル座標.</param>
		/// <param name="screen">スクリーン変換行列.</param>
		/// <param name="projection">透視変換行列.</param>
		/// <param name="view">視野変換行列.</param>
		/// <param name="world">ワールド変換行列.</param>
		static vector3_type Project(const vector3_type& position, const self_type& screen, const self_type& projection, const self_type& view, const self_type& world = IDENTITY)
		{
			return position * world * view * projection * screen;
		}

		/// <summary>
		/// スクリーン座標からローカル座標に変換する.
		/// </summary>
		/// <param name="position">スクリーン座標.</param>
		/// <param name="screen">スクリーン変換行列.</param>
		/// <param name="projection">透視変換行列.</param>
		/// <param name="view">視野変換行列.</param>
		/// <param name="world">ワールド変換行列.</param>
		static vector3_type UnProject(const vector3_type& position, const self_type& screen, const self_type& projection, const self_type& view, const self_type& world = IDENTITY)
		{
			return position * (world * view * projection * screen).getInverse();
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
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>キャスト後のポインタを返す.</returns>
		operator value_type* () noexcept
		{
			return reinterpret_cast<value_type*>(this->v);
		}

		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>キャスト後のポインタを返す.</returns>
		operator const value_type* () const noexcept
		{
			return reinterpret_cast<const value_type*>(this->v);
		}

		/// <summary>
		/// 加算単項演算子オーバーロード.
		/// </summary>
		self_type operator + () const& noexcept
		{
			return self_type{ *this };
		}

		/// <summary>
		/// 加算単項演算子オーバーロード.
		/// </summary>
		self_type&& operator + () && noexcept
		{
			return std::move(*this);
		}

		/// <summary>
		/// 減算演算子オーバーロード.
		/// </summary>
		self_type operator - () const& noexcept
		{
			self_type result(*this);
			for (size_type i = 0; i < 16; ++i)
			{
				result.v[i] = -result.v[i];
			}
			return result;
		}

		/// <summary>
		/// 減算演算子オーバーロード.
		/// </summary>
		self_type&& operator - () && noexcept
		{
			for (size_type i = 0; i < 16; ++i)
			{
				this->v[i] = -this->v[i];
			}
			return std::move(*this);
		}

		/// <summary>
		/// 加算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">加算相手行列.</param>
		/// <returns>計算後の行列.</returns>
		self_type& operator += (const self_type& other) noexcept
		{
			for (size_type i = 0; i < 16; ++i)
			{
				this->v[i] += other.v[i];
			}
			return *this;
		}

		/// <summary>
		/// 減算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">減算相手行列.</param>
		/// <returns>計算後の行列.</returns>
		self_type& operator -= (const self_type& other) noexcept
		{
			for (size_type i = 0; i < 16; ++i)
			{
				this->v[i] -= other.v[i];
			}
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="other">乗算相手行列.</param>
		/// <returns>計算後の行列.</returns>
		self_type& operator *=(const self_type& other) noexcept
		{
			self_type result{ none_init_v };
			for (size_type i = 0; i < 4; i++)
			{
				for (size_type j = 0; j < 4; j++)
				{
					result.m[i][j] = 0;
					for (size_type k = 0; k < 4; k++)
					{
						result.m[i][j] += m[i][k] * other.m[k][j];
					}
				}
			}

			return *this = result;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="s">乗算相手.</param>
		/// <returns>計算後の行列.</returns>
		self_type& operator *= (value_type s) noexcept
		{
			for (size_type i = 0; i < 16; ++i)
			{
				this->v[i] *= s;
			}
			return *this;
		}

		/// <summary>
		/// 除算代入演算子オーバーロード.
		/// </summary>
		/// <param name="s">除算相手.</param>
		/// <returns>計算後の行列.</returns>
		self_type& operator /= (value_type s)
		{
			*this *= (1.0f / s);
			return *this;
		}

		/// <summary>
		/// 加算2項演算子オーバーロード.
		/// </summary>
		self_type operator + (const self_type& right) const&
		{
			return self_type(*this) += right;
		}

		/// <summary>
		/// 加算2項演算子オーバーロード.
		/// </summary>
		self_type&& operator + (const self_type& right)&&
		{
			return std::move(*this += right);
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		self_type operator - (const self_type& right) const&
		{
			return self_type(*this) -= right;
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		self_type&& operator - (const self_type& right)&&
		{
			return std::move(*this -= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		friend vector3_type operator * (const vector3_type& v, const self_type& right)
		{
			return right.transform(v);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		self_type operator * (const self_type& right) const& noexcept
		{
			return self_type(*this) *= right;
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		self_type&& operator * (const self_type& right) && noexcept
		{
			return std::move(*this *= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		self_type operator * (const value_type right) const& noexcept
		{
			return self_type(*this) *= right;
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		self_type&& operator * (const value_type right) && noexcept
		{
			return std::move(*this *= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		friend self_type operator * (const value_type left, const self_type& right) noexcept
		{
			return right * left;
		}

		/// <summary>
		/// 除算2項演算子オーバーロード.
		/// </summary>
		self_type operator / (const value_type s) const&
		{
			return self_type(*this) *= (1.f / s);
		}

		/// <summary>
		/// 除算2項演算子オーバーロード.
		/// </summary>
		self_type&& operator / (const value_type s)&&
		{
			return std::move(*this *= (1.f / s));
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺.</param>
		/// <returns>要素が違っていたら真を返す.</returns>
		constexpr bool operator == (const self_type& right) const noexcept
		{
			for (size_type i = 0; i < 16; ++i)
			{
				if (this->v[i] != right.v[i]) return false;
			}
			return	true;
		}

		/// <summary>
		/// 比較2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">右辺.</param>
		/// <returns>要素が違っていたら真を返す.</returns>
		constexpr bool operator != (const self_type& right) const noexcept
		{
			return !(*this == right);
		}

	};

}
