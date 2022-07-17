#pragma once

#include "bavil_type.h"

namespace bavil::math
{

	struct Colori4
	{
		using self_type = Colori4;
		using value_type = u8;
		using size_type = u32;
#pragma warning(push)
#pragma warning(disable:4201) // 無名構造体・無名共有体の利用
#if __cpp_constexpr >= 201304
		union
		{
			struct
			{
#endif
				/// <summary>
				/// 赤.
				/// </summary>
				value_type r;
				/// <summary>
				/// 緑.
				/// </summary>
				value_type g;
				/// <summary>
				/// 青.
				/// </summary>
				value_type b;
				/// <summary>
				/// アルファ.
				/// </summary>
				value_type a;
#if __cpp_constexpr >= 201304
			};
			value_type v[4];
		};
#endif
#pragma warning(pop)

		/// <summary>
		/// 白.
		/// </summary>
		static const Colori4 WHITE;
		/// <summary>
		/// 黒.
		/// </summary>
		static const Colori4 BLACK;
		/// <summary>
		/// 赤.
		/// </summary>
		static const Colori4 RED;

		static constexpr size_type MAX = 0xffu;

		/// <summary>
		/// デフォルトコンストラクタ.
		/// </summary>
		constexpr Colori4() noexcept
			: r(0xffu), g(0xffu), b(0xffu), a(0xffu)
		{ }

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		explicit Colori4(none_init_t) noexcept
		{ }

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="rgba">RGBA</param>
		explicit constexpr Colori4(const u32 rgba) noexcept
			: r(rgba & 0xff000000), g(rgba & 0x00ff0000u), b(rgba & 0x0000ff00u), a(rgba & 0x000000ffu)
		{ }

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="_red"></param>
		/// <param name="_green"></param>
		/// <param name="blue"></param>
		/// <param name="_alpha"></param>
		constexpr Colori4(value_type _red, value_type _green, value_type _blue, value_type _alpha) noexcept
			: r(_red)
			, g(_green)
			, b(_blue)
			, a(_alpha)
		{ }

		constexpr bool operator == (const self_type& _right) const noexcept
		{
			return
				this->r == _right.r &&
				this->g == _right.g &&
				this->b == _right.b &&
				this->a == _right.a;
		}

		constexpr bool operator != (const self_type& _right) const noexcept
		{
			return !(*this == _right);
		}
	};

}
