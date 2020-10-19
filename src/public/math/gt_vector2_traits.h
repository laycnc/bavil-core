/// @file		gtlib/math/gt_vector2.hpp
/// @date		2014/12/09
/// @brief		2次元ベクトル構造体
/// @author		shouta_takemura
#pragma once

// STL
#include <utility>
// gtlib
#include <gtlib/gt_type.hpp>
#include <gtlib/gt_mpl.hpp>
#include <gtlib/gt_utility.hpp>
#include <gtlib/math/gt_math_function.hpp>
#include <gtlib/math/gt_math_def.hpp>
#include <gtlib/math/tl/gt_tl_vector2.hpp>


/// <summary>gtlib名前空間.</summary>
namespace gt
{
	/// <summary>数学名前空間.</summary>
	namespace math
	{

		namespace tl
		{

			template<typename ElementType, typename ValueType>
			struct vector2_member_traits;

			template<typename ElementType, typename SizeType>
			struct vector2_member_traits<ElementType, tl::Vector2<ElementType, SizeType>>
			{
				using element_type = ElementType;
				using value_type = tl::Vector2<ElementType, SizeType>;
				using self_traits = vector2_member_traits<element_type, value_type>;
				template<class OtherType>
				using any_traits = vector2_traits<element_type, OtherType>;

				static inline element_type GetX( const value_type& self )
				{
					return self.x;
				}

				static inline element_type GetY( const value_type& self )
				{
					return self.y;
				}

				static inline element_type SetX( const value_type& self )
				{
					self.y = value;
				}

				static inline element_type SetY( const value_type& self, element_type value )
				{
					self.x = value;
				}

			protected:

				static inline void _ThisAdd( const value_type& self, element_type value ) noexcept
				{
					self.x += value;
					self.y += value;
				}

				template<class OtherType>
				static inline void _ThisAdd( const value_type& self, const OtherType& other )
				{
					using other_traits = any_traits<OtherType>;
					self.x += other_traits::X( other );
					self.y += other_traits::Y( other );
				}

				static inline void _ThisSub( const value_type& self, element_type value ) noexcept
				{
					self.x -= value;
					self.y -= value;
				}

				template<class OtherType>
				static inline void _ThisSub( const value_type& self, const OtherType& other )
				{
					using other_traits = any_traits<OtherType>;
					self.x -= other_traits::X( other );
					self.y -= other_traits::Y( other );
				}

				static inline void _ThisMultiply( const value_type& self, element_type value ) noexcept
				{
					self.x *= value;
					self.y *= value;
				}

				template<class OtherType>
				static inline void _ThisMultiply( const value_type& self, const OtherType& other )
				{
					using other_traits = any_traits<OtherType>;
					self.x *= other_traits::X( other );
					self.y *= other_traits::Y( other );
				}

				static inline void _ThisDivision( const value_type& self, element_type value )
				{
					self.x /= value;
					self.y /= value;
				}

				template<class OtherType>
				static inline void _ThisDivision( const value_type& self, const OtherType& other )
				{
					using other_traits = any_traits<OtherType>;
					self.x /= other_traits::X( other );
					self.y /= other_traits::Y( other );
				}

			};


			template<typename ElementType>
			struct vector2_member_traits<ElementType, ElementType[2]>
			{
				using element_type = ElementType;
				using value_type = ElementType[2];
				using self_traits = vector2_member_traits<element_type, value_type>;
				template<class OtherType>
				using any_traits = vector2_traits<element_type, OtherType>;

				static inline element_type GetX( const value_type& self )
				{
					return self[0];
				}

				static inline element_type GetY( const value_type& self )
				{
					return self.y;
				}

				static inline element_type SetX( const value_type& self )
				{
					self.y = value;
				}

				static inline element_type SetY( const value_type& self, element_type value )
				{
					self[0] = value;
				}

			protected:

				static inline void _ThisAdd( const value_type& self, element_type value ) noexcept
				{
					self[0] += value;
					self[1] += value;
				}

				template<class OtherType>
				static inline void _ThisAdd( const value_type& self, const OtherType& other )
				{
					using other_traits = any_traits<OtherType>;
					self[0] += other_traits::X( other );
					self[1] += other_traits::Y( other );
				}

				static inline void _ThisSub( const value_type& self, element_type value ) noexcept
				{
					self[0] -= value;
					self[1] -= value;
				}

				template<class OtherType>
				static inline void _ThisSub( const value_type& self, const OtherType& other )
				{
					using other_traits = any_traits<OtherType>;
					self[0] -= other_traits::X( other );
					self[1] -= other_traits::Y( other );
				}

				static inline void _ThisMultiply( const value_type& self, element_type value ) noexcept
				{
					self[0] *= value;
					self[1] *= value;
				}

				template<class OtherType>
				static inline void _ThisMultiply( const value_type& self, const OtherType& other )
				{
					using other_traits = any_traits<OtherType>;
					self[0] *= other_traits::X( other );
					self[1] *= other_traits::Y( other );
				}

				static inline void _ThisDivision( const value_type& self, element_type value )
				{
					self[0] /= value;
					self[1] /= value;
				}

				template<class OtherType>
				static inline void _ThisDivision( const value_type& self, const OtherType& other )
				{
					using other_traits = any_traits<OtherType>;
					self[0] /= other_traits::X( other );
					self[1] /= other_traits::Y( other );
				}

			};



			template<typename ElementType, typename ValueType>
			struct vector2_traits
				: vector2_member_traits<ElementType, ValueType>
			{
				using element_type = ElementType;
				using value_type = ValueType;
				using member_traits = vector2_member_traits<element_type, value_type>;
				using self_traits = vector2_traits<element_type, value_type>;

				template<class OtherType>
				using any_traits = vector2_traits<element_type, OtherType>;


				/// <summary>
				/// 正規化.
				/// </summary>
				/// <returns>正規化後の参照を返す.</returns>
				static inline value_type& Normalize( const value_type& self ) noexcept
				{
					if( const element_type len = self_trits::LengthSqr( self ) )
					{
						return self_trits::Division( self, std::sqrt( len ) );
					}

					return self;
				}

				/// <summary>
				/// ベクトルの長さを求める.
				/// </summary>
				/// <returns>ベクトルの長さを返す.</returns>
				static inline element_type Length( const value_type& self ) noexcept
				{
					return std::sqrt( self_traits::LengthSqr( self ) );
				}

				/// <summary>
				/// ベクトルの長さを求める.
				/// <para>二乗和のみで平方根をとらない.</para>
				/// </summary>
				/// <returns>ベクトルの長さを返す.</returns>
				static inline element_type LengthSqr( const value_type& self ) noexcept
				{
					return self_traits::Dot( self, self );
				}

				/// <summary>
				/// 内積を求める.
				/// <para>a・b = |a||b|cosθ</para>
				/// </summary>
				/// <param name="other">ベクトル</param>
				/// <returns>内積を返す.</returns>
				template<class OtherType>
				static inline element_type Dot( const value_type& self, const OtherType& other ) noexcept
				{
					return
					{
						self_traits::GetX( self ) * any_traits<OtherType>::X( other ) +
						self_traits::GetY( self ) * any_traits<OtherType>::Y( other )
					};
				}

				/// <summary>
				/// ベクトルの外積を求める.
				/// </summary>
				/// <param name="other">ベクトル</param>
				/// <returns>外積を返す.</returns>
				template<class OtherType>
				static inline element_type CCW( const value_type& self, const OtherType& other ) noexcept
				{
					return
					{
						self_traits::GetX( self ) * any_traits<OtherType>::Y( other ) -
						self_traits::GetY( self ) * any_traits<OtherType>::X( other )
					};
				}

				static inline value_type Negate( const value_type& self ) noexcept
				{
					return 
					{
						-self_traits::GetX( self ),
						-self_traits::GetY( self )
					};
				}

				static inline value_type&& Negate( value_type&& self ) noexcept
				{
					self_traits::SetX( self, -self_traits::GetX( self ) );
					self_traits::SetX( self, -self_traits::GetY( self ) );
				}

				template<class OtherType>
				static inline value_type Add( const value_type& self, const OtherType& other ) noexcept
				{
					using other_traits = any_traits<OtherType>;
					return
					{
						self_traits::GetX( self ) + other_traits::X( other ),
						self_traits::GetY( self ) + other_traits::Y( other )
					};
				}

				template<class OtherType>
				static inline value_type&& Add( const value_type&& self, const OtherType& other ) noexcept
				{
					self_traits::_ThisAdd( self, other );
					return std::move( self );
				}

				static inline value_type Add( const value_type& self, element_type other ) noexcept
				{
					using other_traits = any_traits<OtherType>;
					return
					{
						self_traits::GetX( self ) + other,
						self_traits::GetY( self ) + other
					};
				}

				static inline value_type&& Add( const value_type&& self, element_type other ) noexcept
				{
					self_traits::_ThisAdd( self, other );
					return std::move( self );
				}

				template<class OtherType>
				static inline value_type Sub( const value_type& self, const OtherType& other ) noexcept
				{
					using other_traits = any_traits<OtherType>;
					return
					{
						self_traits::GetX( self ) - other_traits::X( other ),
						self_traits::GetY( self ) - other_traits::Y( other )
					};
				}

				template<class OtherType>
				static inline value_type&& Sub( const value_type&& self, const OtherType& other ) noexcept
				{
					self_traits::_ThisSub( self, other );
					return std::move( self );
				}

				static inline value_type Sub( const value_type& self, element_type other ) noexcept
				{
					return
					{
						self_traits::GetX( self ) - other,
						self_traits::GetY( self ) - other
					};
				}

				static inline value_type&& Sub( const value_type&& self, element_type other ) noexcept
				{
					self_traits::_ThisSub( self, other );
					return std::move( self );
				}

				template<class OtherType>
				static inline value_type Multiply( const value_type& self, const OtherType& other ) noexcept
				{
					using other_traits = any_traits<OtherType>;
					return
					{
						self_traits::GetX( self ) * other_traits::X( other ),
						self_traits::GetY( self ) * other_traits::Y( other )
					};
				}

				template<class OtherType>
				static inline value_type&& Multiply( value_type&& self, const OtherType& other ) noexcept
				{
					self_traits::_ThisMultiply( self, other );
					return std::move( self );
				}

				static inline value_type Multiply( const value_type& self, element_type other ) noexcept
				{
					using other_traits = any_traits<OtherType>;
					return
					{
						self_traits::GetX( self ) * other,
						self_traits::GetY( self ) * other
					};
				}

				static inline value_type&& Multiply( value_type&& self, element_type other ) noexcept
				{
					self_traits::_ThisMultiply( self, other );
					return std::move( self );
				}

				template<class OtherType>
				static inline value_type Divide( const value_type& self, const OtherType& other ) noexcept
				{
					using other_traits = any_traits<OtherType>;
					return
					{
						self_traits::GetX( self ) / other_traits::X( other ),
						self_traits::GetY( self ) / other_traits::Y( other )
					};
				}

				template<class OtherType>
				static inline value_type&& Divide( value_type&& self, const OtherType& other ) noexcept
				{
					self_traits::_ThisDivide( self, other );
					return std::move( self );
				}

				static inline value_type Divide( const value_type& self, element_type other ) noexcept
				{
					return
					{
						self_traits::GetX( self ) / other,
						self_traits::GetY( self ) / other
					};
				}

				static inline value_type&& Divide( value_type&& self, element_type other ) noexcept
				{
					self_traits::_ThisDivide( self, other );
					return std::move( self );
				}

				template<class OtherType>
				static inline bool Equality( const value_type& self, const OtherType& other ) noexcept
				{
					using other_traits = any_traits<OtherType>;
					return 
					{
						self_traits::GetX( self ) == other_traits::X( other ) &&
						self_traits::GetY( self ) == other_traits::Y( other ) 
					};
				}

				template<class OtherType>
				static inline bool Inequality( const value_type& self, const OtherType& other ) noexcept
				{
					return !self_traits::Equality( self, other );
				}


			};

		} //! namespace tl



	} //! namespace math

} //! namespace gt

  /********** End of File ******************************************************/