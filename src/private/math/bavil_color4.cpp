#include "math/bavil_color4.h"

namespace bavil::math
{

	namespace
	{

		constexpr Color4 color4_black =
		{
			0.0f, 0.0f, 0.0f, 1.0f
		};

		constexpr Color4 color4_blue =
		{
			0.0f, 0.0f, 1.0f, 1.0f
		};


		constexpr Color4 color4_cyan =
		{
			0.0f, 1.0f, 1.0f, 1.0f
		};

		constexpr Color4 color4_green =
		{
			0.0f, 1.0f, 0.0f, 1.0f
		};

		constexpr Color4 color4_magenta =
		{
			1.0f, 0.0f, 1.0f, 1.0f
		};

		constexpr Color4 color4_red =
		{
			1.0f, 0.0f, 0.0f, 1.0f
		};

		constexpr Color4 color4_white =
		{
			1.0f, 1.0f, 1.0f, 1.0f
		};

		constexpr Color4 color4_yellow =
		{
			1.0f, 1.0f, 0.0f, 1.0f
		};

	}

	/// <summary>
	/// ブラック.
	/// </summary>
	const Color4 Color4::BLACK = color4_black;
	/// <summary>
	/// ブルー.
	/// </summary>
	const Color4 Color4::BLUE = color4_blue;
	/// <summary>
	/// シアン.
	/// </summary>
	const Color4 Color4::CYAN = color4_cyan;
	/// <summary>
	/// グリーン.
	/// </summary>
	const Color4 Color4::GREEN = color4_green;
	/// <summary>
	/// マゼンタ.
	/// </summary>
	const Color4 Color4::MAGENTA = color4_magenta;
	/// <summary>
	/// レッド.
	/// </summary>
	const Color4 Color4::RED = color4_red;
	/// <summary>
	/// ホワイト.
	/// </summary>
	const Color4 Color4::WHITE = color4_white;
	/// <summary>
	/// イエロー.
	/// </summary>
	const Color4 Color4::YELLOW = color4_yellow;

}