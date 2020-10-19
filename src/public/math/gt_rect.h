#pragma once

#include "gt_type.h"

namespace gt::math
{

	/// <summary>
	/// 矩形構造体.
	/// </summary>
	struct Rect
	{
		/// <summary>
		/// 左上隅のｘ座標.
		/// </summary>
		f32	left;
		/// <summary>
		/// 左上隅のｙ座標.
		/// </summary>
		f32	top;
		/// <summary>
		/// 右下隅のｘ座標.
		/// </summary>
		f32	right;
		/// <summary>
		/// 右下隅のｙ座標.
		/// </summary>
		f32	bottom;

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		constexpr Rect(void) noexcept
			: left(0.f)
			, top(0.f)
			, right(1.f)
			, bottom(1.f)
		{ }

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="left_">左端.</param>
		/// <param name="top_">上端.</param>
		/// <param name="right_">右端.</param>
		/// <param name="bottom_">下端.</param>
		constexpr Rect(const f32 left_, const f32 top_, const f32 right_, const f32 bottom_) noexcept
			: left(left_)
			, top(top_)
			, right(right_)
			, bottom(bottom_)
		{}

		/// <summary>
		/// 初期化なしコンストラクタ.
		/// </summary>
		explicit Rect(none_init_t) noexcept
		{}

	};

}
