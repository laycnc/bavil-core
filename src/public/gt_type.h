#pragma once
#include <cstdint>
#include <cstddef>
/// <summary>gtlib名前空間.</summary>
namespace gt
{


#define CONSTEXPR_CPP11 constexpr
#define CONSTEXPR_CPP14 constexpr
#define CONSTEXPR_CPP20 


	/// <summary>
	/// 符号付き8ビット型.
	/// </summary>
	using s8 = std::int8_t;
	/// <summary>
	/// 符号付き816ット型.
	/// </summary>	
	using s16 = std::int16_t;
	/// <summary>
	/// 符号付き32ビット型.
	/// </summary>
	using s32 = std::int32_t;
	/// <summary>
	/// 符号付き64ビット型.
	/// </summary>
	using s64 = std::int64_t;
	/// <summary>
	/// 符号なし8ビット型.
	/// </summary>
	using u8 = std::uint8_t;
	/// <summary>
	/// 符号なし16ビット型.
	/// </summary>	
	using u16 = std::uint16_t;
	/// <summary>
	/// 符号なし32ビット型.
	/// </summary>
	using u32 = std::uint32_t;
	/// <summary>
	/// 符号なし64ビット型.
	/// </summary>
	using u64 = std::uint64_t;

	/// <summary>
	/// 32ビット浮動小数点型.
	/// </summary>
	using f32 = float;

	/// <summary>
	/// 64ビット浮動小数点型.
	/// </summary>
	using f64 = double;

	/// <summary>
	/// サイズ型.
	/// </summary>
	using size_t = std::size_t;

	/// <summary>
	/// 符号有りポインタ型.
	/// </summary>
	using intptr_t = std::intptr_t;

	/// <summary>
	/// 符号無しポインタ型.
	/// </summary>
	using uintptr_t = std::uintptr_t;

	/// <summary>
	/// 符号なしバイト型.
	/// </summary>
	using byte = u8;

	/// <summary>
	/// 符号なしバイト型.
	/// </summary>
	using byte2 = u16;

	/// <summary>
	/// 符号なしバイト型.
	/// </summary>
	using byte4 = u32;

	using uint_identifier = unsigned long long;
	using floating_identifier = long double;

	/// <summary>
	/// 真.
	/// </summary>
	static constexpr u32 GT_TRUE = 1U;
	/// <summary>
	/// 偽.
	/// </summary>
	static constexpr u32 GT_FALSE = 0U;

	/// <summary>
	/// 無効値.
	/// </summary>
	static constexpr u32 INVALID_VALUE = static_cast<u32>(-1);


#if defined(GT_DEBUG)
	/// <summary>
	/// デバッグ時に例外を投げるかもしれない定数
	/// </summary>
	constexpr bool IS_DEVELOP_NOEXCEPT = false;
#else
	/// <summary>
	/// デバッグ時以外は例外を投げない定数
	/// </summary>
	constexpr bool IS_DEVELOP_NOEXCEPT = true;
#endif


	namespace detail
	{
		struct none_init_holder {};
		struct none_helper {};

	} //! namespace detail


	  /// <summary>
	  /// 無効値型.
	  /// </summary>
	using none_t = gt::detail::none_helper;

	/// <summary>
	/// 無効値.
	/// </summary>
	constexpr none_t nullopt = {};

	/// <summary>
	/// 初期化を明示的に行わない型.
	/// </summary>
	using none_init_t = gt::detail::none_init_holder;

	/// <summary>
	/// 初期化を行わない定数.
	/// </summary>
	constexpr none_init_t none_init_v = {};


} //! namespace gt


/********** End of File ******************************************************/