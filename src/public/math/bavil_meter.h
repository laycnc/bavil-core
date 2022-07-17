#pragma once

#include "bavil_type.h"

namespace bavil::math
{

	/// <summary>
	/// メータークラス
	/// </summary>
	class Meter
	{
		f32 m_distance;
	public:
		/// <summary>
		/// デフォルトコンストラクタ.
		/// </summary>
		constexpr Meter() noexcept
			: m_distance{ 0.f }
		{}
		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="distance">メートル.</param>
		constexpr Meter(f32 distance) noexcept
			: m_distance(distance)
		{}
		/// <summary>
		/// 内部データを取得.
		/// </summary>
		/// <returns></returns>
		constexpr f32 get() const noexcept
		{
			return this->m_distance;
		}
		constexpr operator f32() const noexcept
		{
			return this->m_distance;
		}
		constexpr Meter operator + () const noexcept
		{
			return *this;
		}
		constexpr Meter operator - () const noexcept
		{
			return Meter{ -this->m_distance };
		}
		constexpr Meter operator + (const Meter& other) const noexcept
		{
			return Meter(this->m_distance + other.m_distance);
		}
		constexpr Meter operator + (f32 other) const noexcept
		{
			return Meter(this->m_distance + other);
		}
		constexpr Meter operator - (const Meter& other) const noexcept
		{
			return Meter(this->m_distance - other.m_distance);
		}
		constexpr Meter operator - (f32 other) const noexcept
		{
			return Meter(this->m_distance - other);
		}
		constexpr Meter operator * (const Meter& other) const noexcept
		{
			return Meter(this->m_distance * other.m_distance);
		}
		constexpr Meter operator * (f32 other) const noexcept
		{
			return Meter(this->m_distance * other);
		}
		constexpr Meter operator / (const Meter& other) const noexcept
		{
			return Meter(this->m_distance / other.m_distance);
		}
		constexpr Meter operator / (f32 other) const noexcept
		{
			return Meter(this->m_distance / other);
		}
		constexpr bool operator == (const Meter& _right) const noexcept
		{
			return this->m_distance == _right.m_distance;
		}
		constexpr bool operator != (const Meter& _right) const noexcept
		{
			return !(*this == _right);
		}
		friend constexpr Meter operator ""_m(long double distance) noexcept;
		friend constexpr Meter operator ""_m(unsigned long long int distance) noexcept;
		friend constexpr Meter operator ""_mm(long double distance) noexcept;
		friend constexpr Meter operator ""_mm(unsigned long long int distance) noexcept;
		friend constexpr Meter operator ""_cm(long double distance) noexcept;
		friend constexpr Meter operator ""_cm(unsigned long long int distance) noexcept;
		friend constexpr Meter operator ""_km(long double distance) noexcept;
		friend constexpr Meter operator ""_km(unsigned long long int distance) noexcept;

	};

	/// <summary>
	/// メーターリテラル.
	/// </summary>
	/// <param name="distance">距離.</param>
	/// <returns>メートルを返す</returns>
	constexpr Meter operator ""_m(long double distance) noexcept
	{
		return Meter{ static_cast<f32>(distance) };
	}
	/// <summary>
	/// メーターリテラル.
	/// </summary>
	/// <param name="distance">距離.</param>
	/// <returns>メートルを返す</returns>
	constexpr Meter operator ""_m(unsigned long long int distance) noexcept
	{
		return operator""_m(static_cast<long double>(distance));
	}
	/// <summary>
	/// ミリメートルリテラル.
	/// </summary>
	/// <param name="distance">距離.</param>
	/// <returns>変換後のメートルを返す</returns>
	constexpr Meter operator ""_mm(long double distance) noexcept
	{
		return operator""_m(distance * 0.001);
	}
	/// <summary>
	/// ミリメートルリテラル.
	/// </summary>
	/// <param name="distance">距離.</param>
	/// <returns>変換後のメートルを返す</returns>
	constexpr Meter operator ""_mm(unsigned long long int distance) noexcept
	{
		return operator""_mm(static_cast<long double>(distance));
	}
	/// <summary>
	/// センチメートルリテラル.
	/// </summary>
	/// <param name="distance">距離.</param>
	/// <returns>変換後のメートルを返す</returns>
	constexpr Meter operator ""_cm(long double distance) noexcept
	{
		return operator""_m(distance * 0.01);
	}
	/// <summary>
	/// センチメートルリテラル.
	/// </summary>
	/// <param name="distance">距離.</param>
	/// <returns>変換後のメートルを返す</returns>
	constexpr Meter operator ""_cm(unsigned long long int distance) noexcept
	{
		return operator""_cm(static_cast<long double>(distance));
	}
	/// <summary>
	/// キロメートルリテラル.
	/// </summary>
	/// <param name="distance">距離.</param>
	/// <returns>変換後のメートルを返す</returns>
	constexpr Meter operator ""_km(long double distance) noexcept
	{
		return operator""_m(distance * 1000.0);
	}
	/// <summary>
	/// キロメートルリテラル.
	/// </summary>
	/// <param name="distance">距離.</param>
	/// <returns>変換後のメートルを返す</returns>
	constexpr Meter operator ""_km(unsigned long long int distance) noexcept
	{
		return operator""_km(static_cast<long double>(distance));
	}

}
