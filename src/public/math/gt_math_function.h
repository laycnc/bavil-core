#pragma once

#include <cmath>
#include <algorithm>
#include "gt_type.h"
#include "gt_utility.h"
#include "math/gt_angle.h"

namespace gt::math
{

	/// <summary>
	/// 範囲内か判定.
	/// </summary>
	/// <param name="value">値</param>
	/// <param name="low">最小値</param>
	/// <param name="high">最大値</param>
	/// <returns>範囲内なら真を返す.</returns>
	template<class Ty>
	constexpr inline bool IsRange(Ty const& value, Ty const& low, Ty const& high) noexcept
	{
		return (low <= value) && (value <= high);
	}

	/// <summary>
	/// 値をしきい値の間に収める.
	/// </summary>
	/// <param name="value">値</param>
	/// <param name="low">最小値</param>
	/// <param name="high">最大値</param>
	/// <returns>クランプ後の値を返す.</returns>
	template<class Ty>
	constexpr inline auto Clamp(const Ty& value, const Ty& low, const Ty& high) noexcept
		-> decltype(low < high, Ty())
	{
		return std::max(low, std::min(value, high));
	}

	/// <summary>
	/// 値を0.0~1.0の間に収める.
	/// </summary>
	/// <param name="value">値</param>
	/// <returns>クランプ後の値を返す.</returns>
	template<class Ty>
	constexpr inline auto Clamp01(Ty const& value) noexcept
		-> decltype(value < value, Ty())
	{
		return Clamp(value, static_cast<Ty>(0), static_cast<Ty>(1));
	}

	/// <summary>
	/// 値をループさせる.
	/// </summary>
	/// <param name="_value">値.</param>
	/// <param name="_low">最小値.</param>
	/// <param name="_high">最大値.</param>
	template<class Ty>
	constexpr inline const Ty& Loop(const Ty& _value, const Ty& _low, const Ty& _high) noexcept
	{
		return _value < _low ? _high : _value > _high ? _low : _value;
	}

	/// <summary>
	/// 要素を入れ替える.
	/// </summary>
	/// <param name="first">最初の要素</param>
	/// <param name="second">次の要素</param>
	/// <returns></returns>
	template<class Ty>
	inline void Swap(Ty& first, Ty& second) noexcept
	{
		auto temp = first;
		first = second;
		second = temp;
	}

	/// <summary>
	/// 値が正なら1、負なら-1、ゼロなら0を求める.
	/// </summary>
	/// <param name="value">値</param>
	/// <returns>正なら1,負なら-1,ゼロなら0を返す.</returns>
	template<class Ty>
	constexpr inline Ty Zsgn(Ty const& value) noexcept
	{
		return (((value) < static_cast<Ty>(0)) ? static_cast<Ty>(-1) : (value) > static_cast<Ty>(0) ? static_cast<Ty>(1) : static_cast<Ty>(0));
	}

	/// <summary>
	/// 値が正かゼロなら1,負なら-1を求める.
	/// </summary>
	/// <param name="value">値</param>
	/// <returns>正なら1,負なら-1,ゼロなら0を返す.</returns>
	template<class Ty>
	constexpr inline Ty Sgn(Ty const& value) noexcept
	{
		static_assert(std::is_signed<Ty>::value, "not signed error");
		return (value < static_cast<Ty>(0)) ? (static_cast<Ty>(-1)) : (static_cast<Ty>(1));
	}

	/// <summary>
	/// 値を2乗する.
	/// </summary>
	/// <typeparam name="T">計算式の型</typeparam>
	/// <param name="value">値</param>
	/// <returns>計算後の数値を返す.</returns>
	template<class Ty>
	constexpr inline Ty Square(Ty const& value) noexcept
	{
		return std::pow(value, 2);
	}

	/// <summary>
	/// 線形補間.
	/// </summary>
	/// <typeparam name="U">補間係数型</typeparam>
	/// <param name="start">開始値.</param>
	/// <param name="end">終了値.</param>
	/// <param name="amount">補完係数.<para>0.0(開始値)～1.0(終了値)</para>.</param>
	/// <returns>補間後の値を返す.</returns>
	template<class Ty, class U>
	constexpr Ty Lerp(Ty const& start, Ty const& end, const U& amount)noexcept
	{
		return start * (static_cast<U>(1) - amount) + end * amount;
	}

	/// <summary>
	/// 線形補完.
	/// </summary>
	/// <param name="start">開始ベクトル.</param>
	/// <param name="end">終了ベクトル.</param>
	/// <param name="amount">補完係数<para>.0.0(開始値)～1.0(終了値)</para>.</param>
	template<class Ty, class U>
	CONSTEXPR_CPP20 Ty LerpLoop(const Ty& start, Ty const& end, U const& amount) noexcept
	{
		return Lerp(start, end, std::sin(amount) * static_cast<U>(0.5) + static_cast<U>(0.5));
	}

	/// <summary>
	/// 2次補間する.
	/// </summary>
	/// <typeparam name="U">補間係数型</typeparam>
	/// <param name="v0">値0.</param>
	/// <param name="v1">値1.</param>
	/// <param name="v2">値2.</param>
	/// <param name="amount">補完係数<para>.0.0(開始値)～1.0(終了値)</para>.</param>
	/// <returns>補間後の値を返す.</returns>
	template<class Ty, class U>
	constexpr Ty Quadratic(Ty const& v0, Ty const& v1, Ty const& v2, U const& amount) noexcept
	{
		return (v0) * (static_cast<U>(1) - amount) * (static_cast<U>(1) - amount) +
			static_cast<U>(2) * (v1) * (amount) * (static_cast<U>(1) - amount) +
			(v2) * (amount) * (amount);
	}

}
