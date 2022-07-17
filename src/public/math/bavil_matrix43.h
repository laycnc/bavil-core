#pragma once

#include <iterator>
#include <bavil_type.h>
#include <math/bavil_math_def.h>

namespace bavil::math::tl
{

	/// <summary>
	/// 4行3列行列.
	/// <para>平行移動・回転.</para>
	/// </summary>
	template < typename ValueType, typename SizeType > 
	struct Matrix43
	{
		using value_type = ValueType;
		using size_type = SizeType;
		using self_type = Matrix43 < ValueType, SizeType >;
#pragma warning(push)
#pragma warning(disable:4201) // 無名構造体・無名共有体の利用
		union
		{
			struct
			{
				value_type _11, _12, _13;
				value_type _21, _22, _23;
				value_type _31, _32, _33;
				value_type _41, _42, _43;
			};

			value_type	m[4][3];

			value_type v[12];
		};
#pragma warning(pop)

		/// <summary>
		/// 単位行列.
		/// </summary>
		static const Matrix43 IDENTITY;
		/// <summary>
		/// 空行列.
		/// </summary>
		static const Matrix43 EMPTY;

		/// <summary>
		/// コンストラクタ.
		/// </summary>
		/// <param name="m11">1行1列成分</param>
		/// <param name="m12">1行2列成分</param>
		/// <param name="m13">1行3列成分</param>
		/// <param name="m21">2行1列成分</param>
		/// <param name="m22">2行2列成分</param>
		/// <param name="m23">2行3列成分</param>
		/// <param name="m31">3行1列成分</param>
		/// <param name="m32">3行2列成分</param>
		/// <param name="m33">3行3列成分</param>
		/// <param name="m41">4行1列成分</param>
		/// <param name="m42">4行2列成分</param>
		/// <param name="m43">4行3列成分</param>
		constexpr Matrix43(
			const value_type m11, const value_type m12, const value_type m13,
			const value_type m21, const value_type m22, const value_type m23,
			const value_type m31, const value_type m32, const value_type m33,
			const value_type m41, const value_type m42, const value_type m43
		)
			: _11(m11), _12(m12), _13(m13)
			, _21(m21), _22(m22), _23(m23)
			, _31(m31), _32(m32), _33(m33)
			, _41(m41), _42(m42), _43(m43)
		{
		}


		/// <summary>
		/// 要素の先頭を示すポインタを取得.
		/// </summary>
		constexpr value_type* begin()
		{
			return std::begin(this->v);
		}

		/// <summary>
		/// 要素の先頭を示すポインタを取得.
		/// </summary>
		constexpr value_type const* begin() const
		{
			return std::begin(this->v);
		}

		/// <summary>
		/// 要素の最後の次を示すポインタを取得.
		/// </summary>
		constexpr value_type* end()
		{
			return std::end(this->v);
		}

		/// <summary>
		/// 要素の最後の次を示すポインタを取得.
		/// </summary>
		constexpr value_type const* end() const
		{
			return std::end(this->v);
		}


		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>キャスト後のポインタを返す.</returns>
		operator value_type* ()
		{
			return reinterpret_cast<value_type*>(this->v);
		}

		/// <summary>
		/// キャスト演算子オーバーロード.
		/// </summary>
		/// <returns>キャスト後のポインタを返す.</returns>
		operator value_type const* () const
		{
			return reinterpret_cast<const value_type*>(this->v);
		}


	}; //! struct Matrix43

	/// <summary>
	/// 単位行列.
	/// </summary>
	template < typename ValueType, typename SizeType >
	const Matrix43<ValueType, SizeType> Matrix43<ValueType, SizeType>::IDENTITY =
	{
		static_cast<ValueType>(1.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0),
		static_cast<ValueType>(0.0), static_cast<value_type>(1.0), static_cast<value_type>(0.0),
		static_cast<ValueType>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(1.0),
		static_cast<ValueType>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0)
	};

	/// <summary>
	/// 空行列.
	/// </summary>
	template < typename ValueType, typename SizeType >
	const Matrix43<ValueType, SizeType> Matrix43<ValueType, SizeType>::EMPTY =
	{
		static_cast<ValueType>(0.0), static_cast<ValueType>(0.0), static_cast<value_type>(0.0),
		static_cast<ValueType>(0.0), static_cast<ValueType>(0.0), static_cast<value_type>(0.0),
		static_cast<ValueType>(0.0), static_cast<ValueType>(0.0), static_cast<value_type>(0.0),
		static_cast<ValueType>(0.0), static_cast<ValueType>(0.0), static_cast<value_type>(0.0)
	};

}
