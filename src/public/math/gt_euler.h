/// @file		gtlib/math/gt_euler.hpp
/// @date		2015/01/30
/// @brief		オイラー角構造体
/// @author		shouta_takemura
#pragma once


#include <gtlib/gt_type.hpp>


/// <summary>gtlib名前空間.</summary>
namespace gt
{
	/// <summary>数学名前空間.</summary>
	namespace math
	{

#if 0

		/// <summary>実装</summary>
		namespace detail
		{

			template<class Derived>
			struct euler_base
			{
			public:
				f32	x;
				f32	y;
				f32	z;

				/// <summary>
				/// コンストラクタ.
				/// </summary>
				constexpr euler_base() noexcept
					: euler_base(0.f, 0.f, 0.f)
				{}

				/// <summary>
				/// コンストラクタ.
				/// </summary>
				/// <param name="_x">X軸周りのラジアン.</param>
				/// <param name="_y">Y軸周りのラジアン.</param>
				/// <param name="_z">Z軸周りのラジアン.</param>
				constexpr euler_base(f32 _x, f32 _y, f32 _z) noexcept
					: x{ _x }, y{ _y }, z{ _z }
				{}

				/// <summary>
				/// コンストラクタ.
				/// </summary>
				/// <param name="_x">X軸の角度.</param>
				/// <param name="_y">Y軸の角度.</param>
				/// <param name="_z">Z軸の角度.</param>
				constexpr euler_base(Radian _x, Radian _y, Radian _z) noexcept
					: euler_base(_x.get(), _y.get(), _z.get())
				{}

				/// <summary>
				/// コンストラクタ.
				/// </summary>
				/// <param name="_x">X軸の角度.</param>
				/// <param name="_y">Y軸の角度.</param>
				/// <param name="_z">Z軸の角度.</param>
				constexpr euler_base(Degree _x, Degree _y, Degree _z) noexcept
					: euler_base(ToRadian(_x), ToRadian(_y), ToRadian(_z))
				{}

				/// <summary>
				/// 加算演算子オーバーロード.
				/// </summary>
				/// <param name="other">加算対象.</param>
				/// <returns>加算結果.</returns>
				Derived& operator += (const Derived& other) noexcept
				{
					this->x += other.x;
					this->y += other.y;
					this->z += other.z;
					return reinterpret_cast<Derived&>(*this);
				}

				/// <summary>
				/// 減算演算子オーバーロード.
				/// </summary>
				/// <param name="other">減算対象.</param>
				/// <returns>減算結果.</returns>
				Derived& operator -= (const Derived& other) noexcept
				{
					this->x -= other.x;
					this->y -= other.y;
					this->z -= other.z;
					return reinterpret_cast<Derived&>(*this);
				}

				/// <summary>
				/// 加算演算子オーバーロード.
				/// </summary>
				/// <param name="right">右辺値.</param>
				/// <returns></returns>
				constexpr Derived operator + (const Derived& right) const & noexcept
				{
					return Derived
					{
						this->x + right.x,
						this->y + right.y,
						this->z + right.z
					};
				}

				/// <summary>
				/// 加算演算子オーバーロード.
				/// </summary>
				/// <param name="right">右辺値.</param>
				/// <returns></returns>
				Derived&& operator + (const Derived& right) && noexcept
				{
					return move(*this += right);
				}

				/// <summary>
				/// 減算演算子オーバーロード.
				/// </summary>
				/// <param name="right">右辺値.</param>
				/// <returns></returns>
				constexpr Derived operator - (const Derived& right) const & noexcept
				{
					return Derived
					{
						this->x - right.x,
						this->y - right.y,
						this->z - right.z
					};
				}

				/// <summary>
				/// 減算演算子オーバーロード.
				/// </summary>
				/// <param name="right">右辺値.</param>
				/// <returns></returns>
				Derived&& operator - (const Derived& right) && noexcept
				{
					return move(*this -= right);
				}

				constexpr bool operator == (const Derived& right) const noexcept
				{
					return 
					{
						this->x == right.x &&
						this->y == right.y && 
						this->z == right.z
					};
				}

				constexpr bool operator != (const Derived& right) const noexcept
				{
					return !(*this == right);
				}

				Derived& identity() noexcept
				{
					this->x = 0.f;
					this->y = 0.f;
					this->z = 0.f;
					return reinterpret_cast<Derived&>(*this);
				}

			};


			struct euler_xyz
				: public euler_base<euler_xyz>
			{
				using euler_base::euler_base;

				constexpr euler_xyz() noexcept
					: euler_base()
				{}

				constexpr euler_xyz(const euler_base& other) noexcept
					: euler_base(other)
				{}

				Quaternion toQuaternion() const noexcept
				{
					return
					{
						Quaternion(Vector3::UNIT_X, Radian::Create(this->x)) *
						Quaternion(Vector3::UNIT_Y, Radian::Create(this->y)) *
						Quaternion(Vector3::UNIT_Z, Radian::Create(this->z))
					};
				}
			};

			struct euler_xzy
				: public euler_base<euler_xzy>
			{
				using euler_base::euler_base;

				constexpr euler_xzy() noexcept
					: euler_base()
				{}

				constexpr euler_xzy(const euler_base& other) noexcept
					: euler_base(other)
				{}

				Quaternion toQuaternion() const noexcept
				{
					return
					{
						Quaternion(Vector3::UNIT_X, Radian::Create(this->x)) *
						Quaternion(Vector3::UNIT_Z, Radian::Create(this->z)) *
						Quaternion(Vector3::UNIT_Y, Radian::Create(this->y))
					};
				}
			};

			struct euler_yxz
				: public euler_base<euler_yxz>
			{
				using euler_base::euler_base;

				constexpr euler_yxz() noexcept
					: euler_base()
				{}
				
				constexpr euler_yxz(const euler_base& other) noexcept
					: euler_base(other)
				{}

				Quaternion toQuaternion() const noexcept
				{
					return
					{
						Quaternion(Vector3::UNIT_Y, Radian::Create(this->y)) *
						Quaternion(Vector3::UNIT_X, Radian::Create(this->x)) *
						Quaternion(Vector3::UNIT_Z, Radian::Create(this->z))
					};
				}
			};


			struct euler_yzx
				: public euler_base<euler_yzx>
			{
				using euler_base::euler_base;

				constexpr euler_yzx() noexcept
					: euler_base()
				{}

				constexpr euler_yzx(const euler_base& other) noexcept
					: euler_base(other)
				{}

				Quaternion toQuaternion() const noexcept
				{
					return
					{
						Quaternion(Vector3::UNIT_Y, Radian::Create(this->y)) *
						Quaternion(Vector3::UNIT_Z, Radian::Create(this->z)) *
						Quaternion(Vector3::UNIT_X, Radian::Create(this->x)) 
					};
				}
			};

			struct euler_zxy
				: public euler_base<euler_zxy>
			{
				using euler_base::euler_base;

				constexpr euler_zxy() noexcept
					: euler_base()
				{}

				constexpr euler_zxy(const euler_base& other) noexcept
					: euler_base(other)
				{}

				Quaternion toQuaternion() const noexcept
				{
					return
					{
						Quaternion(Vector3::UNIT_Z, Radian::Create(this->z)) *
						Quaternion(Vector3::UNIT_X, Radian::Create(this->x)) * 
						Quaternion(Vector3::UNIT_Y, Radian::Create(this->y)) 
					};
				}
			};

			struct euler_zyx
				: public euler_base<euler_zyx>
			{
				using euler_base::euler_base;

				constexpr euler_zyx() noexcept
					: euler_base()
				{}

				constexpr euler_zyx(const euler_base& other) noexcept
					: euler_base(other)
				{}

				Quaternion toQuaternion() const noexcept
				{
					return
					{
						Quaternion(Vector3::UNIT_Z, Radian::Create(this->z)) *
						Quaternion(Vector3::UNIT_Y, Radian::Create(this->y)) *
						Quaternion(Vector3::UNIT_X, Radian::Create(this->x))
					};
				}
			};

		}

#endif

		struct Euler
		{
			using self_type = Euler;
			using value_type = f32;

			value_type	pitch;
			value_type	yaw;
			value_type	roll;

			/// <summary>
			/// 単位角度.
			/// </summary>
			//static const Euler IDENTITY;

			/// <summary>
			/// コンストラクタ.
			/// </summary>
			constexpr Euler( void ) noexcept
				: pitch()
				, yaw()
				, roll()
			{ }

			explicit Euler( none_init_t ) noexcept { }

			/// <summary>
			/// コンストラクタ.
			/// </summary>
			/// <param name="pitch_">X軸周りの回転量.</param>
			/// <param name="yaw_">Y軸周りの回転量.</param>
			/// <param name="roll_">Z軸周りの回転量.</param>
			constexpr Euler( value_type pitch_, value_type yaw_, value_type roll_ ) noexcept
				: pitch( pitch_ )
				, yaw( yaw_ )
				, roll( roll_ )
			{ }

			self_type& identity( void ) noexcept
			{
				this->pitch = this->yaw = this->roll = static_cast<value_type>( 0.0 );
				return *this;
			}



		};

	} //! namespace math


} //! namespce gt


  /********** End of File ******************************************************/