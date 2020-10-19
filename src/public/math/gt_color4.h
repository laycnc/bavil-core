/// @file		gtlib/math/gt_color4.hpp
/// @date		2014/12/09
/// @brief		カラー型
/// @author		shouta_takemura
#pragma once


// C Library
#include <cassert>
// STL
#include <fstream>
#include <string>
#include <limits>
// gtlib
#include <gt_type.h>
#include <gt_utility.h>
#include <math/gt_math_def.h>
#include <math/gt_math_function.h>

namespace gt::math
{

	/// <summary>
	/// RGBAカラー構造体.
	/// </summary>
	struct Color4
	{
		using value_type = f32;
		using value_array_type = value_type[4];
		using pack_type = u8;
		using size_type = u32;
	public:
#if __cpp_constexpr >= 201304
		union
		{
			struct
			{
#endif
				/// <summary>
				/// Red成分.
				/// </summary>
				value_type	r;
				/// <summary>
				/// Green成分.
				/// </summary>
				value_type	g;
				/// <summary>
				/// Blue成分.
				/// </summary>
				value_type	b;
				/// <summary>
				/// Alpha成分.
				/// </summary>
				value_type	a;
#if __cpp_constexpr >= 201304
			};
			value_array_type v;
		};
#endif

	public:
		/// <summary>
		/// デフォルトコンストラクタ.
		/// </summary>
		constexpr Color4() noexcept
			: r(1.f), g(1.f), b(1.f), a(1.f)
		{}

		/// <summary>
		/// 初期化なしコンストラクタ.
		/// </summary>
		/// <param name="_none">初期化なしタグ.</param>
		explicit Color4(none_init_t _none) noexcept
		{
			static_cast<void>(_none);
		}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="_array">配列.</param>
		explicit constexpr Color4(const value_type* _array) noexcept
			: r{ _array[0] }, g{ _array[1] }, b{ _array[2] }, a{ _array[3] }
		{}


		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="_array">配列.</param>
		explicit constexpr Color4(const pack_type* _array) noexcept
			: r{ _array[0] / 255.f }, g{ _array[1] / 255.f }, b{ _array[2] / 255.f }, a{ _array[3] / 255.f }
		{}

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="red">赤値.</param>
		/// <param name="green">緑値.</param>
		/// <param name="blue">青値.</param>
		/// <param name="alpha">アルファ値.</param>
		constexpr Color4(pack_type red, pack_type green, pack_type blue, pack_type alpha) noexcept
			: r{ red / 255.f }, g{ green / 255.f }, b{ blue / 255.f }, a{ alpha / 255.f }
		{ }

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="red">赤値.</param>
		/// <param name="green">緑値.</param>
		/// <param name="blue">青値.</param>
		/// <param name="alpha">アルファ値.</param>
		constexpr Color4(const value_type red, const value_type green, const value_type blue, const value_type alpha) noexcept
			: r{ red }, g{ green }, b{ blue }, a{ alpha }
		{ }

		/// <summary>
		/// 0.0f～1.0の範囲にクランプ.
		/// </summary>
		/// <returns>変換後のカラーを返す.</returns>
		constexpr Color4& saturate() noexcept
		{
			this->r = math::Clamp(this->r, 0.f, 1.f);
			this->g = math::Clamp(this->g, 0.f, 1.f);
			this->b = math::Clamp(this->b, 0.f, 1.f);
			this->a = math::Clamp(this->a, 0.f, 1.f);

			return *this;
		}

		/// <summary>
		/// カラー補色を求める.
		/// </summary>
		/// <returns>反対色を返す.</returns>
		constexpr Color4& complementary() noexcept
		{
			this->r = 1.f - this->a;
			this->g = 1.f - this->a;
			this->b = 1.f - this->a;
			return *this;
		}

		/// <summary>
		/// カラー補色を求める.
		/// </summary>
		/// <returns>反対色を返す.</returns>
		constexpr Color4 getComplementary() const noexcept
		{
			return Color4
			{
				1.0f - this->r,
				1.0f - this->g,
				1.0f - this->b,
				this->a
			};
		}

		/// <summary>
		/// カラーからモノクロに変換する.
		/// </summary>
		/// <returns>変換後のカラーを返す.</returns>
		constexpr Color4& grayscale() noexcept
		{
			this->a = this->r * 0.2125f + this->g * 0.7154f + this->b * 0.0721f;
			return *this;
		}

		/// <summary>
		/// 線形補完.
		/// </summary>
		/// <param name="start">開始ベクトル.</param>
		/// <param name="end">終了ベクトル.</param>
		/// <param name="amount">補完係数<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		constexpr Color4& lerp(const Color4& start, const Color4& end, const value_type amount) noexcept
		{
			this->r = math::Lerp(start.r, end.r, amount);
			this->g = math::Lerp(start.g, end.g, amount);
			this->b = math::Lerp(start.b, end.b, amount);
			this->a = math::Lerp(start.a, end.a, amount);
			return *this;
		}

		/// <summary>
		/// 線形補完.
		/// </summary>
		/// <param name="start">開始ベクトル.</param>
		/// <param name="end">終了ベクトル.</param>
		/// <param name="amount">補完係数<para>クランプしない</para>.</param>
		constexpr Color4& lerpLoop(const Color4& start, const Color4& end, const value_type amount) noexcept
		{
			return this->lerp(start, end, std::sin(amount) * 0.5f + 0.5f);
		}

	public:
		/// <summary>
		/// 線形補完.
		/// </summary>
		/// <param name="start">開始ベクトル.</param>
		/// <param name="end">終了ベクトル.</param>
		/// <param name="amount">補完係数<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		static Color4 Lerp(const Color4& start, const Color4& end, const value_type amount)
		{
			return Color4{ none_init_v }.lerp(start, end, amount);
		}

		/// <summary>
		/// 線形補完.
		/// </summary>
		/// <param name="start">開始ベクトル.</param>
		/// <param name="end">終了ベクトル.</param>
		/// <param name="amount">補完係数<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		static Color4 LerpLoop(const Color4& start, const Color4& end, const value_type amount)
		{
			return Color4{ none_init_v }.lerpLoop(start, end, amount);
		}

		/// <summary>
		/// べき乗で線形補完を行う.
		/// </summary>
		/// <param name="start">開始ベクトル.</param>
		/// <param name="end">終了ベクトル.</param>
		/// <param name="amount">補完係数<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		/// <param name="power">べき乗数.</param>
		static Color4 LerpPower(const Color4& start, const Color4& end, const value_type amount, const value_type power)
		{
			return Color4::Lerp(start, end, std::pow(amount, power));
		}

		/// <summary>
		/// べき乗で線形補完を行う.
		/// </summary>
		/// <param name="start">開始ベクトル.</param>
		/// <param name="end">終了ベクトル.</param>
		/// <param name="amount">補完係数<para>.0.0(開始値)～1.0(終了値)</para>.</param>
		/// <param name="power">べき乗数.</param>
		static Color4 LerpSinPower(const Color4& start, const Color4& end, const value_type amount, const value_type power)
		{
			return Color4::Lerp(start, end, std::pow(std::sin(90.0f * amount), power));
		}
	public:

#pragma region StaticFildMember

		/// <summary>
		/// カラーコードサイズ.
		/// </summary>
		static constexpr size_type CODE_SIZE = 8U;

		/// <summary>
		/// ブラック.
		/// </summary>
		static const Color4 BLACK;
		/// <summary>
		/// ブルー.
		/// </summary>
		static const Color4 BLUE;
		/// <summary>
		/// シアン.
		/// </summary>
		static const Color4 CYAN;
		/// <summary>
		/// グリーン.
		/// </summary>
		static const Color4 GREEN;
		/// <summary>
		/// マゼンタ.
		/// </summary>
		static const Color4 MAGENTA;
		/// <summary>
		/// レッド.
		/// </summary>
		static const Color4 RED;
		/// <summary>
		/// ホワイト.
		/// </summary>
		static const Color4 WHITE;
		/// <summary>
		/// イエロー.
		/// </summary>
		static const Color4 YELLOW;

#pragma endregion

	public:
		/// <summary>
		/// 最初の要素のポインタを取得.
		/// </summary>
		constexpr value_type* begin() noexcept
		{
#if __cpp_constexpr >= 201304
			return std::begin(this->v);
#else //! __cpp_constexpr >= 201304
			return gt::begin(reinterpret_cast<value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 最初の要素の定数ポインタを取得.
		/// </summary>
		constexpr const value_type* begin() const noexcept
		{
#if __cpp_constexpr >= 201304
			return std::begin(this->v);
#else //! __cpp_constexpr >= 201304
			return std::begin(reinterpret_cast<const value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 最後の次を示すポインタを取得.
		/// </summary>
		constexpr value_type* end() noexcept
		{
#if __cpp_constexpr >= 201304
			return std::end(this->v);
#else //! __cpp_constexpr >= 201304
			return std::end(reinterpret_cast<value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 最後の次を示す定数ポインタを取得.
		/// </summary>
		constexpr const value_type* end() const noexcept
		{
#if __cpp_constexpr >= 201304
			return std::end(this->v);
#else //! __cpp_constexpr >= 201304
			return std::end(reinterpret_cast<const value_array_type&>(*this));
#endif //! __cpp_constexpr >= 201304
		}

	public:
		/// <summary>
		/// 加算単行演算子オーバーロード.
		/// </summary>
		constexpr Color4 operator + () const& noexcept
		{
			return Color4(*this);
		}

		/// <summary>
		/// 加算単行演算子オーバーロード.
		/// </summary>
		constexpr Color4&& operator + () && noexcept
		{
			return std::move(*this);
		}

		/// <summary>
		/// 減算単行演算子オーバーロード.
		/// </summary>
		constexpr Color4 operator - () const& noexcept
		{
			return
			{
				-this->r,
				-this->g,
				-this->b,
				-this->a
			};
		}

		/// <summary>
		/// 減算単行演算子オーバーロード.
		/// </summary>
		constexpr Color4&& operator - () && noexcept
		{
			this->r = -this->r;
			this->g = -this->g;
			this->b = -this->b;
			this->a = -this->a;
			return std::move(*this);
		}

		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>変換後のポインタを返す.</returns>
		constexpr operator value_type* () noexcept
		{
#if __cpp_constexpr >= 201304
			return this->v;
#else //! __cpp_constexpr >= 201304
			return reinterpret_cast<value_type*>(this);
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>変換後のポインタを返す.</returns>
		constexpr operator const value_type* () const noexcept
		{
#if __cpp_constexpr >= 201304
			return this->v;
#else //! __cpp_constexpr >= 201304
			return reinterpret_cast<const value_type*>(this);
#endif //! __cpp_constexpr >= 201304
		}

		/// <summary>
		/// 加算代入演算子オーバーロード.
		/// </summary>
		/// <param name="ohter">加算相手カラー.</param>
		/// <returns>計算後のカラー.</returns>
		constexpr Color4& operator += (const Color4& ohter) noexcept
		{
			this->r += ohter.r;
			this->g += ohter.g;
			this->b += ohter.b;
			this->a += ohter.a;
			return *this;
		}

		/// <summary>
		/// 減算代入演算子オーバーロード.
		/// </summary>
		/// <param name="ohter">減算相手カラー.</param>
		/// <returns>計算後のカラー.</returns>
		constexpr Color4& operator -= (const Color4& ohter) noexcept
		{
			this->r -= ohter.r;
			this->g -= ohter.g;
			this->b -= ohter.b;
			this->a -= ohter.a;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="ohter">乗算相手カラー.</param>
		/// <returns>計算後のカラー.</returns>
		constexpr Color4& operator *= (const Color4& ohter) noexcept
		{
			this->r *= ohter.r;
			this->g *= ohter.g;
			this->b *= ohter.b;
			this->a *= ohter.a;
			return *this;
		}

		/// <summary>
		/// 除算代入演算子オーバーロード.
		/// </summary>
		/// <param name="ohter">除算相手カラー.</param>
		/// <returns>計算後のカラー.</returns>
		constexpr Color4& operator /= (const Color4& ohter) noexcept
		{
			this->r /= ohter.r;
			this->g /= ohter.g;
			this->b /= ohter.b;
			this->a /= ohter.a;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子オーバーロード.
		/// </summary>
		/// <param name="s">スカラー値.</param>
		/// <returns>計算後のカラー.</returns>
		constexpr Color4& operator *= (const value_type s) noexcept
		{
			this->r *= s;
			this->g *= s;
			this->b *= s;
			this->a *= s;
			return *this;
		}

		/// <summary>
		/// 除算代入演算子オーバーロード.
		/// </summary>
		/// <param name="s">スカラー値.</param>
		/// <returns>計算後のカラー.</returns>
		constexpr Color4& operator /= (const value_type s) noexcept
		{
			*this *= (1.0f / s);
			return *this;
		}

	public:
		/// <summary>
		/// 加算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">カラー2.</param>
		/// <returns>加算後のカラーを返す.</returns>
		constexpr Color4 operator + (const Color4& right) const& noexcept
		{
			return Color4
			{
				this->r + right.r,
				this->g + right.g,
				this->b + right.b,
				this->a + right.a
			};
		}

		/// <summary>
		/// 加算2項演算子オーバーロード.
		/// </summary>
		/// <param name="right">カラー2.</param>
		/// <returns>加算後のカラーを返す.</returns>
		constexpr Color4&& operator + (const Color4& right) && noexcept
		{
			return std::move(*this += right);
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		/// <param name="color2">カラー2.</param>
		/// <returns>減算後のカラーを返す.</returns>
		constexpr Color4 operator - (const Color4& right) const& noexcept
		{
			return Color4
			{
				this->r - right.r,
				this->g - right.g,
				this->b - right.b,
				this->a - right.a
			};
		}

		/// <summary>
		/// 減算2項演算子オーバーロード.
		/// </summary>
		/// <param name="color2">カラー2.</param>
		/// <returns>減算後のカラーを返す.</returns>
		constexpr Color4&& operator - (const Color4& right) && noexcept
		{
			return std::move(*this -= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="left">カラー1.</param>
		/// <param name="right">カラー2.</param>
		/// <returns>乗算後のカラーを返す.</returns>
		CONSTEXPR_CPP11 Color4 operator * (const Color4& right) const& noexcept
		{
			return Color4
			{
				this->r * right.r,
				this->g * right.g,
				this->b * right.b,
				this->a * right.a
			};
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="left">カラー1.</param>
		/// <param name="right">カラー2.</param>
		/// <returns>乗算後のカラーを返す.</returns>
		constexpr	Color4&& operator * (const Color4& right) && noexcept
		{
			return std::move(*this *= right);
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="s">数値.</param>
		/// <param name="right">カラー.</param>
		/// <returns>乗算後のカラーを返す.</returns>
		CONSTEXPR_CPP11 friend Color4 operator * (const value_type left, const Color4& right) noexcept
		{
			return right * left;
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="left">カラー.</param>
		/// <param name="s">数値.</param>
		/// <returns>乗算後のカラーを返す.</returns>
		CONSTEXPR_CPP11 Color4 operator * (const value_type right) const& noexcept
		{
			return
			{
				this->r * right,
				this->g * right,
				this->b * right,
				this->a * right
			};
		}

		/// <summary>
		/// 乗算2項演算子オーバーロード.
		/// </summary>
		/// <param name="left">カラー.</param>
		/// <param name="s">数値.</param>
		/// <returns>乗算後のカラーを返す.</returns>
		constexpr	Color4&& operator * (const value_type right) && noexcept
		{
			return std::move(*this *= right);
		}

		/// <summary>
		/// 除法2項演算子オーバーロード.
		/// </summary>
		/// <param name="color">カラー.</param>
		/// <param name="s">数値.</param>
		/// <returns>除法後のカラーを返す.</returns>
		CONSTEXPR_CPP11 Color4 operator / (const value_type right) const& noexcept
		{
			return Color4
			{
				this->r / right,
				this->g / right,
				this->b / right,
				this->a / right
			};
		}

		/// <summary>
		/// 除法2項演算子オーバーロード.
		/// </summary>
		/// <param name="color">カラー.</param>
		/// <param name="s">数値.</param>
		/// <returns>除法後のカラーを返す.</returns>
		constexpr Color4&& operator / (const value_type right) && noexcept
		{
			return std::move(*this /= right);
		}

		constexpr bool operator == (const Color4& _right) const noexcept
		{
			return
				this->r == _right.r &&
				this->g == _right.g &&
				this->b == _right.b &&
				this->a == _right.a;
		}

		constexpr bool operator != (const Color4& _right) const noexcept
		{
			return !(*this == _right);
		}

	};

}