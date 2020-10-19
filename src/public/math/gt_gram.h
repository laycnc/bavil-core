/// @file		gtlib/
/// @date		2015/02/07
/// @brief		ヘッダファイル
/// @author		shouta_takemura
#pragma once
#include <gtlib/gt_type.hpp>
/// <summary>gtlib名前空間.</summary>
namespace gt
{
	/// <summary>数学名前空間.</summary>
	namespace math
	{

		template<class T>
		struct unit_traits
		{
			static constexpr T mega_v = static_cast<T>(1000000.0);
			static constexpr T kilo_v = static_cast<T>(1000.0);
			static constexpr T base_v = static_cast<T>(1.0);
			static constexpr T milli_v = static_cast<T>(0.001);
			static constexpr T micro_v = static_cast<T>(0.000001);

		};

		/// <summary>
		/// グラムクラス
		/// </summary>
		class Gram
			: public unit_traits<f32>
		{
			f32 m_gram = 0.f;
		public:

			/// <summary>
			/// デフォルトコンストラクタ.
			/// </summary>
			constexpr Gram() noexcept
				: m_gram()
			{}

			/// <summary>
			/// コンストラクタ.
			/// </summary>
			/// <param name="_gram">グラム.</param>
			constexpr Gram(f32 _gram) noexcept
				: m_gram(_gram)
			{}

			/// <summary>
			/// コンストラクタ.
			/// </summary>
			/// <param name="_gram">グラム.</param>
			constexpr Gram(floating_identifier _gram) noexcept
				: m_gram(static_cast<f32>(_gram))
			{}

			/// <summary>
			/// 内部データを取得.
			/// </summary>
			/// <returns></returns>
			constexpr f32 get() const noexcept
			{
				return this->m_gram;
			}

			constexpr operator f32() const noexcept
			{
				return this->m_gram;
			}
			constexpr Gram operator + () const noexcept
			{
				return *this;
			}
			constexpr Gram operator - () const noexcept
			{
				return Gram(-this->m_gram);
			}
			constexpr Gram operator + (const Gram& _other) const noexcept
			{
				return Gram(this->m_gram + _other.m_gram);
			}
			constexpr Gram operator + (f32 _other) const noexcept
			{
				return Gram(this->m_gram + _other);
			}
			constexpr Gram operator - (const Gram& _other) const noexcept
			{
				return Gram(this->m_gram - _other.m_gram);
			}
			constexpr Gram operator - (f32 _other) const noexcept
			{
				return Gram(this->m_gram - _other);
			}
			constexpr Gram operator * (const Gram& _other) const noexcept
			{
				return Gram(this->m_gram * _other.m_gram);
			}
			constexpr Gram operator * (f32 _other) const noexcept
			{
				return Gram(this->m_gram * _other);
			}
			constexpr Gram operator / (const Gram& _other) const noexcept
			{
				return Gram(this->m_gram / _other.m_gram);
			}
			constexpr Gram operator / (f32 _other) const noexcept
			{
				return Gram(this->m_gram / _other);
			}
			constexpr bool operator == (const Gram& _right) const noexcept
			{
				return this->m_gram == _right.m_gram;
			}
			constexpr bool operator != (const Gram& _right) const noexcept
			{
				return !(*this == _right);
			}
			friend constexpr Gram operator ""_g(floating_identifier _gram) noexcept;
			friend constexpr Gram operator ""_g(uint_identifier _gram) noexcept;
			friend constexpr Gram operator ""_mg(floating_identifier _gram) noexcept;
			friend constexpr Gram operator ""_mg(uint_identifier _gram) noexcept;
			friend constexpr Gram operator ""_kg(floating_identifier _gram) noexcept;
			friend constexpr Gram operator ""_kg(uint_identifier _gram) noexcept;

		};

		/// <summary>
		/// メーターリテラル.
		/// </summary>
		/// <param name="_gram">重さ.</param>
		/// <returns>グラムを返す</returns>
		constexpr Gram operator ""_g(floating_identifier _gram) noexcept
		{
			return Gram(static_cast<f32>(_gram));
		}
		/// <summary>
		/// メーターリテラル.
		/// </summary>
		/// <param name="_gram">重さ.</param>
		/// <returns>グラムを返す</returns>
		constexpr Gram operator ""_g(uint_identifier _gram) noexcept
		{
			return operator""_g(static_cast<floating_identifier>(_gram));
		}
		/// <summary>
		/// ミリグラムリテラル.
		/// </summary>
		/// <param name="_gram">重さ.</param>
		/// <returns>変換後のグラムを返す</returns>
		constexpr Gram operator ""_mg(floating_identifier _gram) noexcept
		{
			return Gram(_gram * Gram::milli_v);
		}
		/// <summary>
		/// ミリグラムリテラル.
		/// </summary>
		/// <param name="_gram">重さ.</param>
		/// <returns>変換後のグラムを返す</returns>
		constexpr Gram operator ""_mg(uint_identifier _gram) noexcept
		{
			return operator""_mg(static_cast<floating_identifier>(_gram));
		}
		/// <summary>
		/// キログラムリテラル.
		/// </summary>
		/// <param name="_gram">重さ.</param>
		/// <returns>変換後のグラムを返す</returns>
		constexpr Gram operator ""_kg(floating_identifier _gram) noexcept
		{
			return Gram(_gram * Gram::kilo_v);
		}
		/// <summary>
		/// キログラムリテラル.
		/// </summary>
		/// <param name="_gram">重さ.</param>
		/// <returns>変換後のグラムを返す</returns>
		constexpr Gram operator ""_kg(uint_identifier _gram) noexcept
		{
			return operator""_kg(static_cast<floating_identifier>(_gram));
		}

	} //! namespace math

} //! namespace gt

  /********** End of File ******************************************************/