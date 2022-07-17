#pragma once

#include <cmath>
#include "bavil_type.h"

namespace bavil::math
{

	class Degree;
	class Radian;

	template<class Ty = f32>
	constexpr Ty PI = static_cast<Ty>(3.14159265358979323846264338327950288);
	template<class Ty = f32>
	constexpr Ty N2PI = PI<f32> * static_cast<Ty>(2.0);
	template<class Ty = f32>
	constexpr Ty N1DIVPI = static_cast<Ty>(1.0) / PI<Ty>;
	template<class Ty = f32>
	constexpr Ty N1DIV2PI = static_cast<Ty>(1.0) / N2PI<Ty>;
	template<class Ty = f32>
	constexpr Ty PIDIV2 = PI<Ty> / static_cast<Ty>(2.0);
	template<class Ty = f32>
	constexpr Ty PIDIV4 = PI<Ty> / static_cast<Ty>(4.0);


	/// <summary>
	/// ラジアン型
	/// </summary>
	class Radian
	{
		f32 m_value;

	public:
		constexpr Radian(f32 radian) noexcept
			: m_value(radian)
		{}

		/// <summary>
		/// デフォルトコンストラクタ.
		/// </summary>
		constexpr inline Radian() noexcept
			: m_value()
		{}

		/// <summary>
		/// コンストラクタ.
		/// <para>角度からラジアンを作成</para>
		/// </summary>
		/// <param name="degree">角度.</param>
		constexpr inline explicit Radian(Degree degree) noexcept;

		/// <summary>
		/// 内部の値を取得.
		/// </summary>
		/// <returns></returns>
		constexpr inline f32 get() const noexcept
		{
			return this->m_value;
		}

		constexpr inline Radian operator + ()const noexcept
		{
			return *this;
		}
		constexpr Radian operator - ()const noexcept
		{
			return Radian{ -this->m_value };
		}
		inline Radian& operator = (Degree degree) noexcept;
		Radian& operator += (Radian other) noexcept
		{
			this->m_value += other.m_value;
			return *this;
		}
		Radian& operator += (f32 other) noexcept
		{
			this->m_value += other;
			return *this;
		}
		Radian& operator -= (Radian other) noexcept
		{
			this->m_value -= other.m_value;
			return *this;
		}
		Radian& operator -= (f32 other) noexcept
		{
			this->m_value -= other;
			return *this;
		}
		Radian& operator *= (Radian other) noexcept
		{
			this->m_value *= other.m_value;
			return *this;
		}
		Radian& operator /= (Radian other) noexcept
		{
			this->m_value /= other.m_value;
			return *this;
		}
		constexpr Radian operator + (Radian right) const noexcept
		{
			return Radian{ this->m_value + right.m_value };
		}
		constexpr Radian operator - (Radian right) const noexcept
		{
			return Radian{ this->m_value - right.m_value };
		}
		constexpr Radian operator * (Radian right) const noexcept
		{
			return Radian{ this->m_value * right.m_value };
		}
		constexpr Radian operator * (f32 right) const noexcept
		{
			return Radian{ this->m_value * right };
		}
		constexpr Radian operator / (Radian right) const noexcept
		{
			return Radian{ this->m_value / right.m_value };
		}
		constexpr Radian operator / (f32 right) const noexcept
		{
			return Radian{ this->m_value / right };
		}
		constexpr bool operator == (const Radian& right) const noexcept
		{
			return this->m_value == right.m_value;
		}
		constexpr bool operator != (const Radian& right) const noexcept
		{
			return this->m_value != right.m_value;
		}
		constexpr bool operator < (const Radian& right) const noexcept
		{
			return this->m_value < right.m_value;
		}
		constexpr bool operator <= (const Radian& right) const noexcept
		{
			return this->m_value < right.m_value;
		}
		constexpr bool operator > (const Radian& right) const noexcept
		{
			return this->m_value > right.m_value;
		}
		constexpr bool operator >= (const Radian& right) const noexcept
		{
			return this->m_value > right.m_value;
		}

		/// <summary>
		/// サイン.
		/// </summary>
		/// <param name="radian">ラジアン.</param>
		/// <returns></returns>
		friend inline f32 Sin(Radian radian) noexcept
		{
			return std::sin(radian.m_value);
		}

		/// <summary>
		/// コサイン.
		/// </summary>
		/// <param name="radian">ラジアン.</param>
		/// <returns></returns>
		friend inline f32 Cos(Radian radian) noexcept
		{
			return std::cos(radian.m_value);
		}

		/// <summary>
		/// タンジェント.
		/// </summary>
		/// <param name="radian">ラジアン.</param>
		/// <returns></returns>
		friend inline f32 Tan(Radian radian) noexcept
		{
			return std::tan(radian.m_value);
		}

		/// <summary>
		/// 逆サイン.
		/// </summary>
		/// <param name="radian">ラジアン.</param>
		/// <returns></returns>
		friend inline f32 Asin(Radian radian) noexcept
		{
			return std::asin(radian.m_value);
		}

		/// <summary>
		/// 逆コサイン.
		/// </summary>
		/// <param name="radian">ラジアン.</param>
		/// <returns></returns>
		friend inline f32 Acos(Radian radian) noexcept
		{
			return std::acos(radian.m_value);
		}

		/// <summary>
		/// 逆タンジェント.
		/// </summary>
		/// <param name="radian">ラジアン.</param>
		/// <returns></returns>
		friend inline f32 Atan(Radian radian) noexcept
		{
			return std::atan(radian.m_value);
		}

		/// <summary>
		/// 逆タンジェント.
		/// </summary>
		/// <param name="y">The y.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend inline f32 Atan(Radian y, Radian x) noexcept
		{
			return std::atan2(y.m_value, x.m_value);
		}

		friend inline void SinCos(Radian& out_sin, Radian& out_cos, Radian _value) noexcept
		{
			constexpr f32 PIDIV2 = 1.570796327f;

			// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
			const f32 quotient = static_cast<f32>(static_cast<int>(PI<f32> * _value.get() + _value.get() >= 0.f ? 0.5f : -0.5f));

			f32 y = _value.get() - PI<f32> * quotient;

			// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
			f32 sign;
			if (y > PIDIV2)
			{
				y = PI<f32> - y;
				sign = -1.0f;
			}
			else if (y < -PIDIV2)
			{
				y = -PI<f32> - y;
				sign = -1.0f;
			}
			else
			{
				sign = +1.0f;
			}

			const f32 y2 = y * y;

			// 11-degree minimax approximation
			out_sin.m_value = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

			// 10-degree minimax approximation
			const f32 p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
			out_cos.m_value = sign * p;
		}

		/// <summary>
		/// 浮動小数点型から角度を生成.
		/// </summary>
		/// <param name="radian">ラジアン.</param>
		/// <returns></returns>
		static constexpr inline Radian Create(f32 radian) noexcept
		{
			return Radian(radian);
		}

		friend inline constexpr Degree ToDegree(Radian) noexcept;
		friend inline constexpr Radian ToRadian(Degree) noexcept;
		friend constexpr Radian operator ""_rad(floating_identifier) noexcept;
		friend constexpr Radian operator ""_rad(uint_identifier) noexcept;
	};

	/// <summary>
	/// ラジアンリテラル.
	/// </summary>
	/// <param name="radian">ラジアン値.</param>
	/// <returns>ラジアンを返す</returns>
	constexpr Radian operator ""_rad(floating_identifier radian) noexcept
	{
		return Radian{ static_cast<f32>(radian) };
	}

	/// <summary>
	/// ラジアンリテラル.
	/// </summary>
	/// <param name="radian">ラジアン値.</param>
	/// <returns>ラジアンを返す</returns>
	constexpr Radian operator ""_rad(uint_identifier radian) noexcept
	{
		return operator""_rad(static_cast<floating_identifier>(radian));
	}

	/// <summary>
	/// 度数クラス
	/// </summary>
	class Degree
	{
		f32 m_value;

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="degree">度数.</param>
		constexpr Degree(f32 degree) noexcept
			: m_value(degree)
		{}
	public:

		/// <summary>
		/// デフォルトコンストラクタ.
		/// </summary>
		constexpr Degree() noexcept
			: m_value()
		{}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="radian">ラジアン .</param>
		constexpr explicit Degree(Radian radian) noexcept;

		/// <summary>
		/// 内部の値を取得.
		/// </summary>
		/// <returns></returns>
		constexpr inline f32 get() const noexcept
		{
			return this->m_value;
		}

		constexpr Degree operator + ()const noexcept
		{
			return *this;
		}
		constexpr Degree operator - ()const noexcept
		{
			return Degree{ -this->m_value };
		}
		inline Degree& operator = (Radian radian) noexcept;
		inline Degree& operator += (Degree other) noexcept
		{
			this->m_value += other.m_value;
			return *this;
		}
		inline Degree& operator -= (Degree other) noexcept
		{
			this->m_value -= other.m_value;
			return *this;
		}
		inline Degree& operator *= (Degree other) noexcept
		{
			this->m_value *= other.m_value;
			return *this;
		}
		inline Degree& operator /= (Degree other) noexcept
		{
			this->m_value /= other.m_value;
			return *this;
		}
		constexpr inline Degree operator + (Degree right) const noexcept
		{
			return Degree{ this->m_value + right.m_value };
		}
		constexpr inline Degree operator - (Degree right) const noexcept
		{
			return Degree{ this->m_value - right.m_value };
		}
		constexpr inline Degree operator * (Degree right) const noexcept
		{
			return Degree{ this->m_value * right.m_value };
		}
		constexpr inline Degree operator * (f32 right) const noexcept
		{
			return Degree{ this->m_value * right };
		}
		constexpr inline Degree operator / (Degree right) const noexcept
		{
			return Degree{ this->m_value / right.m_value };
		}
		constexpr inline Degree operator / (f32 right) const noexcept
		{
			return Degree{ this->m_value / right };
		}
		constexpr inline bool operator == (const Degree& right) const noexcept
		{
			return this->m_value == right.m_value;
		}
		constexpr inline bool operator != (const Degree& right) const noexcept
		{
			return this->m_value != right.m_value;
		}
		constexpr inline bool operator < (const Degree& right) const noexcept
		{
			return this->m_value < right.m_value;
		}
		constexpr inline bool operator <= (const Degree& right) const noexcept
		{
			return this->m_value < right.m_value;
		}
		constexpr inline bool operator > (const Degree& right) const noexcept
		{
			return this->m_value > right.m_value;
		}
		constexpr inline bool operator >= (const Degree& right) const noexcept
		{
			return this->m_value > right.m_value;
		}

		/// <summary>
		/// 正規化する.
		/// </summary>
		/// <returns></returns>
		static constexpr Degree Normalize(Degree degree) noexcept
		{
			return Degree(degree.m_value - static_cast<int>(degree.m_value / 360) * 360.f);
		}

		/// <summary>
		/// 角度の正規化.
		/// <para>正数のみを返す.</para>
		/// </summary>
		/// <param name="angle">角度.</param>
		static inline Degree UnsignedNormalize(Degree degree) noexcept;

		/// <summary>
		/// 角度差を求める.
		/// </summary>
		/// <param name="my">自身の角度</param>
		/// <param name="target">対象の角度</param>
		/// <returns>角度を返す</returns>
		static inline Degree Subtract(Degree my, Degree target) noexcept;

		/// <summary>
		/// 浮動小数点型から角度を生成.
		/// </summary>
		/// <param name="degree">角度.</param>
		/// <returns></returns>
		static constexpr inline Degree Create(f32 degree) noexcept
		{
			return Degree(degree);
		}

		friend inline constexpr Degree ToDegree(Radian) noexcept;
		friend inline constexpr Radian ToRadian(Degree) noexcept;
		friend constexpr Degree operator ""_deg(floating_identifier) noexcept;
		friend constexpr Degree operator ""_deg(uint_identifier) noexcept;
	};

	/// <summary>
	/// 度数リテラル.
	/// </summary>
	/// <param name="radian">度数値.</param>
	/// <returns>度数を返す</returns>
	constexpr Degree operator ""_deg(floating_identifier degree) noexcept
	{
		return Degree{ static_cast<f32>(degree) };
	}

	/// <summary>
	/// 度数リテラル.
	/// </summary>
	/// <param name="radian">度数値.</param>
	/// <returns>度数を返す</returns>
	constexpr Degree operator ""_deg(uint_identifier degree) noexcept
	{
		return operator""_deg(static_cast<floating_identifier>(degree));
	}

	/// <summary>
	/// 度数に変換する.
	/// </summary>
	/// <param name="degree">ラジアン.</param>
	/// <returns>度数を返す</returns>
	inline constexpr Degree ToDegree(Radian radian) noexcept
	{
		return Degree(radian.m_value * 180.f * PI<f32>);
	}

	/// <summary>
	/// ラジアンに変換する.
	/// </summary>
	/// <param name="degree">度数.</param>
	/// <returns>ラジアンを返す</returns>
	inline constexpr Radian ToRadian(Degree degree) noexcept
	{
		return Radian(degree.m_value * PI<f32> / 180.f);
	}


	/// <summary>
	/// コンストラクタ.
	/// <para>角度からラジアンを作成</para>
	/// </summary>
	/// <param name="degree">角度.</param>
	constexpr Radian::Radian(Degree degree) noexcept
		: m_value(ToRadian(degree).m_value)
	{}

	inline Degree& Degree::operator = (Radian radian) noexcept
	{
		return *this = Degree(radian);
	}

	/// <summary>
	/// コンストラクタ.
	/// </summary>
	/// <param name="radian">ラジアン .</param>
	constexpr Degree::Degree(Radian radian) noexcept
		: m_value(ToDegree(radian).m_value)
	{}

	inline Radian& Radian::operator = (Degree degree) noexcept
	{
		return *this = Radian(degree);
	}

	/// <summary>
	/// 角度の正規化.
	/// <para>正数のみを返す.</para>
	/// </summary>
	/// <param name="angle">角度.</param>
	inline Degree Degree::UnsignedNormalize(Degree degree) noexcept
	{
		constexpr Degree _zero = 0_deg;
		degree = Normalize(degree);
		if (degree < _zero)
		{
			return Degree(degree.m_value + 360.f);
		}
		return degree;
	}

	/// <summary>
	/// 角度差を求める.
	/// </summary>
	/// <param name="my">自身の角度</param>
	/// <param name="target">対象の角度</param>
	/// <returns>角度を返す</returns>
	inline Degree Degree::Subtract(Degree my, Degree target) noexcept
	{
		Degree result = Normalize(target - my);

		if (result > 180_deg)
		{
			result -= 360_deg;
		}
		else if (result < -360_deg)
		{
			result += 360_deg;
		}
		return result;
	}

}